#pragma once

#include "Graphics/Common.h"
#include "Graphics/Pipeline/Pipeline.h"

#include <vector>

namespace Graphics
{
	struct Device;
	struct CommandPool;
	struct RenderPass;
	struct Framebuffer;

	struct CommandBuffer : public Handle<vk::CommandBuffer, false, true>
	{
	public:
		CommandBuffer(CommandPool& pool, vk::CommandBuffer handle, vk::CommandBufferLevel level);
		~CommandBuffer();

		bool begin();
		bool end();

		void cmdBeginRenderPass(RenderPass& renderPass, Framebuffer& framebuffer, vk::Rect2D renderArea, const std::vector<vk::ClearValue>& clearValues);
		void cmdEndRenderPass();

		void cmdSetScissors(const std::vector<vk::Rect2D>& scissors);
		void cmdSetViewports(const std::vector<vk::Viewport>& viewports);
		void cmdSetLineWidth(float lineWidth);

		void cmdBindPipeline(Pipeline& pipeline);
		void cmdDraw(std::uint32_t vertexCount, std::uint32_t instanceCount, std::uint32_t firstVertex, std::uint32_t firstInstance);

		void cmdPipelineBarrier(vk::PipelineStageFlags srcStageMask, vk::PipelineStageFlags dstStageMask, vk::DependencyFlags dependencyFlags, const std::vector<vk::MemoryBarrier>& memoryBarriers, const std::vector<vk::BufferMemoryBarrier>& bufferMemoryBarriers, const std::vector<vk::ImageMemoryBarrier>& imageMemoryBarrier);

		auto getLevel() const
		{
			return m_Level;
		}

		Device& getDevice();
		Device& getDevice() const;
		auto&   getPool()
		{
			return m_Pool;
		}
		auto& getPool() const
		{
			return m_Pool;
		}

	private:
		CommandPool&           m_Pool;
		vk::CommandBufferLevel m_Level;
	};
} // namespace Graphics
