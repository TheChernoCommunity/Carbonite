//
//	Created by MarcasRealAccount on 14. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLMaterial.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLUniform.h"
#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLShaderProgram.h"
#include "Engine/Renderer/Material/ReservedUniformBuffers.h"
#include "Engine/Utility/Logger.h"

#include <cstdint>
#include <set>
#include <stdexcept>
#include <string>

#include <glad/glad.h>

namespace gp1::renderer::opengl
{
	Logger s_Logger("OpenGLShaderProgram");

	OpenGLShaderProgram::~OpenGLShaderProgram()
	{
		CleanUp();
	}

	void OpenGLShaderProgram::Bind()
	{
		glUseProgram(m_ProgramId);
	}

	void OpenGLShaderProgram::Unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShaderProgram::Update()
	{
		if (m_Dirty)
		{
			if (m_ProgramId)
				CleanUp();

			GenGLData();
		}

		ShaderProgram::Update();

		if (m_Dirty)
		{
			for (auto& material : m_Materials)
			{
				std::shared_ptr<OpenGLMaterial> mat = std::reinterpret_pointer_cast<OpenGLMaterial>(material.lock());
				mat->UpdateGLData();
			}
			m_Dirty = false;
		}
	}

	OpenGLUniformBufferInfo* OpenGLShaderProgram::GetUniformBufferInfo(const std::string& name) const
	{
		for (auto& uniformBuffer : m_UniformBufferInfos)
			if (uniformBuffer.m_Name == name)
				return const_cast<OpenGLUniformBufferInfo*>(&uniformBuffer);
		return nullptr;
	}

	void OpenGLShaderProgram::GenGLData()
	{
		GLint maxBindingsVal;
		GLint maxTextureBindingsVal;
		glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &maxBindingsVal);
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTextureBindingsVal);
		GLuint maxBindings        = static_cast<GLuint>(maxBindingsVal);
		GLuint maxTextureBindings = static_cast<GLuint>(maxTextureBindingsVal);
		m_ProgramId               = glCreateProgram();
		if (m_ProgramId)
		{
			size_t                shaderCount = m_Shaders.size();
			std::vector<uint32_t> shaderIds;
			shaderIds.reserve(shaderCount);
			for (size_t i = 0; i < shaderCount; i++)
			{
				Shader&  shader   = m_Shaders[i];
				uint32_t shaderId = glCreateShader(GetGLShaderType(shader.m_Type));
				if (shaderId)
				{
					uint8_t*            shaderData     = shader.m_Data.data();
					size_t              shaderDataSize = shader.m_Data.size();
					constexpr GLsizei   dataCount      = 1;
					const GLchar* const dataArr[dataCount] { reinterpret_cast<const GLchar*>(shaderData) };
					const GLint         dataSizes[dataCount] { static_cast<GLint>(shaderDataSize) };

					glShaderSource(shaderId, dataCount, dataArr, dataSizes);
					glCompileShader(shaderId);

					GLint status;
					glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
					if (!status)
					{
						GLint logLength;
						glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
						std::string infoLog(logLength, '\0');
						glGetShaderInfoLog(shaderId, logLength, nullptr, infoLog.data());
						infoLog = "Shader compile failed: " + infoLog;
						for (uint32_t id : shaderIds)
						{
							glDetachShader(m_ProgramId, id);
							glDeleteShader(id);
						}
						glDeleteShader(shaderId);
						CleanUp();
						s_Logger.LogError(infoLog.c_str());
						return;
					}
					else
					{
						glAttachShader(m_ProgramId, shaderId);
						shaderIds.push_back(shaderId);
					}
				}
			}

			glLinkProgram(m_ProgramId);

			for (uint32_t shaderId : shaderIds)
			{
				glDetachShader(m_ProgramId, shaderId);
				glDeleteShader(shaderId);
			}

			GLint status;
			glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &status);
			if (!status)
			{
				GLint logLength;
				glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &logLength);
				std::string infoLog(logLength, '\0');
				glGetProgramInfoLog(m_ProgramId, logLength, nullptr, infoLog.data());
				infoLog = "Shader program link failed: " + infoLog;
				CleanUp();
				// sLogger.LogError(infoLog);
				return;
			}

			m_UniformBufferInfos.reserve(m_UniformBuffers.size());
			std::set<GLuint> usedBindings;
			GLuint           usedBindingsSafeOffset = 0;
			for (auto& uniformBuffer : m_UniformBuffers)
			{
				GLuint index = glGetUniformBlockIndex(m_ProgramId, uniformBuffer.m_Name.data());
				if (index)
				{
					GLint bindingVal;
					glGetActiveUniformBlockiv(m_ProgramId, index, GL_UNIFORM_BLOCK_BINDING, &bindingVal);
					GLuint binding = static_cast<GLuint>(bindingVal);
					if (binding < static_cast<uint32_t>(ReservedUniformBuffers::MaxUniformBufferCount))
					{
						for (binding = static_cast<uint32_t>(ReservedUniformBuffers::MaxUniformBufferCount) + usedBindingsSafeOffset; binding < maxBindings; binding++)
							if (usedBindings.find(binding) == usedBindings.end())
								break;

						if (usedBindings.find(binding) != usedBindings.end())
						{
							std::string infoLog = "Shader program requires more Uniform Buffers than are available! The max is (" + std::to_string(maxBindings) + ")";
							CleanUp();
							s_Logger.LogError(infoLog.c_str());
							return;
						}

						usedBindingsSafeOffset = binding - static_cast<uint32_t>(ReservedUniformBuffers::MaxUniformBufferCount);
						glUniformBlockBinding(m_ProgramId, index, binding);
					}

					std::vector<std::pair<std::string, uint32_t>> offsets;
					offsets.reserve(uniformBuffer.m_Elements.size());
					{
						std::vector<std::string>   uniformNames;
						std::vector<const GLchar*> pUniformNames;
						std::vector<GLuint>        uniformIndices;
						std::vector<GLint>         uniformOffsets;
						pUniformNames.reserve(uniformBuffer.m_Elements.size());
						uniformIndices.resize(uniformBuffer.m_Elements.size());
						uniformOffsets.resize(uniformBuffer.m_Elements.size());
						for (auto& element : uniformBuffer.m_Elements)
						{
							uniformNames.push_back(uniformBuffer.m_Name + "_" + element.m_Name);
							const std::string& uniformName = uniformNames[uniformNames.size() - 1];
							pUniformNames.push_back(uniformName.c_str());
						}
						glGetUniformIndices(m_ProgramId, static_cast<GLsizei>(pUniformNames.size()), pUniformNames.data(), uniformIndices.data());
						glGetActiveUniformsiv(m_ProgramId, static_cast<GLsizei>(uniformIndices.size()), uniformIndices.data(), GL_UNIFORM_OFFSET, uniformOffsets.data());

						std::set<GLuint> usedTextureBindings;
						for (size_t i = 0; i < uniformIndices.size(); i++)
						{
							std::string& name = uniformNames[i];
							for (auto& element : uniformBuffer.m_Elements)
							{
								if (element.m_Name == name && OpenGLUniform::IsTextureType(element.m_Type))
								{
									GLuint textureBinding;
									glGetUniformuiv(m_ProgramId, uniformIndices[i], &textureBinding);

									for (; textureBinding < maxTextureBindings; textureBinding++)
										if (usedTextureBindings.find(textureBinding) == usedTextureBindings.end())
											break;

									uniformOffsets[i] = textureBinding;
									glUniform1i(uniformIndices[i], textureBinding);
								}
							}
						}

						for (size_t i = 0; i < uniformOffsets.size(); i++)
							offsets.push_back({ uniformBuffer.m_Elements[i].m_Name, uniformOffsets[i] });
					}

					usedBindings.insert(binding);
					m_UniformBufferInfos.push_back({ uniformBuffer.m_Name, binding, offsets });
				}
				else
				{
					m_UniformBufferInfos.push_back({ uniformBuffer.m_Name, UINT32_MAX, {} });
				}
			}
		}

		if (!m_Editable || !m_Dynamic)
			m_Shaders.clear();
	}

	void OpenGLShaderProgram::CleanUp()
	{
		glDeleteProgram(m_ProgramId);
		m_ProgramId = 0;
		m_UniformBufferInfos.clear();
	}

	uint32_t OpenGLShaderProgram::GetGLShaderType(EShaderType shaderType) const
	{
		switch (shaderType)
		{
		case EShaderType::VertexShader: return GL_VERTEX_SHADER;
		case EShaderType::TessControlShader: return GL_TESS_CONTROL_SHADER;
		case EShaderType::TessEvaluationShader: return GL_TESS_EVALUATION_SHADER;
		case EShaderType::GeometryShader: return GL_GEOMETRY_SHADER;
		case EShaderType::FragmentShader: return GL_FRAGMENT_SHADER;
		case EShaderType::ComputeShader: return GL_COMPUTE_SHADER;
		default: return 0;
		}
	}
} // namespace gp1::renderer::opengl

#endif