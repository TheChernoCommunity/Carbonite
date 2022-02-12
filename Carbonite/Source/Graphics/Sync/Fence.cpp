#include "Fence.h"
#include "Graphics/Device/Device.h"

namespace Graphics::Sync
{
	void Fence::ResetFences(const std::vector<Fence*>& fences)
	{
		if (fences.empty())
			return;

		auto& device = fences[0]->getDevice();
		for (std::size_t i = 1; i < fences.size(); ++i)
			if (&fences[i]->getDevice() != &device)
				return;

		std::vector<vk::Fence> fncs(fences.size());
		for (std::size_t i = 0; i < fences.size(); ++i)
			fncs[i] = fences[i]->getHandle();

		device->resetFences(fncs);
	}

	void Fence::WaitForFences(const std::vector<Fence*>& fences, bool waitAll, std::uint64_t timeout)
	{
		if (fences.empty())
			return;

		auto& device = fences[0]->getDevice();
		for (std::size_t i = 1; i < fences.size(); ++i)
			if (&fences[i]->getDevice() != &device)
				return;

		std::vector<vk::Fence> fncs(fences.size());
		for (std::size_t i = 0; i < fences.size(); ++i)
			fncs[i] = fences[i]->getHandle();

		[[maybe_unused]] auto result = device->waitForFences(fncs, waitAll, timeout);
	}

	Fence::Fence(Device& device)
	    : m_Device(device)
	{
		m_Device.addChild(this);
	}

	Fence::~Fence()
	{
		if (isValid())
			destroy();
		m_Device.removeChild(this);
	}

	void Fence::reset()
	{
		ResetFences({ this });
	}

	void Fence::waitFor(std::uint64_t timeout)
	{
		WaitForFences({ this }, true, timeout);
	}

	bool Fence::getState()
	{
		return m_Device->getFenceStatus(m_Handle) == vk::Result::eSuccess;
	}

	void Fence::createImpl()
	{
		vk::FenceCreateInfo createInfo = { m_Signaled ? vk::FenceCreateFlagBits::eSignaled : vk::FenceCreateFlags {} };

		m_Handle = m_Device->createFence(createInfo);
	}

	bool Fence::destroyImpl()
	{
		m_Device->destroyFence(m_Handle);
		return true;
	}
} // namespace Graphics::Sync