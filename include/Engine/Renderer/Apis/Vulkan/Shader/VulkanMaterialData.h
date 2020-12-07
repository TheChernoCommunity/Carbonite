//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#pragma once

#include "Engine/Renderer/Apis/Vulkan/VulkanRendererData.h"
#include "Engine/Renderer/Shader/Material.h"

namespace gp1::renderer::apis::vulkan::shader
{
	class VulkanMaterialData : public VulkanRendererData
	{
	public:
		VulkanMaterialData(renderer::shader::Material* material);

		virtual void CleanUp() override;

		friend VulkanRenderer;
	};

} // namespace gp1::renderer::apis::vulkan::shader
