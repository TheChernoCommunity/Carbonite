#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Renderer.h"

#include <memory>

namespace gp1::renderer::vulkan
{
	class VulkanRenderer : public Renderer
	{
	public:
		virtual bool IsCompatible() const override;

		virtual void SetWindowHints() override;

	protected:
		virtual std::unique_ptr<StaticMesh>             OnCreateStaticMesh() override;
		virtual std::unique_ptr<Material>               OnCreateMaterial() override;
		virtual std::unique_ptr<ReservedUniformBuffers> OnCreateReservedUniformBuffers() override;
		virtual std::unique_ptr<Uniform>                OnCreateUniform(EUniformType type) override;
		virtual std::unique_ptr<UniformBuffer>          OnCreateUniformBuffer() override;
		virtual std::unique_ptr<ShaderProgram>          OnCreateShaderProgram() override;
		virtual std::unique_ptr<DebugRenderer>          OnCreateDebugRenderer() override;
		virtual std::unique_ptr<Texture2D>              OnCreateTexture2D() override;
		virtual std::unique_ptr<Texture2DArray>         OnCreateTexture2DArray() override;
		virtual std::unique_ptr<Texture3D>              OnCreateTexture3D() override;
		virtual std::unique_ptr<TextureCubeMap>         OnCreateTextureCubeMap() override;

		virtual void OnInit() override;
		virtual void OnDeInit() override;

		virtual void OnBeginFrame() override;
		virtual void OnEndFrame() override;
		virtual void OnRender(scene::Camera* camera) override;
	};
} // namespace gp1::renderer::vulkan

#endif