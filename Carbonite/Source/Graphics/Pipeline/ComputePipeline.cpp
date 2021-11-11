#include "PCH.h"

#include "Graphics/Device/Device.h"
#include "Graphics/Pipeline/ComputePipeline.h"
#include "Graphics/Pipeline/PipelineLayout.h"
#include "Graphics/Shader.h"

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
		if (!m_Shader || m_Shader->getType() != ShaderType::Compute)
			return;

		m_UsedShader = m_Shader;

		vk::ComputePipelineCreateInfo createInfo = { {}, { {}, vk::ShaderStageFlagBits::eCompute, m_UsedShader->getHandle(), "main" }, *m_PipelineLayout, (m_BasePipeline && m_BasePipeline != this) ? m_BasePipeline->getHandle() : nullptr, m_BasePipelineIndex };

		m_Handle = getDevice()->createComputePipeline(nullptr, createInfo).value;
		m_UsedShader->addChild(this);
	}

	bool ComputePipeline::destroyImpl()
	{
		getDevice()->destroyPipeline(m_Handle);
		if (m_UsedShader)
		{
			m_UsedShader->removeChild(this);
			m_UsedShader = nullptr;
		}
		return true;
	}
} // namespace Graphics