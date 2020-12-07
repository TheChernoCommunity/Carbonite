//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/Vulkan/Shader/VulkanMaterialData.h"
#include "Engine/Renderer/Shader/Shader.h"

namespace gp1::renderer::apis::vulkan::shader
{
	VulkanMaterialData::VulkanMaterialData(renderer::shader::Material* material)
	    : VulkanRendererData(material) {}

	void VulkanMaterialData::CleanUp() {}

} // namespace gp1::renderer::apis::vulkan::shader
