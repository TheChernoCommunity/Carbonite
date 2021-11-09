#include "PCH.h"

#include "Graphics/Device/Device.h"
#include "Graphics/Device/Queue.h"
#include "Graphics/Commands/CommandPool.h"
#include "Graphics/Sync/Semaphore.h"

namespace Graphics
{
	QueueFamily::QueueFamily(Device& device, std::uint32_t familyIndex, vk::QueueFlags queueFlags, std::uint32_t timestampValidBits, vk::Extent3D minImageTransferGranularity, bool supportsPresent, std::uint32_t queueCount)
	    : Handle(this), m_Device(device), m_QueueFlags(queueFlags), m_TimestampValidBits(timestampValidBits), m_MinImageTransferGranularity(minImageTransferGranularity), m_SupportsPresent(supportsPresent), m_FamilyIndex(familyIndex)
	{
		m_Queues.reserve(queueCount);

		for (std::uint32_t i = 0; i < queueCount; ++i)
			m_Queues.emplace_back(*this, i, device->getQueue(familyIndex, i));

		m_Device.addChild(this);
	}

	QueueFamily::~QueueFamily()
	{
		if (isValid())
			destroy();
		m_Device.removeChild(this);
	}

	Queue* QueueFamily::getQueue(std::uint32_t index) const
	{
		return index < m_Queues.size() ? const_cast<Queue*>(&m_Queues[index]) : nullptr;
	}

	Queue::Queue(QueueFamily& queueFamily, std::uint32_t index, vk::Queue handle)
	    : Handle(handle), m_QueueFamily(queueFamily), m_Index(index)
	{
		m_QueueFamily.addChild(this);
	}

	Queue::~Queue()
	{
		if (isValid())
			destroy();
		m_QueueFamily.removeChild(this);
	}
	
	bool Queue::submitCommandBuffers(const std::vector<CommandBuffer*>& commandBuffers, const std::vector<Semaphore*>& waitSemaphores, const std::vector<Semaphore*>& signalSemaphores, const std::vector<vk::PipelineStageFlags>& waitDstStageMask, vk::Fence fence) {
		
		std::vector<vk::CommandBuffer> vkCommandBuffers(commandBuffers.size());
		for (std::size_t i = 0; i < commandBuffers.size(); ++i)
			vkCommandBuffers[i] = commandBuffers[i]->getHandle();
		std::vector<vk::Semaphore> vkWaitSemaphores(waitSemaphores.size());
		for (std::size_t i = 0; i < waitSemaphores.size(); ++i)
			vkWaitSemaphores[i] = waitSemaphores[i]->getHandle();
		std::vector<vk::Semaphore> vkSignalSemaphores(signalSemaphores.size());
		for (std::size_t i = 0; i < signalSemaphores.size(); ++i)
			vkSignalSemaphores[i] = signalSemaphores[i]->getHandle();
		
		vk::SubmitInfo submit = { vkWaitSemaphores, waitDstStageMask, vkCommandBuffers, vkSignalSemaphores };
		return m_Handle.submit(1, &submit, fence) == vk::Result::eSuccess;
	}
	
	void Queue::waitIdle() {
		m_Handle.waitIdle();
	}
	
	Device& Queue::getDevice() {
		return m_QueueFamily.getDevice();
	}
	
	Device& Queue::getDevice() const {
		return m_QueueFamily.getDevice();
	}
} // namespace Graphics
