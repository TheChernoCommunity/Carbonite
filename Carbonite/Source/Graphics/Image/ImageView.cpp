#include "Graphics/Image/ImageView.h"

namespace Graphics
{
	ImageView::ImageView(Image& image)
	    : Handle({ &image }), m_Image(&image)
	{
	}

	ImageView::~ImageView()
	{
		if (isCreated())
			destroy();
	}

	void ImageView::createImpl()
	{
		vk::ImageViewCreateInfo createInfo = { {}, m_Image->getHandle(), m_ViewType, m_Format, m_Components, m_SubresourceRange };

		m_Handle = m_Image->getVma()->getDevice()->getHandle().createImageView(createInfo);
	}

	bool ImageView::destroyImpl()
	{
		m_Image->getVma()->getDevice()->getHandle().destroyImageView(m_Handle);
		return true;
	}
} // namespace Graphics