#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Material/UniformBuffer.h"

namespace gp1::renderer::vulkan
{
	struct VulkanUniformBuffer : public UniformBuffer
	{
	};
} // namespace gp1::renderer::vulkan
#endif