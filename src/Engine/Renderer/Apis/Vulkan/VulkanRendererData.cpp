#include "Engine/Renderer/Apis/Vulkan/VulkanRendererData.h"

namespace gp1::renderer::apis::vulkan
{
	RendererType VulkanRendererData::GetRendererType() const
	{
		return RendererType::VULKAN;
	}

} // namespace gp1::renderer::apis::vulkan
