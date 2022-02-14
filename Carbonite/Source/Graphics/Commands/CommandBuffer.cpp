#include "CommandBuffer.h"
#include "CommandPool.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Device/Queue.h"
#include "Graphics/Image/Framebuffer.h"
#include "Graphics/Image/Image.h"
#include "Graphics/Memory/Buffer.h"
#include "Graphics/Pipeline/Descriptor/DescriptorSet.h"
#include "Graphics/Pipeline/PipelineLayout.h"
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

	void CommandBuffer::end()
	{
		m_Handle.end();
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

	void CommandBuffer::cmdSetScissors(const std::vector<vk::Rect2D>& scissors)
	{
		m_Handle.setScissor(0, scissors);
	}

	void CommandBuffer::cmdSetViewports(const std::vector<vk::Viewport>& viewports)
	{
		m_Handle.setViewport(0, viewports);
	}

	void CommandBuffer::cmdSetLineWidth(float lineWidth)
	{
		m_Handle.setLineWidth(lineWidth);
	}

	void CommandBuffer::cmdBindPipeline(Pipeline& pipeline)
	{
		m_Handle.bindPipeline(pipeline.getBindPoint(), pipeline.getHandle());
	}

	void CommandBuffer::cmdBindVertexBuffers(std::uint32_t firstBinding, const std::vector<Graphics::Memory::Buffer*>& buffers, const std::vector<vk::DeviceSize>& offsets)
	{
		std::vector<vk::Buffer> buffs;
		buffs.resize(buffers.size());
		for (std::size_t i = 0; i < buffers.size(); ++i)
			buffs[i] = *buffers[i];
		m_Handle.bindVertexBuffers(firstBinding, buffs, offsets);
	}

	void CommandBuffer::cmdBindIndexBuffer(Graphics::Memory::Buffer& buffer, vk::DeviceSize offset, vk::IndexType indexType)
	{
		m_Handle.bindIndexBuffer(buffer, offset, indexType);
	}

	void CommandBuffer::cmdBindDescriptorSets(vk::PipelineBindPoint bindPoint, Graphics::PipelineLayout& layout, std::uint32_t firstSet, const std::vector<DescriptorSet*>& descriptorSets, const std::vector<std::uint32_t>& dynamicOffsets)
	{
		std::vector<vk::DescriptorSet> sets;
		sets.resize(descriptorSets.size());
		for (std::size_t i = 0; i < descriptorSets.size(); ++i)
			sets[i] = *descriptorSets[i];
		m_Handle.bindDescriptorSets(bindPoint, layout, firstSet, sets, dynamicOffsets);
	}

	void CommandBuffer::cmdDraw(std::uint32_t vertexCount, std::uint32_t instanceCount, std::uint32_t firstVertex, std::uint32_t firstInstance)
	{
		m_Handle.draw(vertexCount, instanceCount, firstVertex, firstInstance);
	}

	void CommandBuffer::cmdDrawIndexed(std::uint32_t indexCount, std::uint32_t instanceCount, std::uint32_t firstIndex, std::uint32_t vertexOffset, std::uint32_t firstInstance)
	{
		m_Handle.drawIndexed(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
	}

	void CommandBuffer::cmdCopyBuffer(Memory::Buffer& srcBuffer, Memory::Buffer& dstBuffer, const std::vector<vk::BufferCopy>& regions)
	{
		m_Handle.copyBuffer(srcBuffer, dstBuffer, regions);
	}

	void CommandBuffer::cmdCopyBufferToImage(Memory::Buffer& srcBuffer, Image& dstImage, vk::ImageLayout dstImageLayout, const std::vector<vk::BufferImageCopy>& regions)
	{
		m_Handle.copyBufferToImage(srcBuffer, dstImage, dstImageLayout, regions);
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