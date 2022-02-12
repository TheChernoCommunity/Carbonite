#include "Semaphore.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Instance.h"

namespace Graphics::Sync
{
	void Semaphore::WaitForSemaphores(const std::vector<Semaphore*>& semaphores, std::uint64_t timeout)
	{
		if (semaphores.empty())
			return;

		auto& device = semaphores[0]->getDevice();
		for (std::size_t i = 1; i < semaphores.size(); ++i)
			if (&semaphores[i]->getDevice() != &device)
				return;

		std::vector<vk::Semaphore> semas;
		semas.reserve(semaphores.size());
		for (std::size_t i = 0; i < semaphores.size(); ++i)
			if (semaphores[i]->m_CreatedType == vk::SemaphoreType::eTimeline)
				semas.emplace_back(semaphores[i]->getHandle());

		vk::SemaphoreWaitInfo waitInfo = { {}, semas };

		[[maybe_unused]] auto result = device->waitSemaphores(waitInfo, timeout, device.getDispatcher());
	}

	Semaphore::Semaphore(Device& device)
	    : m_Device(device)
	{
		m_Device.addChild(this);
	}

	Semaphore::~Semaphore()
	{
		if (isValid())
			destroy();
		m_Device.removeChild(this);
	}

	void Semaphore::waitFor(std::uint64_t timeout)
	{
		if (m_CreatedType == vk::SemaphoreType::eTimeline)
			WaitForSemaphores({ this }, timeout);
	}

	std::uint64_t Semaphore::getValue()
	{
		if (m_CreatedType == vk::SemaphoreType::eTimeline)
			return m_Device->getSemaphoreCounterValue(m_Handle, m_Device.getDispatcher());
		return 0;
	}

	void Semaphore::createImpl()
	{
		bool supportsTimelineSemaphores = m_Device.getInstance().getApiVersion() > Version { 0, 1, 2, 0 } || m_Device.getExtensionVersion("VK_KHR_timeline_semaphores");

		vk::SemaphoreCreateInfo createInfo = {};

		vk::SemaphoreTypeCreateInfoKHR typeCreateInfo = { m_Type, m_InitialValue };
		if (supportsTimelineSemaphores)
			createInfo.pNext = &typeCreateInfo;

		m_Handle = m_Device->createSemaphore(createInfo);

		if (supportsTimelineSemaphores)
			m_CreatedType = m_Type;
	}

	bool Semaphore::destroyImpl()
	{
		m_Device->destroySemaphore(m_Handle);
		return true;
	}
} // namespace Graphics::Sync