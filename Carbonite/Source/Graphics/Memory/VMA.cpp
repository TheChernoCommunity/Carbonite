#include "PCH.h"

#include "Graphics/Device/Device.h"
#include "Graphics/Device/Surface.h"
#include "Graphics/Instance.h"
#include "Graphics/Memory/VMA.h"

namespace Graphics::Memory
{
	VMA::VMA(Device& device)
	    : m_Device(device)
	{
		m_Device.addChild(this);
	}

	VMA::~VMA()
	{
		if (isValid())
			destroy();
		m_Device.removeChild(this);
	}

	void VMA::createImpl()
	{
		auto& surface  = m_Device.getSurface();
		auto& instance = surface.getInstance();

		VmaAllocatorCreateInfo createInfo = { {}, m_Device.getPhysicalDevice(), *m_Device, 0, nullptr, nullptr, 0, nullptr, nullptr, nullptr, *instance, instance.getApiVersion(), nullptr };

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
