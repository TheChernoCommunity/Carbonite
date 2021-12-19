#include "PCH.h"

#include "Graphics/Device/Device.h"
#include "Graphics/Pipeline/RenderPass.h"

namespace Graphics
{
	RenderPassAttachment::RenderPassAttachment(vk::Format format, vk::SampleCountFlagBits samples, vk::AttachmentLoadOp loadOp, vk::AttachmentStoreOp storeOp, vk::AttachmentLoadOp stencilLoadOp, vk::AttachmentStoreOp stencilStoreOp, vk::ImageLayout initialLayout, vk::ImageLayout finalLayout)
	    : m_Format(format), m_Samples(samples), m_LoadOp(loadOp), m_StoreOp(storeOp), m_StencilLoadOp(stencilLoadOp), m_StencilStoreOp(stencilStoreOp), m_InitialLayout(initialLayout), m_FinalLayout(finalLayout) {}

	RenderPassAttachmentRef::RenderPassAttachmentRef(std::uint32_t attachment, vk::ImageLayout layout)
	    : m_Attachment(attachment), m_Layout(layout) {}

	RenderPassSubpass::RenderPassSubpass(vk::PipelineBindPoint pipelineBindPoint, const std::vector<RenderPassAttachmentRef>& attachmentRefs, const std::vector<RenderPassAttachmentRef>& colorAttachmentRefs, std::vector<RenderPassAttachmentRef>& resolveAttachmentRefs, const std::vector<std::uint32_t>& preserveAttachments)
	    : m_PipelineBindPoint(pipelineBindPoint), m_AttachmentRefs(attachmentRefs), m_ColorAttachmentRefs(colorAttachmentRefs), m_ResolveAttachmentRefs(resolveAttachmentRefs), m_PreserveAttachments(preserveAttachments) {}

	RenderPassSubpassDependency::RenderPassSubpassDependency(std::uint32_t srcSubpass, std::uint32_t dstSubpass, vk::PipelineStageFlags srcStageMask, vk::PipelineStageFlags dstStageMask, vk::AccessFlags srcAccessMask, vk::AccessFlags dstAccessMask, vk::DependencyFlags dependencyFlags)
	    : m_SrcSubpass(srcSubpass), m_DstSubpass(dstSubpass), m_SrcStageMask(srcStageMask), m_DstStageMask(dstStageMask), m_SrcAccessMask(srcAccessMask), m_DstAccessMask(dstAccessMask), m_DependencyFlags(dependencyFlags) {}

	RenderPass::RenderPass(Device& device)
	    : m_Device(device)
	{
		m_Device.addChild(this);
	}

	RenderPass::~RenderPass()
	{
		if (isValid())
			destroy();
		m_Device.removeChild(this);
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

		m_Handle = m_Device->createRenderPass(createInfo);
	}

	bool RenderPass::destroyImpl()
	{
		m_Device->destroyRenderPass(m_Handle);
		return true;
	}
} // namespace Graphics
