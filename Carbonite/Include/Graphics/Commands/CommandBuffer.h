#pragma once

#include "Graphics/Common.h"

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
		
		void cmdPipelineBarrier(vk::PipelineStageFlags srcStageMask, vk::PipelineStageFlags dstStageMask, vk::DependencyFlags dependencyFlags, const std::vector<vk::MemoryBarrier>& memoryBarriers, const std::vector<vk::BufferMemoryBarrier>& bufferMemoryBarriers, const std::vector<vk::ImageMemoryBarrier>& imageMemoryBarrier);
		
		auto getLevel() const
		{
			return m_Level;
		}

		Device& getDevice();
		Device& getDevice() const;
		auto& getPool()
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
}
