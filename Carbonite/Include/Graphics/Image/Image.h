#pragma once

#include "Graphics/Memory/VMA.h"

#include <set>

namespace Graphics
{
	struct Image : public Handle<vk::Image>
	{
	public:
		Image(Memory::VMA& vma);
		Image(Memory::VMA& vma, vk::Image& handle);
		~Image();

		auto& getVma()
		{
			return m_Vma;
		}
		auto& getVma() const
		{
			return m_Vma;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		vk::ImageType m_ImageType   = vk::ImageType::e2D;
		std::uint32_t m_Width       = 1;
		std::uint32_t m_Height      = 1;
		std::uint32_t m_Depth       = 1;
		std::uint32_t m_MipLevels   = 1;
		std::uint32_t m_ArrayLevels = 1;

		vk::Format              m_Format        = vk::Format::eR8G8B8A8Srgb;
		vk::SampleCountFlagBits m_Samples       = vk::SampleCountFlagBits::e1;
		vk::ImageTiling         m_Tiling        = vk::ImageTiling::eOptimal;
		vk::ImageUsageFlags     m_Usage         = vk::ImageUsageFlagBits::eTransferDst;
		VmaMemoryUsage          m_MemoryUsage   = VMA_MEMORY_USAGE_GPU_ONLY;
		vk::ImageLayout         m_InitialLayout = vk::ImageLayout::eUndefined;

		std::set<std::uint32_t> m_Indices;

	private:
		Memory::VMA& m_Vma;

		VmaAllocation m_Allocation;
	};
} // namespace Graphics
