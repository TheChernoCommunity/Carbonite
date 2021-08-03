#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Texture/Texture2D.h"

namespace gp1::renderer::vulkan
{
	struct VulkanTexture2D : public Texture2D
	{
	};
} // namespace gp1::renderer::vulkan

#endif