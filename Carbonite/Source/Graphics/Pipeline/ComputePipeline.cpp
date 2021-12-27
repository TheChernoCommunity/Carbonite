#include "PCH.h"

#include "ComputePipeline.h"
#include "Graphics/Device/Device.h"
#include "PipelineLayout.h"
#include "ShaderModule.h"

namespace Graphics
{
	ComputePipeline::ComputePipeline(PipelineLayout& pipelineLayout)
	    : m_PipelineLayout(pipelineLayout)
	{
		m_PipelineLayout.addChild(this);
	}

	ComputePipeline::~ComputePipeline()
	{
		if (isValid())
			destroy();

		m_PipelineLayout.removeChild(this);
	}

	Device& ComputePipeline::getDevice()
	{
		return m_PipelineLayout.getDevice();
	}

	Device& ComputePipeline::getDevice() const
	{
		return m_PipelineLayout.getDevice();
	}

	void ComputePipeline::createImpl()
	{
		if (!m_ShaderModule || m_ShaderModule->getCreatedType() != EShaderType::Compute)
			return;

		vk::ComputePipelineCreateInfo createInfo = {
			{},
			{ {}, vk::ShaderStageFlagBits::eCompute, m_ShaderModule->getHandle(), "main" },
			*m_PipelineLayout,
			(m_BasePipeline && m_BasePipeline != this) ? m_BasePipeline->getHandle() : nullptr,
			m_BasePipelineIndex
		};

		m_Handle = getDevice()->createComputePipeline(nullptr, createInfo).value;
	}

	bool ComputePipeline::destroyImpl()
	{
		getDevice()->destroyPipeline(m_Handle);
		return true;
	}
} // namespace Graphics