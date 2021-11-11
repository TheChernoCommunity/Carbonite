#include "PCH.h"

#include "Graphics/Commands/CommandBuffer.h"
#include "Graphics/Commands/CommandPool.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Device/Queue.h"
#include "Graphics/Image/Framebuffer.h"
#include "Graphics/Pipeline/RenderPass.h"

namespace Graphics
{
	CommandBuffer::CommandBuffer(CommandPool& pool, vk::CommandBuffer handle, vk::CommandBufferLevel level)
	    : Handle(handle), m_Pool(pool), m_Level(level)
	{
		m_Pool.addChild(this);
	}

	CommandBuffer::~CommandBuffer()
	{
		if (isValid())
			destroy();
		m_Pool.removeChild(this);
	}

	bool CommandBuffer::begin()
	{
		vk::CommandBufferBeginInfo beginInfo = { {}, nullptr };
		return m_Handle.begin(&beginInfo) == vk::Result::eSuccess;
	}

	bool CommandBuffer::end()
	{
		// INFO(MarcasRealAccount): Had to do an ugly hack here, because vulkan-hpp doesn't have a vk::Result return value for end.
		try
		{
			m_Handle.end();
		}
		catch ([[maybe_unused]] const std::exception& e)
		{
			return false;
		}
		return true;
	}

	void CommandBuffer::cmdBeginRenderPass(RenderPass& renderPass, Framebuffer& framebuffer, vk::Rect2D renderArea, const std::vector<vk::ClearValue>& clearValues)
	{
		vk::RenderPassBeginInfo beginInfo = { *renderPass, *framebuffer, renderArea, clearValues };

		m_Handle.beginRenderPass(beginInfo, vk::SubpassContents::eInline);
	}

	void CommandBuffer::cmdEndRenderPass()
	{
		m_Handle.endRenderPass();
	}

	void CommandBuffer::cmdSetScissor(std::vector<vk::Rect2D>& scissors)
	{
		m_Handle.setScissor(0, scissors);
	}

	void CommandBuffer::cmdSetViewport(std::vector<vk::Viewport>& viewports)
	{
		m_Handle.setViewport(0, viewports);
	}

	void CommandBuffer::cmdBindPipeline(Pipeline& pipeline)
	{
		m_Handle.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline.getHandle());
	}

	void CommandBuffer::draw()
	{
		m_Handle.draw(3, 1, 0, 0);
	}

	void CommandBuffer::cmdPipelineBarrier(vk::PipelineStageFlags srcStageMask, vk::PipelineStageFlags dstStageMask, vk::DependencyFlags dependencyFlags, const std::vector<vk::MemoryBarrier>& memoryBarriers, const std::vector<vk::BufferMemoryBarrier>& bufferMemoryBarriers, const std::vector<vk::ImageMemoryBarrier>& imageMemoryBarrier)
	{
		m_Handle.pipelineBarrier(srcStageMask, dstStageMask, dependencyFlags, memoryBarriers, bufferMemoryBarriers, imageMemoryBarrier);
	}

	Device& CommandBuffer::getDevice()
	{
		return m_Pool.getDevice();
	}

	Device& CommandBuffer::getDevice() const
	{
		return m_Pool.getDevice();
	}
} // namespace Graphics
