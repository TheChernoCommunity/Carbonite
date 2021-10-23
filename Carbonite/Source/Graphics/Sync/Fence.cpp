#include "Graphics/Sync/Fence.h"

namespace Graphics::Sync
{
	void Fence::ResetFences(const std::vector<Fence*>& fences)
	{
		if (fences.empty())
			return;

		auto device = fences[0]->getDevice();
		for (std::size_t i = 1; i < fences.size(); ++i)
			if (fences[i]->getDevice() != device)
				return;

		std::vector<vk::Fence> fncs(fences.size());
		for (std::size_t i = 0; i < fences.size(); ++i)
			fncs[i] = fences[i]->getHandle();

		device->getHandle().resetFences(fncs);
	}

	void Fence::WaitForFences(const std::vector<Fence*>& fences, bool waitAll, std::uint64_t timeout)
	{
		if (fences.empty())
			return;

		auto device = fences[0]->getDevice();
		for (std::size_t i = 1; i < fences.size(); ++i)
			if (fences[i]->getDevice() != device)
				return;

		std::vector<vk::Fence> fncs(fences.size());
		for (std::size_t i = 0; i < fences.size(); ++i)
			fncs[i] = fences[i]->getHandle();

		[[maybe_unused]] auto result = device->getHandle().waitForFences(fncs, waitAll, timeout);
	}

	Fence::Fence(Device& device)
	    : Handle({ &device }), m_Device(&device)
	{
	}

	Fence::~Fence()
	{
		if (isCreated())
			destroy();
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
		return m_Device->getHandle().getFenceStatus(m_Handle) == vk::Result::eSuccess;
	}

	void Fence::createImpl()
	{
		vk::FenceCreateInfo createInfo = { m_Signaled ? vk::FenceCreateFlagBits::eSignaled : vk::FenceCreateFlags {} };

		m_Handle = m_Device->getHandle().createFence(createInfo);
	}

	bool Fence::destroyImpl()
	{
		m_Device->getHandle().destroyFence(m_Handle);
		return true;
	}
} // namespace Graphics::Sync