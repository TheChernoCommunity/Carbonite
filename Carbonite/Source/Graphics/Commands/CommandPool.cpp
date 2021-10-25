#include "Graphics/Commands/CommandPool.h"
#include "Graphics/Device/Queue.h"

namespace Graphics
{
	CommandBuffer::CommandBuffer(CommandPool& pool, vk::CommandBuffer handle, vk::CommandBufferLevel level)
	    : m_Pool(pool), m_Level(level)
	{
		m_Handle = handle;
		m_Pool.addChild(this);
	}

	CommandBuffer::~CommandBuffer()
	{
		if (isCreated())
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

	CommandPool::CommandPool(Device& device)
	    : m_Device(device)
	{
		m_Device.addChild(this);
	}

	CommandPool::~CommandPool()
	{
		if (isCreated())
			destroy();
		m_Device.removeChild(this);
	}

	void CommandPool::setQueueFamily(QueueFamily& queueFamily)
	{
		m_QueueFamily = &queueFamily;
	}

	void CommandPool::reset()
	{
		m_Device->resetCommandPool(m_Handle);
	}

	std::vector<CommandBuffer*> CommandPool::allocateBuffers(vk::CommandBufferLevel level, std::uint32_t count)
	{
		std::vector<CommandBuffer*> buffers;
		buffers.reserve(count);

		vk::CommandBufferAllocateInfo allocInfo = { m_Handle, level, count };

		std::vector<vk::CommandBuffer> cmdBuffers(count);

		if (m_Device->allocateCommandBuffers(&allocInfo, cmdBuffers.data()) == vk::Result::eSuccess)
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
		if (m_QueueFamily == nullptr)
			return;

		vk::CommandPoolCreateInfo createInfo = { {}, m_QueueFamily->getFamilyIndex() };

		m_Handle = m_Device->createCommandPool(createInfo);
	}

	bool CommandPool::destroyImpl()
	{
		m_Device->destroyCommandPool(m_Handle);

		m_CommandBuffers.clear();
		return true;
	}
} // namespace Graphics
