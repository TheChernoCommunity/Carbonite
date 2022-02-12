#include "DescriptorSetLayout.h"
#include "Graphics/Device/Device.h"

namespace Graphics
{
	DescriptorSetLayout::DescriptorSetLayout(Device& device)
	    : m_Device(device)
	{
		m_Device.addChild(this);
	}

	DescriptorSetLayout::~DescriptorSetLayout()
	{
		if (isValid())
			destroy();
		m_Device.removeChild(this);
	}

	void DescriptorSetLayout::createImpl()
	{
		vk::DescriptorSetLayoutCreateInfo createInfo = { {}, m_Bindings };

		m_Handle = m_Device->createDescriptorSetLayout(createInfo);
	}

	bool DescriptorSetLayout::destroyImpl()
	{
		m_Device->destroyDescriptorSetLayout(m_Handle);
		return true;
	}
} // namespace Graphics