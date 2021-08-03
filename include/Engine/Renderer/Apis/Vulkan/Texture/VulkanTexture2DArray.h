#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Texture/Texture2DArray.h"

namespace gp1::renderer::vulkan
{
	struct VulkanTexture2DArray : public Texture2DArray
	{
	};
} // namespace gp1::renderer::vulkan

#endif