//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#include "Engine/Renderer/Apis/Vulkan/Texture/VulkanTextureCubeMapData.h"

namespace gp1::renderer::apis::vulkan::texture
{
	VulkanTextureCubeMapData::VulkanTextureCubeMapData(renderer::texture::TextureCubeMap* texture)
	    : VulkanRendererData(texture) {}

	void VulkanTextureCubeMapData::CleanUp() {}

} // namespace gp1::renderer::apis::vulkan::texture
