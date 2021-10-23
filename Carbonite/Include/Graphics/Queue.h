#pragma once

#include <vulkan/vulkan.hpp>

namespace Graphics
{
	struct Queue
	{
		unsigned  graphicsFamilyIndex;
		vk::Queue graphicsQueue;
	};
} // namespace Graphics
