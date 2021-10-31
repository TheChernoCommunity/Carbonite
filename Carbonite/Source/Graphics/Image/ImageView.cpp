#include "PCH.h"

#include "Graphics/Device/Device.h"
#include "Graphics/Image/Image.h"
#include "Graphics/Image/ImageView.h"
#include "Graphics/Memory/VMA.h"

namespace Graphics
{
	ImageView::ImageView(Image& image)
	    : m_Image(image)
	{
		m_Image.addChild(this);
	}

	ImageView::~ImageView()
	{
		if (isValid())
			destroy();
		m_Image.removeChild(this);
	}

	void ImageView::createImpl()
	{
		vk::ImageViewCreateInfo createInfo = { {}, *m_Image, m_ViewType, m_Format, m_Components, m_SubresourceRange };

		m_Handle = m_Image.getVma().getDevice()->createImageView(createInfo);
	}

	bool ImageView::destroyImpl()
	{
		m_Image.getVma().getDevice()->destroyImageView(m_Handle);
		return true;
	}
} // namespace Graphics
