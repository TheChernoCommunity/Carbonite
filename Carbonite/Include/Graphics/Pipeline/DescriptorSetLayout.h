#pragma once

#include "Graphics/Common.h"

namespace Graphics
{
	struct Device;

	struct DescriptorSetLayout : public Handle<vk::DescriptorSetLayout, true, true>
	{
	public:
		DescriptorSetLayout(Device& device);
		~DescriptorSetLayout();

		auto& getDevice() { return m_Device; }
		auto& getDevice() const { return m_Device; }

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		std::vector<vk::DescriptorSetLayoutBinding> m_Bindings;

	private:
		Device& m_Device;
	};
} // namespace Graphics
