#pragma once

#include "Graphics/Image/Image.h"
#include "Graphics/Memory/VMA.h"

#include <set>

namespace Graphics
{
	struct Swapchain : public Handle<vk::SwapchainKHR>
	{
	public:
		Swapchain(Memory::VMA& vma);
		~Swapchain();

		auto getVma() const
		{
			return m_Vma;
		}

		Image* getImage(std::uint32_t image) const;
		auto&  getImages()
		{
			return m_Images;
		}
		auto& getImages() const
		{
			return m_Images;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		std::uint32_t m_ImageCount       = 2;
		std::uint32_t m_ImageArrayLayers = 1;

		vk::ImageUsageFlags             m_ImageUsage     = vk::ImageUsageFlagBits::eColorAttachment;
		vk::CompositeAlphaFlagBitsKHR   m_CompositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		vk::SurfaceTransformFlagBitsKHR m_PreTransform   = vk::SurfaceTransformFlagBitsKHR::eIdentity;

		vk::Format         m_Format      = vk::Format::eB8G8R8Srgb;
		vk::ColorSpaceKHR  m_ColorSpace  = vk::ColorSpaceKHR::eSrgbNonlinear;
		vk::PresentModeKHR m_PresentMode = vk::PresentModeKHR::eFifo;

		std::uint32_t m_Width   = 0;
		std::uint32_t m_Height  = 0;
		bool          m_Clipped = true;

		std::set<std::uint32_t> m_Indices;

	private:
		Memory::VMA* m_Vma;

		std::vector<Image> m_Images;
	};
} // namespace Graphics