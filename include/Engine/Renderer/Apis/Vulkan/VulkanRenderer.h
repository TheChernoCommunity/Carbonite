#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Renderer.h"

namespace gp1::renderer::vulkan
{
	class VulkanRenderer : public Renderer
	{
	public:
		VulkanRenderer(window::Window* window);

		virtual StaticMesh*    CreateStaticMesh() override;
		virtual Material*      CreateMaterial() override;
		virtual ShaderProgram* CreateShader() override;

		virtual bool IsCompatible() const override;

		virtual void SetWindowHints() override;
		virtual void Init() override;
		virtual void DeInit() override;
		virtual void Render(scene::Camera* camera) override;
	};
} // namespace gp1::renderer::vulkan

#endif