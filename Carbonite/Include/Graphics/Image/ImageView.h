#pragma once

#include "Graphics/Common.h"

namespace Graphics
{
	struct Image;

	struct ImageView : public Handle<vk::ImageView, true, true>
	{
	public:
		ImageView(Image& image);
		~ImageView();

		auto& getImage()
		{
			return m_Image;
		}
		auto& getImage() const
		{
			return m_Image;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		vk::ImageViewType         m_ViewType         = vk::ImageViewType::e2D;
		vk::Format                m_Format           = vk::Format::eR8G8B8A8Srgb;
		vk::ComponentMapping      m_Components       = { vk::ComponentSwizzle::eIdentity, vk::ComponentSwizzle::eIdentity, vk::ComponentSwizzle::eIdentity, vk::ComponentSwizzle::eIdentity };
		vk::ImageSubresourceRange m_SubresourceRange = { vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 };

	private:
		Image& m_Image;
	};
} // namespace Graphics
