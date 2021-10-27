#include "PCH.h"

#include "Graphics/Device/Surface.h"
#include "Graphics/Memory/VMA.h"
#include "Graphics/Swapchain/Swapchain.h"

namespace Graphics
{
	Swapchain::Swapchain(Memory::VMA& vma)
	    : m_Vma(vma)
	{
		m_Vma.addChild(this);
	}

	Swapchain::~Swapchain()
	{
		if (isValid())
			destroy();
		m_Vma.removeChild(this);
	}

	Image* Swapchain::getImage(std::uint32_t image) const
	{
		return image < m_Images.size() ? const_cast<Image*>(&m_Images[image]) : nullptr;
	}

	void Swapchain::createImpl()
	{
		vk::SharingMode imageSharingMode = vk::SharingMode::eExclusive;

		if (m_Indices.size() > 1)
			imageSharingMode = vk::SharingMode::eConcurrent;

		std::vector<std::uint32_t> indices(m_Indices.begin(), m_Indices.end());

		auto& device = m_Vma.getDevice();

		vk::SwapchainCreateInfoKHR createInfo = { {}, *device.getSurface(), m_ImageCount, m_Format, m_ColorSpace, { m_Width, m_Height }, m_ImageArrayLayers, m_ImageUsage, imageSharingMode, indices, m_PreTransform, m_CompositeAlpha, m_PresentMode, m_Clipped, m_Handle };

		m_Handle = device->createSwapchainKHR(createInfo);

		auto images = device->getSwapchainImagesKHR(m_Handle);
		m_Images.reserve(images.size());
		for (std::size_t i = 0; i < images.size(); ++i)
		{
			auto& image = m_Images.emplace_back(m_Vma, images[i]);
			addChild(&image);
		}
	}

	bool Swapchain::destroyImpl()
	{
		if (!m_Recreate)
			m_Vma.getDevice()->destroySwapchainKHR(m_Handle);
		for (auto& image : m_Images)
			removeChild(&image);
		m_Images.clear();
		return !m_Recreate;
	}
} // namespace Graphics
