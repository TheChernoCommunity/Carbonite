#pragma once

#include "Graphics/Common.h"

#include <set>

namespace Graphics::Memory
{
	struct VMA;

	struct Buffer : public Handle<vk::Buffer, true, true>
	{
	public:
		Buffer(VMA& vma);
		~Buffer();

		void* mapMemory();
		void  unmapMemory();

		std::uint64_t getSize() const
		{
			return m_AllocatedSize;
		}

		auto& getVma()
		{
			return m_Vma;
		}
		auto& getVma() const
		{
			return m_Vma;
		}

		auto& getAllocation() const
		{
			return m_Allocation;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		std::uint64_t           m_Size        = 0;
		vk::BufferUsageFlags    m_Usage       = vk::BufferUsageFlagBits::eTransferDst;
		VmaMemoryUsage          m_MemoryUsage = VMA_MEMORY_USAGE_GPU_ONLY;
		std::set<std::uint32_t> m_Indices;

	private:
		std::uint64_t m_AllocatedSize = 0;

		VMA& m_Vma;

		VmaAllocation m_Allocation = {};
	};
} // namespace Graphics::Memory
