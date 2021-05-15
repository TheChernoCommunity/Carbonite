#pragma once

#include "Engine/Renderer/RendererData.h"

namespace gp1::renderer::apis::vulkan
{
	class VulkanRenderer;

	struct VulkanRendererData : public RendererData
	{
	public:
		template <typename T>
		VulkanRendererData(T* data)
		    : RendererData(data)
		{
		}

		virtual RendererType GetRendererType() const override;
	};

} // namespace gp1::renderer::apis::vulkan
