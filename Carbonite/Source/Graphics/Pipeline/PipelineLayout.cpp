#include "PCH.h"

#include "Graphics/Pipeline/PipelineLayout.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Pipeline/DescriptorSetLayout.h"

namespace Graphics
{
	PipelineLayout::PipelineLayout(Device& device)
	    : m_Device(device)
	{
		m_Device.addChild(this);
	}

	PipelineLayout::~PipelineLayout()
	{
		if (isValid())
			destroy();
		m_Device.removeChild(this);
	}

	void PipelineLayout::createImpl()
	{
		std::vector<vk::DescriptorSetLayout> descriptorSetLayouts(m_DescriptorSetLayouts.size());
		m_UsedDescriptorSetLayouts.resize(m_DescriptorSetLayouts.size());
		for (std::size_t i = 0; i < m_DescriptorSetLayouts.size(); ++i)
		{
			auto descriptorSetLayout      = m_DescriptorSetLayouts[i];
			descriptorSetLayouts[i]       = descriptorSetLayout->getHandle();
			m_UsedDescriptorSetLayouts[i] = descriptorSetLayout;
			descriptorSetLayout->addChild(this);
		}

		vk::PipelineLayoutCreateInfo createInfo = { {}, descriptorSetLayouts, m_PushConstantRanges };

		m_Handle = m_Device->createPipelineLayout(createInfo);
	}

	bool PipelineLayout::destroyImpl()
	{
		m_Device->destroyPipelineLayout(m_Handle);
		for (auto descriptorSetLayout : m_UsedDescriptorSetLayouts)
			descriptorSetLayout->removeChild(this);
		m_UsedDescriptorSetLayouts.clear();
		return true;
	}
} // namespace Graphics