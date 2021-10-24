#pragma once

#include "Device.h"

namespace Graphics
{
	struct Queue;

	struct QueueFamily
	{
	public:
		QueueFamily(Device& device, std::uint32_t familyIndex, vk::QueueFlags queueFlags, std::uint32_t timestampValidBits, vk::Extent3D minImageTransferGranularity, bool supportsPresent, std::uint32_t queueCount);

		auto getDevice() const
		{
			return m_Device;
		}

		auto getQueueFlags() const
		{
			return m_QueueFlags;
		}
		auto getTimestampValidBits() const
		{
			return m_TimestampValidBits;
		}
		auto& getMinImageTransferGranularity() const
		{
			return m_MinImageTransferGranularity;
		}
		auto isPresentSupported() const
		{
			return m_SupportsPresent;
		}

		auto getFamilyIndex() const
		{
			return m_FamilyIndex;
		}

		Queue* getQueue(std::uint32_t index) const;
		auto&  getQueues() const
		{
			return m_Queues;
		}

	private:
		Device* m_Device;

		vk::QueueFlags m_QueueFlags;
		std::uint32_t  m_TimestampValidBits;
		vk::Extent3D   m_MinImageTransferGranularity;
		bool           m_SupportsPresent;

		std::uint32_t      m_FamilyIndex;
		std::vector<Queue> m_Queues;
	};

	struct Queue : public Handle<vk::Queue, false>
	{
	public:
		Queue(QueueFamily& queueFamily, std::uint32_t index, vk::Queue handle);
		~Queue();

		auto getQueueFamily() const
		{
			return m_QueueFamily;
		}

		auto getIndex() const
		{
			return m_Index;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	private:
		QueueFamily* m_QueueFamily;

		std::uint32_t m_Index;
	};
} // namespace Graphics
