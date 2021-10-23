#include "Graphics/Image/Image.h"

namespace Graphics
{
	Image::Image(Device& device)
	    : Handle({ &device }), m_Device(&device)
	{
	}

	Image::Image(Device& device, vk::Image& handle)
	    : Handle({ &device }, handle), m_Device(&device)
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

		vk::ImageCreateInfo createInfo = { {}, m_ImageType, m_Format, { m_Width, m_Height, m_Depth }, m_MipLevels, m_ArrayLevels, m_Samples, m_Tiling, m_Usage, imageSharingMode, indices, m_InitialLayout };

		// TODO(MarcasRealAccount): Use VMA instead to create the image with a buffer attached.
		m_Handle = m_Device->getHandle().createImage(createInfo);
	}

	bool Image::destroyImpl()
	{
		m_Device->getHandle().destroyImage(m_Handle);
		return true;
	}
} // namespace Graphics