#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Texture/Texture3D.h"

namespace gp1::renderer::vulkan
{
	struct VulkanTexture3D : public Texture3D
	{
	};
} // namespace gp1::renderer::vulkan

#endif