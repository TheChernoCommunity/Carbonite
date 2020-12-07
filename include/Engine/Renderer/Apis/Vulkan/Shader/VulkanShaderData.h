//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#pragma once

#include "Engine/Renderer/Apis/Vulkan/VulkanRendererData.h"
#include "Engine/Renderer/Shader/Shader.h"

namespace gp1::renderer::apis::vulkan::shader
{
	class VulkanShaderData : public VulkanRendererData
	{
	public:
		VulkanShaderData(renderer::shader::Shader* shader);

		virtual void CleanUp() override;

		friend VulkanRenderer;
	};

} // namespace gp1::renderer::apis::vulkan::shader
