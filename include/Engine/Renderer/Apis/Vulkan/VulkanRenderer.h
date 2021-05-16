//
//	Created by MarcasRealAccount on 13. May. 2021
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Material/Material.h"
#include "Engine/Renderer/Mesh/StaticMesh.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Shader/ShaderProgram.h"

#include <memory>

namespace gp1::renderer::vulkan
{
	class VulkanRenderer : public Renderer
	{
	public:
		virtual std::shared_ptr<StaticMesh>    CreateStaticMesh() override;
		virtual std::shared_ptr<Material>      CreateMaterial() override;
		virtual std::shared_ptr<ShaderProgram> CreateShader() override;

		virtual bool IsCompatible() const override;

		virtual void SetWindowHints() override;

		virtual void Init() override;
		virtual void DeInit() override;

		virtual void Render(scene::Camera* camera) override;
	};
} // namespace gp1::renderer::vulkan

#endif