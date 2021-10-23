#pragma once

#include <vulkan/vulkan.hpp>

namespace Graphics
{
	struct Queue
	{
		std::uint32_t graphicsFamilyIndex;
		vk::Queue     graphicsQueue;
	};
} // namespace Graphics
