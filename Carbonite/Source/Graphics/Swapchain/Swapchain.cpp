#include "Graphics/Swapchain/Swapchain.h"
#include "Graphics/Device/Surface.h"

namespace Graphics
{
	Swapchain::Swapchain(Memory::VMA& vma)
	    : Handle({ &vma }), m_Vma(&vma)
	{
	}

	Swapchain::~Swapchain()
	{
		if (isCreated())
			destroy();
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

		auto  device       = m_Vma->getDevice();
		auto& deviceHandle = device->getHandle();

		vk::SwapchainCreateInfoKHR createInfo = { {}, device->getSurface()->getHandle(), m_ImageCount, m_Format, m_ColorSpace, { m_Width, m_Height }, m_ImageArrayLayers, m_ImageUsage, imageSharingMode, indices, m_PreTransform, m_CompositeAlpha, m_PresentMode, m_Clipped, m_Handle };

		m_Handle = deviceHandle.createSwapchainKHR(createInfo);

		auto images = deviceHandle.getSwapchainImagesKHR(m_Handle);
		m_Images.reserve(images.size());
		for (std::size_t i = 0; i < images.size(); ++i)
			m_Images.emplace_back(*m_Vma, images[i]);
	}

	bool Swapchain::destroyImpl()
	{
		if (!m_Recreate)
			m_Vma->getDevice()->getHandle().destroySwapchainKHR(m_Handle);
		m_Images.clear();
		return !m_Recreate;
	}
} // namespace Graphics