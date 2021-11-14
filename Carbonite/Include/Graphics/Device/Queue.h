#pragma once

#include "Graphics/Common.h"

#include <vector>

namespace Graphics
{
	namespace Sync
	{
		struct Fence;
		struct Semaphore;
	} // namespace Sync

	struct Swapchain;
	struct Device;
	struct Queue;
	struct CommandBuffer;

	struct QueueFamily : public Handle<void*, false, false>
	{
	public:
		QueueFamily(Device& device, std::uint32_t familyIndex, vk::QueueFlags queueFlags, std::uint32_t timestampValidBits, vk::Extent3D minImageTransferGranularity, bool supportsPresent, std::uint32_t queueCount);
		~QueueFamily();

		auto& getDevice()
		{
			return m_Device;
		}
		auto& getDevice() const
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
		Device& m_Device;

		vk::QueueFlags m_QueueFlags;
		std::uint32_t  m_TimestampValidBits;
		vk::Extent3D   m_MinImageTransferGranularity;
		bool           m_SupportsPresent;

		std::uint32_t      m_FamilyIndex;
		std::vector<Queue> m_Queues;
	};

	struct Queue : public Handle<vk::Queue, false, true>
	{
	public:
		Queue(QueueFamily& queueFamily, std::uint32_t index, vk::Queue handle);
		~Queue();

		bool                    submitCommandBuffers(const std::vector<CommandBuffer*>& commandBuffers, const std::vector<Sync::Semaphore*>& waitSemaphores, const std::vector<Sync::Semaphore*>& signalSemaphores, const std::vector<vk::PipelineStageFlags>& waitDstStageMask, Sync::Fence* fence);
		std::vector<vk::Result> present(const std::vector<Swapchain*>& swapchains, const std::vector<std::uint32_t>& imageIndices, const std::vector<Sync::Semaphore*>& waitSemaphores);
		void                    waitIdle();

		auto getIndex() const
		{
			return m_Index;
		}

		Device& getDevice();
		Device& getDevice() const;
		auto&   getQueueFamily()
		{
			return m_QueueFamily;
		}
		auto& getQueueFamily() const
		{
			return m_QueueFamily;
		}

	private:
		QueueFamily& m_QueueFamily;

		std::uint32_t m_Index;
	};
} // namespace Graphics
