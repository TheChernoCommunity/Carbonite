#pragma once

#include "Graphics/Device.h"

#include <set>

namespace Graphics
{
	struct Image : public Handle<vk::Image>
	{
	public:
		Image(Device& device);
		Image(Device& device, vk::Image& handle);
		~Image();

		auto getDevice() const
		{
			return m_Device;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		vk::ImageType m_ImageType   = vk::ImageType::e2D;
		std::uint32_t m_Width       = 0;
		std::uint32_t m_Height      = 0;
		std::uint32_t m_Depth       = 0;
		std::uint32_t m_MipLevels   = 1;
		std::uint32_t m_ArrayLevels = 1;

		vk::Format              m_Format        = vk::Format::eR8G8B8A8Srgb;
		vk::SampleCountFlagBits m_Samples       = vk::SampleCountFlagBits::e1;
		vk::ImageTiling         m_Tiling        = vk::ImageTiling::eOptimal;
		vk::ImageUsageFlags     m_Usage         = vk::ImageUsageFlagBits::eTransferDst;
		vk::ImageLayout         m_InitialLayout = vk::ImageLayout::eUndefined;

		std::set<std::uint32_t> m_Indices;

	private:
		Device* m_Device;
	};
} // namespace Graphics