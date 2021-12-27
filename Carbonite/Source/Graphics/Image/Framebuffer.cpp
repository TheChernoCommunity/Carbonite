#include "PCH.h"

#include "Framebuffer.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Pipeline/RenderPass.h"
#include "ImageView.h"

namespace Graphics
{
	Framebuffer::Framebuffer(RenderPass& renderPass)
	    : m_RenderPass(renderPass)
	{
		m_RenderPass.addChild(this);
	}

	Framebuffer::~Framebuffer()
	{
		if (isValid())
			destroy();
		m_RenderPass.removeChild(this);
	}

	void Framebuffer::createImpl()
	{
		std::vector<vk::ImageView> attachments(m_Attachments.size());
		m_UsedAttachments.resize(attachments.size());
		for (std::size_t i = 0; i < m_Attachments.size(); ++i)
		{
			auto attachment      = m_Attachments[i];
			attachments[i]       = attachment->getHandle();
			m_UsedAttachments[i] = attachment;
			attachment->addChild(this);
		}

		vk::FramebufferCreateInfo createInfo = { {}, *m_RenderPass, attachments, m_Width, m_Height, m_Layers };

		m_Handle = m_RenderPass.getDevice()->createFramebuffer(createInfo);
	}

	bool Framebuffer::destroyImpl()
	{
		m_RenderPass.getDevice()->destroyFramebuffer(m_Handle);
		for (auto attachment : m_UsedAttachments)
			attachment->removeChild(this);
		m_UsedAttachments.clear();
		return true;
	}
} // namespace Graphics
