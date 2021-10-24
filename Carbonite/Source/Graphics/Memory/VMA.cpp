#include "Graphics/Memory/VMA.h"

namespace Graphics::Memory
{
	VMA::VMA(Device& device)
	    : Handle({ &device }), m_Device(&device)
	{
	}

	VMA::~VMA()
	{
		if (isCreated())
			destroy();
	}

	void VMA::createImpl()
	{
		auto surface  = m_Device->getSurface();
		auto instance = surface->getInstance();


		VmaAllocatorCreateInfo createInfo = { {}, m_Device->getPhysicalDevice(), m_Device->getHandle(), 0, nullptr, nullptr, 0, nullptr, nullptr, nullptr, instance->getHandle(), instance->getApiVersion(), nullptr };

		VmaAllocator allocator;

		auto result = vmaCreateAllocator(&createInfo, &allocator);
		if (result == VK_SUCCESS)
			m_Handle = allocator;
	}

	bool VMA::destroyImpl()
	{
		vmaDestroyAllocator(m_Handle);
		return true;
	}
} // namespace Graphics::Memory