#include "DescriptorPool.h"
#include "DescriptorSet.h"
#include "DescriptorSetLayout.h"
#include "Graphics/Device/Device.h"

namespace Graphics
{
	DescriptorPool::DescriptorPool(Device& device)
	    : m_Device(device)
	{
		m_Device.addChild(this);
	}

	DescriptorPool::~DescriptorPool()
	{
		if (isValid())
			destroy();
		m_Device.removeChild(this);
	}

	std::vector<DescriptorSet> DescriptorPool::allocateSets(const std::vector<DescriptorSetLayout*>& descriptorSetLayouts)
	{
		std::vector<vk::DescriptorSetLayout> layouts;
		layouts.resize(descriptorSetLayouts.size());
		for (std::size_t i = 0; i < layouts.size(); ++i)
			layouts[i] = *descriptorSetLayouts[i];

		vk::DescriptorSetAllocateInfo allocateInfo = { m_Handle, layouts };

		auto sets = m_Device->allocateDescriptorSets(allocateInfo);

		std::vector<DescriptorSet> realSets;
		realSets.reserve(sets.size());
		for (std::size_t i = 0; i < sets.size(); ++i)
			realSets.emplace_back(*this, sets[i]);
		return realSets;
	}

	void DescriptorPool::updateDescriptorSets(const std::vector<vk::WriteDescriptorSet>& writes, const std::vector<vk::CopyDescriptorSet>& copies)
	{
		m_Device->updateDescriptorSets(writes, copies);
	}

	void DescriptorPool::createImpl()
	{
		vk::DescriptorPoolCreateInfo createInfo = { {}, m_MaxSets, m_PoolSizes };

		m_Handle = m_Device->createDescriptorPool(createInfo);
	}

	bool DescriptorPool::destroyImpl()
	{
		m_Device->destroyDescriptorPool(m_Handle);
		return true;
	}
} // namespace Graphics