//
//	Created by MarcasRealAccount on 14. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLMaterial.h"
#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLShaderProgram.h"

#include <glad/glad.h>

namespace gp1::renderer::opengl
{
	OpenGLUniformBufferInfo::OpenGLUniformBufferInfo(const std::string& name, UniformBuffer* uniformBuffer)
	    : m_Name(name), m_UniformBuffer(uniformBuffer) {}

	void OpenGLUniformBufferInfo::Bind()
	{
		if (m_UniformBuffer->IsDirty())
		{
			if (!m_Ubo)
			{
				glGenBuffers(1, &m_Ubo);
				m_UboSize = 0;
			}

			std::vector<uint8_t> uniformData;
			m_UniformBuffer->GetUniformData(uniformData);
			if (uniformData.size() != m_UboSize)
			{
				glBindBuffer(GL_UNIFORM_BUFFER, m_Ubo);
				glBufferData(GL_UNIFORM_BUFFER, uniformData.size(), uniformData.data(), GL_DYNAMIC_DRAW);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}
			else
			{
				glBindBuffer(GL_UNIFORM_BUFFER, m_Ubo);
				glBufferSubData(GL_UNIFORM_BUFFER, 0, uniformData.size(), uniformData.data());
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}
		}

		glBindBufferBase(GL_UNIFORM_BUFFER, m_Binding, m_Ubo);
	}

	void OpenGLUniformBufferInfo::CleanUp()
	{
		glDeleteBuffers(1, &m_Ubo);
		m_Ubo     = 0;
		m_UboSize = 0;
	}

	OpenGLMaterial::~OpenGLMaterial()
	{
		CleanUp();
	}

	void OpenGLMaterial::Bind()
	{
		OpenGLShaderProgram* shaderProgram = reinterpret_cast<OpenGLShaderProgram*>(GetShaderProgram());
		if (!shaderProgram)
			return;

		bool wasShaderProgramDirty = shaderProgram->Update();
		if (wasShaderProgramDirty)
		{
			UpdateShaderProgram();
			std::vector<OpenGLUniformBufferInfo> oldInfos = m_UniformBufferInfos;
			m_UniformBufferInfos.clear();
			m_UniformBufferInfos.reserve(m_UniformBuffers.size());
			for (auto& uniformBuffer : m_UniformBuffers)
			{
				const std::string&      bufferName = uniformBuffer.GetName();
				OpenGLUniformBufferInfo info       = OpenGLUniformBufferInfo(bufferName, &uniformBuffer);
				for (auto itr = oldInfos.begin(), end = oldInfos.end(); itr != end; itr++)
				{
					if (itr->m_Name == bufferName)
					{
						info.m_Ubo     = itr->m_Ubo;
						info.m_UboSize = itr->m_UboSize;
						oldInfos.erase(itr);
						break;
					}
				}
				if (shaderProgram->IsUniformBufferValid(bufferName))
				{
					info.m_Binding = shaderProgram->GetUniformBufferBindingPoint(bufferName);
					for (auto& uniform : uniformBuffer)
						uniform.second.m_Offset = shaderProgram->GetUniformBufferElementOffset(bufferName, uniform.first);
					m_UniformBufferInfos.push_back(info);
				}
				else
				{
					info.CleanUp();
				}
			}
			m_UniformBufferInfos.shrink_to_fit();

			for (auto& oldInfo : oldInfos)
				oldInfo.CleanUp();
		}

		if (m_CullMode.m_Enabled)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GetGLFace(m_CullMode.m_Face));
		}

		if (m_DepthTest)
			glEnable(GL_DEPTH_TEST);

		if (m_BlendFunc.m_Enabled)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GetGLBlendFunc(m_BlendFunc.m_SrcFunc), GetGLBlendFunc(m_BlendFunc.m_DstFunc));
		}

		if (m_PolygonMode.m_Enabled)
			glPolygonMode(GetGLFace(m_PolygonMode.m_Face), GetGLPolygonMode(m_PolygonMode.m_Mode));

		shaderProgram->Bind();
		for (auto& uniformBufferInfo : m_UniformBufferInfos)
			uniformBufferInfo.Bind();
	}

	void OpenGLMaterial::Unbind()
	{
		OpenGLShaderProgram* shaderProgram = reinterpret_cast<OpenGLShaderProgram*>(GetShaderProgram());
		if (!shaderProgram)
			return;

		shaderProgram->Unbind();

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void OpenGLMaterial::CleanUp()
	{
		for (auto& uniformBufferInfo : m_UniformBufferInfos)
			uniformBufferInfo.CleanUp();
		m_UniformBufferInfos.clear();
	}

	uint32_t OpenGLMaterial::GetGLFace(ETriangleFace face)
	{
		switch (face)
		{
		case ETriangleFace::Front: return GL_FRONT;
		case ETriangleFace::Back: return GL_BACK;
		case ETriangleFace::FrontAndBack: return GL_FRONT_AND_BACK;
		default: return 0;
		}
	}

	uint32_t OpenGLMaterial::GetGLBlendFunc(EBlendFunc blendFunc)
	{
		switch (blendFunc)
		{
		case EBlendFunc::Zero: return GL_ZERO;
		case EBlendFunc::One: return GL_ONE;
		case EBlendFunc::SrcColor: return GL_SRC_COLOR;
		case EBlendFunc::OneMinusSrcColor: return GL_ONE_MINUS_SRC_COLOR;
		case EBlendFunc::DstColor: return GL_DST_COLOR;
		case EBlendFunc::OneMinusDstColor: return GL_ONE_MINUS_DST_COLOR;
		case EBlendFunc::SrcAlpha: return GL_SRC_ALPHA;
		case EBlendFunc::OneMinusSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
		case EBlendFunc::DstAlpha: return GL_DST_ALPHA;
		case EBlendFunc::OneMinusDstAlpha: return GL_ONE_MINUS_DST_ALPHA;
		case EBlendFunc::ConstantColor: return GL_CONSTANT_COLOR;
		case EBlendFunc::OneMinusConstantColor: return GL_ONE_MINUS_CONSTANT_COLOR;
		case EBlendFunc::ConstantAlpha: return GL_CONSTANT_ALPHA;
		case EBlendFunc::OneMinusConstantAlpha: return GL_ONE_MINUS_CONSTANT_ALPHA;
		case EBlendFunc::SrcAlphaSaturate: return GL_SRC_ALPHA_SATURATE;
		case EBlendFunc::Src1Color: return GL_SRC1_COLOR;
		case EBlendFunc::OneMinusSrc1Color: return GL_ONE_MINUS_SRC1_COLOR;
		case EBlendFunc::Src1Alpha: return GL_SRC1_ALPHA;
		case EBlendFunc::OneMinusSrc1Alpha: return GL_ONE_MINUS_SRC1_ALPHA;
		default: return 0;
		}
	}

	uint32_t OpenGLMaterial::GetGLPolygonMode(EPolygonMode polygonMode)
	{
		switch (polygonMode)
		{
		case EPolygonMode::Point: return GL_POINT;
		case EPolygonMode::Line: return GL_LINE;
		case EPolygonMode::Fill: return GL_FILL;
		default: return 0;
		}
	}
} // namespace gp1::renderer::opengl

#endif