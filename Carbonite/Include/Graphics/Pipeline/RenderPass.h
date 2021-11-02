#pragma once

#include "Graphics/Common.h"

#include <vector>

namespace Graphics
{
	struct RenderPassAttachment
	{
	public:
		vk::Format              m_Format         = vk::Format::eB8G8R8A8Srgb;
		vk::SampleCountFlagBits m_Samples        = vk::SampleCountFlagBits::e1;
		vk::AttachmentLoadOp    m_LoadOp         = vk::AttachmentLoadOp::eClear;
		vk::AttachmentStoreOp   m_StoreOp        = vk::AttachmentStoreOp::eStore;
		vk::AttachmentLoadOp    m_StencilLoadOp  = vk::AttachmentLoadOp::eDontCare;
		vk::AttachmentStoreOp   m_StencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		vk::ImageLayout         m_InitialLayout  = vk::ImageLayout::eUndefined;
		vk::ImageLayout         m_FinalLayout    = vk::ImageLayout::ePresentSrcKHR;
	};

	struct RenderPassAttachmentRef
	{
	public:
		std::uint32_t   m_Attachment = 0;
		vk::ImageLayout m_Layout     = vk::ImageLayout::eColorAttachmentOptimal;
	};

	struct RenderPassSubpass
	{
	public:
		vk::PipelineBindPoint                m_PipelineBindPoint = vk::PipelineBindPoint::eGraphics;
		std::vector<RenderPassAttachmentRef> m_AttachmentRefs;
		std::vector<RenderPassAttachmentRef> m_ColorAttachmentRefs;
		std::vector<RenderPassAttachmentRef> m_ResolveAttachmentRefs;
		std::vector<std::uint32_t>           m_PreserveAttachments;

		bool                    m_UseDepthStencilAttachment = false;
		RenderPassAttachmentRef m_DepthStencilAttachment;
	};

	struct RenderPassSubpassDependency
	{
	public:
		std::uint32_t          m_SrcSubpass    = 0;
		std::uint32_t          m_DstSubpass    = 0;
		vk::PipelineStageFlags m_SrcStageMask  = vk::PipelineStageFlagBits::eNoneKHR;
		vk::PipelineStageFlags m_DstStageMask  = vk::PipelineStageFlagBits::eNoneKHR;
		vk::AccessFlags        m_SrcAccessMask = vk::AccessFlagBits::eNoneKHR;
		vk::AccessFlags        m_DstAccessMask = vk::AccessFlagBits::eNoneKHR;
		vk::DependencyFlags    m_DependencyFlags;
	};

	struct Device;

	struct RenderPass : public Handle<vk::RenderPass, true, true>
	{
	public:
		RenderPass(Device& device);
		~RenderPass();

		auto& getDevice()
		{
			return m_Device;
		}
		auto& getDevice() const
		{
			return m_Device;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		std::vector<RenderPassAttachment>        m_Attachments;
		std::vector<RenderPassSubpass>           m_Subpasses;
		std::vector<RenderPassSubpassDependency> m_Dependencies;

	private:
		Device& m_Device;
	};
} // namespace Graphics
