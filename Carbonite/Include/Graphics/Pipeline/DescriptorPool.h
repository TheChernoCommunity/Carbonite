#pragma once

#include "Graphics/Common.h"

#include <vector>

namespace Graphics
{
	struct Device;
	struct DescriptorSetLayout;
	struct DescriptorSet;

	struct DescriptorPool : public Handle<vk::DescriptorPool, true, true>
	{
	public:
		DescriptorPool(Device& device);
		~DescriptorPool();

		auto& getDevice() { return m_Device; }
		auto& getDevice() const { return m_Device; }
		
		std::vector<DescriptorSet> allocateSets(const std::vector<DescriptorSetLayout*>& descriptorSetLayouts);
		void                       updateDescriptorSets(const std::vector<vk::WriteDescriptorSet>& writes, const std::vector<vk::CopyDescriptorSet>& copies);

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		std::uint32_t m_MaxSets = 4;

		std::vector<vk::DescriptorPoolSize> m_PoolSizes;

	private:
		Device& m_Device;
	};
} // namespace Graphics
