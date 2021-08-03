//
//	Created by MarcasRealAccount on 14. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLMaterial.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLUniformBuffer.h"
#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLShaderProgram.h"

#include <glad/glad.h>

namespace gp1::renderer::opengl
{
	OpenGLMaterial::~OpenGLMaterial()
	{
		CleanUp();
	}

	void OpenGLMaterial::Bind()
	{
		OpenGLShaderProgram* shaderProgram = reinterpret_cast<OpenGLShaderProgram*>(GetShaderProgram());
		if (!shaderProgram)
			return;

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
		for (auto& uniformBuffer : m_UniformBuffers)
		{
			OpenGLUniformBuffer* buffer = reinterpret_cast<OpenGLUniformBuffer*>(uniformBuffer.m_UniformBuffer.get());
			buffer->Bind();
		}
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

	void OpenGLMaterial::UpdateGLData()
	{
		OpenGLShaderProgram* shaderProgram = reinterpret_cast<OpenGLShaderProgram*>(GetShaderProgram());
		if (!shaderProgram)
			return;

		for (auto& uniformBuffer : m_UniformBuffers)
		{
			OpenGLUniformBuffer* buffer = reinterpret_cast<OpenGLUniformBuffer*>(uniformBuffer.m_UniformBuffer.get());

			OpenGLUniformBufferInfo* info = shaderProgram->GetUniformBufferInfo(uniformBuffer.m_Name);
			if (info)
			{
				buffer->SetBinding(info->m_Binding);
				buffer->SetOffsets(info->m_Offsets);
			}
		}
	}

	void OpenGLMaterial::CleanUp()
	{
		for (auto& uniformBuffer : m_UniformBuffers)
		{
			OpenGLUniformBuffer* buffer = reinterpret_cast<OpenGLUniformBuffer*>(uniformBuffer.m_UniformBuffer.get());
			buffer->CleanUp();
		}
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