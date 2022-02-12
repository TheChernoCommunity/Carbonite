#include "Swapchain.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Device/Surface.h"
#include "Graphics/Image/Image.h"
#include "Graphics/Memory/VMA.h"
#include "Graphics/Sync/Fence.h"
#include "Graphics/Sync/Semaphore.h"

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

	vk::Result Swapchain::acquireNextImage(std::uint64_t timeout, Sync::Semaphore* signalSemaphore, Sync::Fence* fence, std::uint32_t& image)
	{
		return getDevice()->acquireNextImageKHR(m_Handle, timeout, signalSemaphore ? signalSemaphore->getHandle() : nullptr, fence ? fence->getHandle() : nullptr, &image);
	}

	Image* Swapchain::getImage(std::uint32_t image) const
	{
		return image < m_Images.size() ? const_cast<Image*>(&m_Images[image]) : nullptr;
	}

	Device& Swapchain::getDevice()
	{
		return m_Vma.getDevice();
	}

	Device& Swapchain::getDevice() const
	{
		return m_Vma.getDevice();
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