//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#include "Engine/Renderer/Apis/Vulkan/Texture/VulkanTexture3DData.h"

namespace gp1::renderer::apis::vulkan::texture
{
	VulkanTexture3DData::VulkanTexture3DData(renderer::texture::Texture3D* texture)
	    : VulkanRendererData(texture) {}

	void VulkanTexture3DData::CleanUp() {}

} // namespace gp1::renderer::apis::vulkan::texture
