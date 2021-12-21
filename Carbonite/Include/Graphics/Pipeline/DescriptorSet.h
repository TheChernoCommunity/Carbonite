#pragma once

#include "Graphics/Common.h"

#include <vector>

namespace Graphics
{
	struct DescriptorPool;
	struct Device;

	struct DescriptorSet : public Handle<vk::DescriptorSet, false, true>
	{
	public:
		DescriptorSet(DescriptorPool& descriptorPool, vk::DescriptorSet handle);
		~DescriptorSet();

		auto& getDescriptorPool()
		{
			return m_DescriptorPool;
		}
		auto& getDescriptorPool() const
		{
			return m_DescriptorPool;
		}

	private:
		DescriptorPool& m_DescriptorPool;
	};
} // namespace Graphics