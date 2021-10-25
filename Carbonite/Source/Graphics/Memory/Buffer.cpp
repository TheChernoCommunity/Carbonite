#include "Graphics/Memory/Buffer.h"

namespace Graphics::Memory
{
	Buffer::Buffer(VMA& vma)
	    : Handle({ &vma }), m_Vma(&vma)
	{
	}

	Buffer::~Buffer()
	{
		if (isCreated())
			destroy();
	}

	void* Buffer::mapMemory()
	{
		void* memory = nullptr;
		vmaMapMemory(m_Vma->getHandle(), m_Allocation, &memory);
		return memory;
	}

	void Buffer::unmapMemory()
	{
		vmaUnmapMemory(m_Vma->getHandle(), m_Allocation);
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

		auto result = vmaCreateBuffer(m_Vma->getHandle(), &vkCreateInfo, &allocationCreateInfo, &buffer, &m_Allocation, nullptr);
		if (result == VK_SUCCESS)
			m_Handle = buffer;
	}

	bool Buffer::destroyImpl()
	{
		vmaDestroyBuffer(m_Vma->getHandle(), m_Handle, m_Allocation);
		m_Allocation = nullptr;
		return true;
	}
} // namespace Graphics::Memory