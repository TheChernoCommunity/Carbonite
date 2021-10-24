#include "Graphics/Device/Queue.h"

namespace Graphics
{
	QueueFamily::QueueFamily(Device& device, std::uint32_t familyIndex, vk::QueueFlags queueFlags, std::uint32_t timestampValidBits, vk::Extent3D minImageTransferGranularity, bool supportsPresent, std::uint32_t queueCount)
	    : m_Device(&device), m_QueueFlags(queueFlags), m_TimestampValidBits(timestampValidBits), m_MinImageTransferGranularity(minImageTransferGranularity), m_SupportsPresent(supportsPresent), m_FamilyIndex(familyIndex)
	{
		m_Queues.reserve(queueCount);

		for (std::uint32_t i = 0; i < queueCount; ++i)
			m_Queues.emplace_back(*this, i, device.getHandle().getQueue(familyIndex, i));
	}

	Queue* QueueFamily::getQueue(std::uint32_t index) const
	{
		return index < m_Queues.size() ? const_cast<Queue*>(&m_Queues[index]) : nullptr;
	}

	Queue::Queue(QueueFamily& queueFamily, std::uint32_t index, vk::Queue handle)
	    : Handle({ queueFamily.getDevice() }, handle), m_QueueFamily(&queueFamily), m_Index(index)
	{
	}

	Queue::~Queue()
	{
		if (isCreated())
			destroy();
	}

	void Queue::createImpl()
	{
	}

	bool Queue::destroyImpl()
	{
		return true;
	}
} // namespace Graphics