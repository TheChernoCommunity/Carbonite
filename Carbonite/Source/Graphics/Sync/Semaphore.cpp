#include "PCH.h"

#include "Graphics/Device/Device.h"
#include "Semaphore.h"

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

		std::vector<vk::Semaphore> semas(semaphores.size());
		for (std::size_t i = 0; i < semaphores.size(); ++i)
			semas[i] = semaphores[i]->getHandle();

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
		WaitForSemaphores({ this }, timeout);
	}

	std::uint64_t Semaphore::getValue()
	{
		return m_Device->getSemaphoreCounterValue(m_Handle);
	}

	void Semaphore::createImpl()
	{
		vk::SemaphoreCreateInfo createInfo = {};

		m_Handle = m_Device->createSemaphore(createInfo);
	}

	bool Semaphore::destroyImpl()
	{
		m_Device->destroySemaphore(m_Handle);
		return true;
	}
} // namespace Graphics::Sync
