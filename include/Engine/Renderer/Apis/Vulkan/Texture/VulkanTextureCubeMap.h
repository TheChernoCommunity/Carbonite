#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Texture/TextureCubeMap.h"

namespace gp1::renderer::vulkan
{
	struct VulkanTextureCubeMap : public TextureCubeMap
	{
	};
} // namespace gp1::renderer::vulkan

#endif