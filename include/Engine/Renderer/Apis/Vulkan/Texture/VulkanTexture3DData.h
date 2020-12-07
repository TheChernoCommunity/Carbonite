//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#pragma once

#include "Engine/Renderer/Apis/Vulkan/VulkanRendererData.h"
#include "Engine/Renderer/Texture/Texture3D.h"

#include <stdint.h>

namespace gp1::renderer::apis::vulkan::texture
{
	struct VulkanTexture3DData : public VulkanRendererData
	{
	public:
		VulkanTexture3DData(renderer::texture::Texture3D* texture);

		virtual void CleanUp() override;

		friend VulkanRenderer;
	};

} // namespace gp1::renderer::apis::vulkan::texture
