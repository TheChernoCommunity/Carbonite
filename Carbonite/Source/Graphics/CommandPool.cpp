#include "Graphics/CommandPool.h"

namespace Graphics
{
	CommandBuffer::CommandBuffer(CommandPool& pool, vk::CommandBuffer handle, vk::CommandBufferLevel level)
	    : Handle({ &pool }), m_Pool(&pool), m_Level(level)
	{
		m_Handle = handle;
	}

	CommandBuffer::~CommandBuffer()
	{
		if (isCreated())
			destroy();
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

	CommandPool::CommandPool(Device& device /*, Queue& queue */)
	    : Handle({ &device /*, &queue */ }), m_Device(&device) /*, m_Queue(&queue) */
	{
	}

	CommandPool::~CommandPool()
	{
		if (isCreated())
			destroy();
	}

	void CommandPool::reset()
	{
		m_Device->getHandle().resetCommandPool(m_Handle);
	}

	std::vector<CommandBuffer*> CommandPool::allocateBuffers(vk::CommandBufferLevel level, std::uint32_t count)
	{
		std::vector<CommandBuffer*> buffers;
		buffers.reserve(count);

		vk::CommandBufferAllocateInfo allocInfo = { m_Handle, level, count };

		std::vector<vk::CommandBuffer> cmdBuffers(count);

		if (m_Device->getHandle().allocateCommandBuffers(&allocInfo, cmdBuffers.data()) == vk::Result::eSuccess)
		{
			auto commandBuffers = getCommandBuffers(level);
			if (commandBuffers == nullptr)
			{
				m_CommandBuffers.push_back({ level, {} });
				commandBuffers = getCommandBuffers(level);
			}

			for (std::size_t i = 0; i < count; ++i)
				buffers.push_back(&commandBuffers->emplace_back(*this, cmdBuffers[i], level));
		}

		return buffers;
	}

	CommandBuffer* CommandPool::getCommandBuffer(vk::CommandBufferLevel level, std::uint32_t index) const
	{
		auto commandBuffers = getCommandBuffers(level);
		if (!commandBuffers)
			return nullptr;

		return index < commandBuffers->size() ? const_cast<CommandBuffer*>(&(*commandBuffers)[index]) : nullptr;
	}

	std::vector<CommandBuffer>* CommandPool::getCommandBuffers(vk::CommandBufferLevel level)
	{
		for (auto& commandBuffers : m_CommandBuffers)
			if (commandBuffers.first == level)
				return &commandBuffers.second;
		return nullptr;
	}

	const std::vector<CommandBuffer>* CommandPool::getCommandBuffers(vk::CommandBufferLevel level) const
	{
		for (auto& commandBuffers : m_CommandBuffers)
			if (commandBuffers.first == level)
				return &commandBuffers.second;
		return nullptr;
	}

	void CommandPool::createImpl()
	{
		vk::CommandPoolCreateInfo createInfo = { {}, 0 /* queue.getQueueFamily() */ };

		m_Handle = m_Device->getHandle().createCommandPool(createInfo);
	}

	bool CommandPool::destroyImpl()
	{
		m_Device->getHandle().destroyCommandPool(m_Handle);

		m_CommandBuffers.clear();
		return true;
	}
} // namespace Graphics