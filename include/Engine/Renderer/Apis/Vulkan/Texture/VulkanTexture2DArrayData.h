//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#pragma once

#include "Engine/Renderer/Apis/Vulkan/VulkanRendererData.h"
#include "Engine/Renderer/Texture/Texture2DArray.h"

#include <stdint.h>

namespace gp1::renderer::apis::vulkan::texture
{
	struct VulkanTexture2DArrayData : public VulkanRendererData
	{
	public:
		VulkanTexture2DArrayData(renderer::texture::Texture2DArray* texture);

		virtual void CleanUp() override;

		friend VulkanRenderer;
	};

} // namespace gp1::renderer::apis::vulkan::texture
