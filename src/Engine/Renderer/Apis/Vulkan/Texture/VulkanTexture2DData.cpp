//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#include "Engine/Renderer/Apis/Vulkan/Texture/VulkanTexture2DData.h"

namespace gp1::renderer::apis::vulkan::texture
{
	VulkanTexture2DData::VulkanTexture2DData(renderer::texture::Texture2D* texture)
	    : VulkanRendererData(texture) {}

	void VulkanTexture2DData::CleanUp() {}

} // namespace gp1::renderer::apis::vulkan::texture
