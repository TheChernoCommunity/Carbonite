//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/Vulkan/Shader/VulkanShaderData.h"

namespace gp1::renderer::apis::vulkan::shader
{
	VulkanShaderData::VulkanShaderData(renderer::shader::Shader* shader)
	    : VulkanRendererData(shader) {}

	void VulkanShaderData::CleanUp() {}

} // namespace gp1::renderer::apis::vulkan::shader
