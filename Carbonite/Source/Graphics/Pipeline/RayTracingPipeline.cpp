#include "RayTracingPipeline.h"
#include "Graphics/Device/Device.h"
#include "PipelineLayout.h"
#include "ShaderModule.h"

namespace Graphics
{
	RayTracingPipeline::RayTracingPipeline(PipelineLayout& pipelineLayout)
	    : m_PipelineLayout(pipelineLayout)
	{
		m_PipelineLayout.addChild(this);
	}

	RayTracingPipeline::~RayTracingPipeline()
	{
		if (isValid())
			destroy();

		m_PipelineLayout.removeChild(this);
	}

	Device& RayTracingPipeline::getDevice()
	{
		return m_PipelineLayout.getDevice();
	}

	Device& RayTracingPipeline::getDevice() const
	{
		return m_PipelineLayout.getDevice();
	}

	void RayTracingPipeline::createImpl()
	{
		std::vector<vk::PipelineShaderStageCreateInfo> shaderStageCreateInfos;
		shaderStageCreateInfos.resize(m_ShaderStages.size());
		for (std::size_t i = 0; i < m_ShaderStages.size(); ++i)
		{
			auto                    shaderStage     = m_ShaderStages[i];
			vk::ShaderStageFlagBits shaderStageType = static_cast<vk::ShaderStageFlagBits>(shaderStage->getCreatedType());

			shaderStageCreateInfos[i] = {
				{},
				shaderStageType,
				shaderStage->getHandle(),
				"main"
			};
		}

		m_UsedLibraries = m_Libraries;
		std::vector<vk::Pipeline> libraries(m_UsedLibraries.size());
		for (std::size_t i = 0; i < m_UsedLibraries.size(); ++i)
			libraries[i] = m_UsedLibraries[i]->getHandle();

		vk::PipelineLibraryCreateInfoKHR libraryInfo = { libraries };

		vk::RayTracingPipelineInterfaceCreateInfoKHR libraryInterface = { m_MaxPipelineRayPayloadSize, m_MaxPipelineRayHitAttributeSize };
		vk::PipelineDynamicStateCreateInfo           dynamicState     = { {}, m_DynamicStates };

		vk::RayTracingPipelineCreateInfoKHR createInfo = {
			{},
			shaderStageCreateInfos,
			m_Groups,
			m_MaxPipelineRayRecursionDepth,
			&libraryInfo,
			&libraryInterface,
			&dynamicState,
			*m_PipelineLayout,
			(m_BasePipeline && m_BasePipeline != this) ? m_BasePipeline->getHandle() : nullptr,
			m_BasePipelineIndex
		};

		Device& device = getDevice();
		m_Handle       = device->createRayTracingPipelineKHR(nullptr, nullptr, createInfo, nullptr, device.getDispatcher()).value;
		for (auto library : m_UsedLibraries)
			library->addChild(this);
	}

	bool RayTracingPipeline::destroyImpl()
	{
		getDevice()->destroyPipeline(m_Handle);
		for (auto library : m_UsedLibraries)
			library->removeChild(this);
		m_UsedLibraries.clear();
		return true;
	}
} // namespace Graphics