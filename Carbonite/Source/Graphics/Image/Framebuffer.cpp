#include "Graphics/Image/Framebuffer.h"

namespace Graphics
{
	Framebuffer::Framebuffer(RenderPass& renderPass)
	    : Handle({ &renderPass }), m_RenderPass(&renderPass)
	{
	}

	Framebuffer::~Framebuffer()
	{
		if (isCreated())
			destroy();
	}

	void Framebuffer::createImpl()
	{
		std::vector<vk::ImageView> attachments(m_Attachments.size());
		for (std::size_t i = 0; i < m_Attachments.size(); ++i)
		{
			auto attachment = m_Attachments[i];
			attachments[i]  = attachment->getHandle();
		}

		vk::FramebufferCreateInfo createInfo = { {}, m_RenderPass->getHandle(), attachments, m_Width, m_Height, m_Layers };

		m_Handle = m_RenderPass->getDevice()->getHandle().createFramebuffer(createInfo);
	}

	bool Framebuffer::destroyImpl()
	{
		m_RenderPass->getDevice()->getHandle().destroyFramebuffer(m_Handle);
		return true;
	}
} // namespace Graphics