#pragma once

#include "Graphics/Device.h"

namespace Graphics
{
	struct CommandPool;

	struct CommandBuffer : Handle<vk::CommandBuffer, false>
	{
	public:
		CommandBuffer(CommandPool& pool, vk::CommandBuffer handle, vk::CommandBufferLevel level);
		~CommandBuffer();

		bool begin();
		bool end();

		auto getPool() const
		{
			return m_Pool;
		}
		auto getLevel() const
		{
			return m_Level;
		}

	private:
		virtual void createImpl() override {}
		virtual bool destroyImpl() override
		{
			return true;
		}

	private:
		CommandPool*           m_Pool;
		vk::CommandBufferLevel m_Level;
	};

	struct CommandPool : Handle<vk::CommandPool>
	{
	public:
		using CommandBufferLevelListT = std::pair<vk::CommandBufferLevel, std::vector<CommandBuffer>>;
		using CommandBuffersT         = std::vector<CommandBufferLevelListT>;

	public:
		CommandPool(Device& device /*, Queue& queue */);
		~CommandPool();

		void reset();

		std::vector<CommandBuffer*> allocateBuffers(vk::CommandBufferLevel level, std::uint32_t count);

		CommandBuffer*                    getCommandBuffer(vk::CommandBufferLevel level, std::uint32_t index) const;
		std::vector<CommandBuffer>*       getCommandBuffers(vk::CommandBufferLevel level);
		const std::vector<CommandBuffer>* getCommandBuffers(vk::CommandBufferLevel level) const;
		auto&                             getCommandBuffers() const
		{
			return m_CommandBuffers;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	private:
		Device* m_Device;
		/* Queue* m_Queue; */

		CommandBuffersT m_CommandBuffers;
	};
} // namespace Graphics