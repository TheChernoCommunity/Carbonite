#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Material/ReservedUniformBuffers.h"

namespace gp1::renderer::vulkan
{
	struct VulkanReservedUniformBuffers : public ReservedUniformBuffers
	{
	};
} // namespace gp1::renderer::vulkan

#endif