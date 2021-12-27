#include "PCH.h"

#include "Graphics/Device/Device.h"
#include "ShaderModule.h"

namespace Graphics
{
	ShaderModule::ShaderModule(Device& device)
	    : m_Device(device)
	{
		m_Device.addChild(this);
	}

	ShaderModule::~ShaderModule()
	{
		if (isValid())
			destroy();

		m_Device.removeChild(this);
	}

	void ShaderModule::createImpl()
	{
		vk::ShaderModuleCreateInfo createInfo = { {}, m_Code };

		m_Handle      = m_Device->createShaderModule(createInfo);
		m_CreatedType = m_Type;
	}

	bool ShaderModule::destroyImpl()
	{
		m_Device->destroyShaderModule(m_Handle);
		return true;
	}
} // namespace Graphics
