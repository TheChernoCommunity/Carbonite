#include "PCH.h"

#include "Graphics/Pipeline/DescriptorSet.h"
#include "Graphics/Pipeline/DescriptorPool.h"

namespace Graphics
{
	DescriptorSet::DescriptorSet(DescriptorPool& descriptorPool, vk::DescriptorSet handle)
	    : m_DescriptorPool(descriptorPool), Handle(handle)
	{
		m_DescriptorPool.addChild(this);
	}

	DescriptorSet::~DescriptorSet()
	{
		if (isValid())
			destroy();
		m_DescriptorPool.removeChild(this);
	}
} // namespace Graphics