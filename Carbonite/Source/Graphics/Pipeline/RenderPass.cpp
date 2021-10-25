#include "Graphics/Pipeline/RenderPass.h"

namespace Graphics
{
	RenderPass::RenderPass(Device& device)
	    : Handle({ &device }), m_Device(&device)
	{
	}

	RenderPass::~RenderPass()
	{
		if (isCreated())
			destroy();
	}

	void RenderPass::createImpl()
	{
		std::vector<vk::AttachmentDescription> attachments(m_Attachments.size());
		for (std::size_t i = 0; i < m_Attachments.size(); ++i)
		{
			auto& attachment = m_Attachments[i];
			attachments[i]   = { {}, attachment.m_Format, attachment.m_Samples, attachment.m_LoadOp, attachment.m_StoreOp, attachment.m_StencilLoadOp, attachment.m_StencilStoreOp, attachment.m_InitialLayout, attachment.m_FinalLayout };
		}

		std::vector<std::vector<vk::AttachmentReference>> subpassesInputAttachments(m_Subpasses.size());
		std::vector<std::vector<vk::AttachmentReference>> subpassesColorAttachments(m_Subpasses.size());
		std::vector<std::vector<vk::AttachmentReference>> subpassesResolveAttachments(m_Subpasses.size());
		std::vector<vk::AttachmentReference>              subpassesDepthStencilAttachment(m_Subpasses.size());
		std::vector<vk::SubpassDescription>               subpasses(m_Subpasses.size());
		for (std::size_t i = 0; i < m_Subpasses.size(); ++i)
		{
			auto& subpass          = m_Subpasses[i];
			auto& inputAttachments = subpassesInputAttachments[i];
			inputAttachments.resize(subpass.m_AttachmentRefs.size());
			for (std::size_t j = 0; j < subpass.m_AttachmentRefs.size(); ++j)
			{
				auto& attachment    = subpass.m_AttachmentRefs[j];
				inputAttachments[j] = { attachment.m_Attachment, attachment.m_Layout };
			}
			auto& colorAttachments = subpassesColorAttachments[i];
			colorAttachments.resize(subpass.m_ColorAttachmentRefs.size());
			for (std::size_t j = 0; j < subpass.m_ColorAttachmentRefs.size(); ++j)
			{
				auto& attachment    = subpass.m_ColorAttachmentRefs[j];
				colorAttachments[j] = { attachment.m_Attachment, attachment.m_Layout };
			}
			auto& resolveAttachments = subpassesResolveAttachments[i];
			resolveAttachments.resize(subpass.m_ResolveAttachmentRefs.size());
			for (std::size_t j = 0; j < subpass.m_ResolveAttachmentRefs.size(); ++j)
			{
				auto& attachment      = subpass.m_ResolveAttachmentRefs[j];
				resolveAttachments[j] = { attachment.m_Attachment, attachment.m_Layout };
			}
			auto& depthStencilAttachment = subpassesDepthStencilAttachment[i];

			subpasses[i] = { {}, subpass.m_PipelineBindPoint, inputAttachments, colorAttachments, resolveAttachments, nullptr, subpass.m_PreserveAttachments };
			if (subpass.m_UseDepthStencilAttachment)
			{
				auto& attachment       = subpass.m_DepthStencilAttachment;
				depthStencilAttachment = { attachment.m_Attachment, attachment.m_Layout };

				subpasses[i].pDepthStencilAttachment = &depthStencilAttachment;
			}
		}

		std::vector<vk::SubpassDependency> dependencies(m_Dependencies.size());
		for (std::size_t i = 0; i < m_Dependencies.size(); ++i)
		{
			auto& dependency = m_Dependencies[i];

			dependencies[i] = { dependency.m_SrcSubpass, dependency.m_DstSubpass, dependency.m_SrcStageMask, dependency.m_DstStageMask, dependency.m_SrcAccessMask, dependency.m_DstAccessMask, dependency.m_DependencyFlags };
		}

		vk::RenderPassCreateInfo createInfo = { {}, attachments, subpasses, dependencies };

		m_Handle = m_Device->getHandle().createRenderPass(createInfo);
	}

	bool RenderPass::destroyImpl()
	{
		m_Device->getHandle().destroyRenderPass(m_Handle);
		return true;
	}
} // namespace Graphics