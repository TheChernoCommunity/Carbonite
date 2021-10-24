#include "Graphics/Image/Image.h"

namespace Graphics
{
	Image::Image(Memory::VMA& vma)
	    : Handle({ &vma }), m_Vma(&vma)
	{
	}

	Image::Image(Memory::VMA& vma, vk::Image& handle)
	    : Handle({ &vma }, handle), m_Vma(&vma)
	{
	}

	Image::~Image()
	{
		if (isCreated())
			destroy();
	}

	void Image::createImpl()
	{
		vk::SharingMode imageSharingMode = vk::SharingMode::eExclusive;

		if (m_Indices.size() > 1)
			imageSharingMode = vk::SharingMode::eConcurrent;

		std::vector<std::uint32_t> indices(m_Indices.begin(), m_Indices.end());

		VkImage image;

		vk::ImageCreateInfo createInfo = { {}, m_ImageType, m_Format, { m_Width, m_Height, m_Depth }, m_MipLevels, m_ArrayLevels, m_Samples, m_Tiling, m_Usage, imageSharingMode, indices, m_InitialLayout };

		VmaAllocationCreateInfo allocationCreateInfo = { {}, m_MemoryUsage, 0, 0, 0, nullptr, nullptr, 0.0f };

		VkImageCreateInfo vkCreateInfo = createInfo;

		auto result = vmaCreateImage(m_Vma->getHandle(), &vkCreateInfo, &allocationCreateInfo, &image, &m_Allocation, nullptr);
		if (result == VK_SUCCESS)
			m_Handle = image;
	}

	bool Image::destroyImpl()
	{
		vmaDestroyImage(m_Vma->getHandle(), m_Handle, m_Allocation);
		m_Allocation = nullptr;
		return true;
	}
} // namespace Graphics