//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#pragma once
#include "Engine/Renderer/Renderer.h"

namespace gp1::renderer::apis::vulkan
{
	class VulkanRenderer : public Renderer
	{
	public:
		VulkanRenderer(window::Window* window);

		virtual RendererType GetRendererType() const override;

		virtual renderer::debug::DebugRenderer* CreateDebugRenderer() override;

		virtual RendererData* CreateRendererData(Data* data) override;

	protected:
		virtual void InitRenderer() override;
		virtual void DeInitRenderer() override;
		virtual void RenderScene(scene::Scene* scene, uint32_t width, uint32_t height) override;
	};

} // namespace gp1::renderer::apis::vulkan
