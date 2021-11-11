#pragma once

#include "Graphics/Common.h"

#include <vector>

namespace Graphics
{
	struct Device;
	struct DescriptorSetLayout;

	struct PipelineLayout : public Handle<vk::PipelineLayout, true, true>
	{
	public:
		PipelineLayout(Device& device);
		~PipelineLayout();

		auto& getDevice()
		{
			return m_Device;
		}
		auto& getDevice() const
		{
			return m_Device;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		std::vector<DescriptorSetLayout*>  m_DescriptorSetLayouts;
		std::vector<vk::PushConstantRange> m_PushConstantRanges;

	private:
		Device& m_Device;

		std::vector<DescriptorSetLayout*> m_UsedDescriptorSetLayouts;
	};
} // namespace Graphics