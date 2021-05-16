//
//	Created by MarcasRealAccount on 14. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLShaderProgram.h"
#include "Engine/Renderer/Material/ReservedUniformBuffers.h"

#include <cstdint>
#include <set>
#include <stdexcept>
#include <string>

#include <glad/glad.h>

namespace gp1::renderer::opengl
{
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

	bool OpenGLShaderProgram::Update()
	{
		if (m_Dirty)
		{
			if (m_ProgramId)
				CleanUp();

			GenGLData();
			m_Dirty      = false;
			m_HasChanged = true;
		}
		return m_HasChanged;
	}

	bool OpenGLShaderProgram::IsUniformBufferValid(const std::string& name) const
	{
		for (auto& uniformBuffer : m_UniformBufferBindingPoints)
			if (uniformBuffer.m_Name == name)
				return uniformBuffer.m_Binding != UINT32_MAX;
		return false;
	}

	uint32_t OpenGLShaderProgram::GetUniformBufferBindingPoint(const std::string& name) const
	{
		for (auto& uniformBuffer : m_UniformBufferBindingPoints)
			if (uniformBuffer.m_Name == name)
				return uniformBuffer.m_Binding;
		return 0;
	}

	uint32_t OpenGLShaderProgram::GetUniformBufferElementOffset(const std::string& bufferName, const std::string& elementName) const
	{
		for (auto& uniformBuffer : m_UniformBufferBindingPoints)
		{
			if (uniformBuffer.m_Name == bufferName)
			{
				for (auto& offset : uniformBuffer.m_Offsets)
					if (offset.first == elementName)
						return offset.second;
				return 0;
			}
		}
		return 0;
	}

	void OpenGLShaderProgram::GenGLData()
	{
		GLint maxBindingsVal;
		glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &maxBindingsVal);
		GLuint maxBindings = static_cast<GLuint>(maxBindingsVal);
		m_ProgramId        = glCreateProgram();
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
						// sLogger.LogError(infoLog);
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

			m_UniformBufferBindingPoints.reserve(m_UniformBuffers.size());
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
							// sLogger.LogError(infoLog);
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

						for (size_t i = 0; i < uniformOffsets.size(); i++)
							offsets.push_back({ uniformBuffer.m_Elements[i].m_Name, uniformOffsets[i] });
					}

					usedBindings.insert(binding);
					m_UniformBufferBindingPoints.push_back({ uniformBuffer.m_Name, binding, offsets });
				}
				else
				{
					m_UniformBufferBindingPoints.push_back({ uniformBuffer.m_Name, UINT32_MAX, {} });
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
		m_UniformBufferBindingPoints.clear();
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