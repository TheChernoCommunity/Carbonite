#include "PCH.h"

#include "Buffer.h"
#include "VMA.h"

namespace Graphics::Memory
{
	Buffer::Buffer(VMA& vma)
	    : m_Vma(vma)
	{
		m_Vma.addChild(this);
	}

	Buffer::~Buffer()
	{
		if (isValid())
			destroy();
		m_Vma.removeChild(this);
	}

	void* Buffer::mapMemory()
	{
		void* memory = nullptr;
		vmaMapMemory(*m_Vma, m_Allocation, &memory);
		return memory;
	}

	void Buffer::unmapMemory()
	{
		vmaUnmapMemory(*m_Vma, m_Allocation);
	}

	void Buffer::createImpl()
	{
		vk::SharingMode imageSharingMode = vk::SharingMode::eExclusive;

		if (m_Indices.size() > 1)
			imageSharingMode = vk::SharingMode::eConcurrent;

		std::vector<std::uint32_t> indices(m_Indices.begin(), m_Indices.end());

		VkBuffer buffer;

		vk::BufferCreateInfo    createInfo           = { {}, m_Size, m_Usage, imageSharingMode, indices };
		VmaAllocationCreateInfo allocationCreateInfo = { {}, m_MemoryUsage, 0, 0, 0, nullptr, nullptr, 0.0f };

		VkBufferCreateInfo vkCreateInfo = createInfo;

		auto result = vmaCreateBuffer(*m_Vma, &vkCreateInfo, &allocationCreateInfo, &buffer, &m_Allocation, nullptr);
		if (result == VK_SUCCESS)
		{
			m_Handle        = buffer;
			m_AllocatedSize = m_Size;
		}
	}

	bool Buffer::destroyImpl()
	{
		vmaDestroyBuffer(*m_Vma, m_Handle, m_Allocation);
		m_Allocation = nullptr;
		return true;
	}
} // namespace Graphics::Memory
