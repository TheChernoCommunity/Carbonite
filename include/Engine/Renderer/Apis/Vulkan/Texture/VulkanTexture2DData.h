//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#pragma once

#include "Engine/Renderer/Apis/Vulkan/VulkanRendererData.h"
#include "Engine/Renderer/Texture/Texture2D.h"

#include <stdint.h>

namespace gp1::renderer::apis::vulkan::texture
{
	struct VulkanTexture2DData : public VulkanRendererData
	{
	public:
		VulkanTexture2DData(renderer::texture::Texture2D* texture);

		virtual void CleanUp() override;

		friend VulkanRenderer;
	};

} // namespace gp1::renderer::apis::vulkan::texture
