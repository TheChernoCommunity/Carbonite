//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#include "Engine/Renderer/Apis/Vulkan/Texture/VulkanTexture2DArrayData.h"

namespace gp1::renderer::apis::vulkan::texture
{
	VulkanTexture2DArrayData::VulkanTexture2DArrayData(renderer::texture::Texture2DArray* texture)
	    : VulkanRendererData(texture) {}

	void VulkanTexture2DArrayData::CleanUp() {}

} // namespace gp1::renderer::apis::vulkan::texture
