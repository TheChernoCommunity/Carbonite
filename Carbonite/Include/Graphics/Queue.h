#pragma once

#include <cstdint>

#include <vulkan/vulkan.hpp>

namespace Graphics
{
	struct Queue
	{
		std::uint32_t graphicsFamilyIndex;
		std::uint32_t presentFamilyIndex;
		vk::Queue     graphicsQueue;
		vk::Queue     presentQueue;
	};
} // namespace Graphics
