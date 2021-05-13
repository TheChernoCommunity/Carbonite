#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Material/Material.h"

#include <cstdint>
#include <vector>

namespace gp1::renderer::opengl
{
	struct OpenGLUniformBufferInfo
	{
	public:
		OpenGLUniformBufferInfo(const std::string& name, UniformBuffer* uniformBuffer);

		void Bind();

		void CleanUp();

	public:
		std::string    m_Name;
		UniformBuffer* m_UniformBuffer;
		uint32_t       m_Ubo     = 0;
		uint32_t       m_UboSize = 0;
		uint32_t       m_Binding = 0;
	};

	struct OpenGLMaterial : public Material
	{
	public:
		virtual ~OpenGLMaterial();

		void Bind();
		void Unbind();

	private:
		void CleanUp();

		uint32_t GetGLFace(ETriangleFace face);
		uint32_t GetGLBlendFunc(EBlendFunc blendFunc);
		uint32_t GetGLPolygonMode(EPolygonMode polygonMode);

	private:
		std::vector<OpenGLUniformBufferInfo> m_UniformBufferInfos;
	};
} // namespace gp1::renderer::opengl

#endif