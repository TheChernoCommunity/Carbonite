#pragma once

#include "Graphics/Common.h"

namespace Graphics
{
	struct Device;
	struct CommandPool;

	struct CommandBuffer : public Handle<vk::CommandBuffer, false, true>
	{
	public:
		CommandBuffer(CommandPool& pool, vk::CommandBuffer handle, vk::CommandBufferLevel level);
		~CommandBuffer();

		bool begin();
		bool end();

		auto& getPool()
		{
			return m_Pool;
		}
		auto& getPool() const
		{
			return m_Pool;
		}
		auto getLevel() const
		{
			return m_Level;
		}

	private:
		CommandPool&           m_Pool;
		vk::CommandBufferLevel m_Level;
	};

	struct CommandPool : public Handle<vk::CommandPool, true, true>
	{
	public:
		using CommandBufferLevelListT = std::pair<vk::CommandBufferLevel, std::vector<CommandBuffer>>;
		using CommandBuffersT         = std::vector<CommandBufferLevelListT>;

	public:
		CommandPool(Device& device);
		~CommandPool();

		void setQueueFamily(QueueFamily& queueFamily);
		auto getQueueFamily() const
		{
			return m_QueueFamily;
		}

		void reset();

		std::vector<CommandBuffer*> allocateBuffers(vk::CommandBufferLevel level, std::uint32_t count);

		CommandBuffer*                    getCommandBuffer(vk::CommandBufferLevel level, std::uint32_t index) const;
		std::vector<CommandBuffer>*       getCommandBuffers(vk::CommandBufferLevel level);
		const std::vector<CommandBuffer>* getCommandBuffers(vk::CommandBufferLevel level) const;
		auto&                             getCommandBuffers() const
		{
			return m_CommandBuffers;
		}

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

	protected:
		QueueFamily* m_QueueFamily = nullptr;

	private:
		Device& m_Device;

		CommandBuffersT m_CommandBuffers;
	};
} // namespace Graphics
