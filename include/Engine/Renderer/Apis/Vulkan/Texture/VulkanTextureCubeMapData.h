//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#pragma once

#include "Engine/Renderer/Apis/Vulkan/VulkanRendererData.h"
#include "Engine/Renderer/Texture/TextureCubeMap.h"

namespace gp1::renderer::apis::vulkan::texture
{
	struct VulkanTextureCubeMapData : public VulkanRendererData
	{
	public:
		VulkanTextureCubeMapData(renderer::texture::TextureCubeMap* texture);

		virtual void CleanUp() override;

		friend VulkanRenderer;
	};

} // namespace gp1::renderer::apis::vulkan::texture
