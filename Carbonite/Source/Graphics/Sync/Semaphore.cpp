#include "Graphics/Sync/Semaphore.h"

namespace Graphics::Sync
{
	void Semaphore::WaitForSemaphores(const std::vector<Semaphore*>& semaphores, std::uint64_t timeout)
	{
		if (semaphores.empty())
			return;

		auto device = semaphores[0]->getDevice();
		for (std::size_t i = 1; i < semaphores.size(); ++i)
			if (semaphores[i]->getDevice() != device)
				return;

		std::vector<vk::Semaphore> semas(semaphores.size());
		for (std::size_t i = 0; i < semaphores.size(); ++i)
			semas[i] = semaphores[i]->getHandle();

		vk::SemaphoreWaitInfo waitInfo = { {}, semas };

		[[maybe_unused]] auto result = device->getHandle().waitSemaphores(waitInfo, timeout);
	}

	Semaphore::Semaphore(Device& device)
	    : m_Device(&device), Handle({ &device })
	{
	}

	Semaphore::~Semaphore()
	{
		if (isCreated())
			destroy();
	}

	void Semaphore::waitFor(std::uint64_t timeout)
	{
		WaitForSemaphores({ this }, timeout);
	}

	std::uint64_t Semaphore::getValue()
	{
		return m_Device->getHandle().getSemaphoreCounterValue(m_Handle);
	}

	void Semaphore::createImpl()
	{
		vk::SemaphoreCreateInfo createInfo = {};

		m_Handle = m_Device->getHandle().createSemaphore(createInfo);
	}

	bool Semaphore::destroyImpl()
	{
		m_Device->getHandle().destroySemaphore(m_Handle);
		return true;
	}
} // namespace Graphics::Sync