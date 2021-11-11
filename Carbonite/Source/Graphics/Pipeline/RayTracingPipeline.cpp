#include "PCH.h"

#include "Graphics/Device/Device.h"
#include "Graphics/Pipeline/PipelineLayout.h"
#include "Graphics/Pipeline/RayTracingPipeline.h"
#include "Graphics/Shader.h"

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
		m_UsedShaders = m_Shaders;
		std::vector<vk::PipelineShaderStageCreateInfo> shaderStageCreateInfos(m_UsedShaders.size());
		for (std::size_t i = 0; i < m_UsedShaders.size(); ++i)
		{
			auto shader = m_Shaders[i];

			vk::ShaderStageFlagBits shaderStage;

			switch (shader->getType())
			{
			case ShaderType::RTRayGen:
				shaderStage = vk::ShaderStageFlagBits::eRaygenKHR;
				break;
			case ShaderType::RTAnyHit:
				shaderStage = vk::ShaderStageFlagBits::eAnyHitKHR;
				break;
			case ShaderType::RTClosestHit:
				shaderStage = vk::ShaderStageFlagBits::eClosestHitKHR;
				break;
			case ShaderType::RTMiss:
				shaderStage = vk::ShaderStageFlagBits::eMissKHR;
				break;
			case ShaderType::RTIntersection:
				shaderStage = vk::ShaderStageFlagBits::eIntersectionKHR;
				break;
			case ShaderType::RTCallable:
				shaderStage = vk::ShaderStageFlagBits::eCallableKHR;
				break;
			default:
				return;
			}

			shaderStageCreateInfos[i] = { {}, shaderStage, shader->getHandle(), "main" };
		}

		m_UsedLibraries = m_Libraries;
		std::vector<vk::Pipeline> libraries(m_UsedLibraries.size());
		for (std::size_t i = 0; i < m_UsedLibraries.size(); ++i)
			libraries[i] = m_UsedLibraries[i]->getHandle();

		vk::PipelineLibraryCreateInfoKHR libraryInfo = { libraries };

		vk::RayTracingPipelineInterfaceCreateInfoKHR libraryInterface = { m_MaxPipelineRayPayloadSize, m_MaxPipelineRayHitAttributeSize };
		vk::PipelineDynamicStateCreateInfo           dynamicState     = { {}, m_DynamicStates };

		vk::RayTracingPipelineCreateInfoKHR createInfo = { {}, shaderStageCreateInfos, m_Groups, m_MaxPipelineRayRecursionDepth, &libraryInfo, &libraryInterface, &dynamicState, *m_PipelineLayout, (m_BasePipeline && m_BasePipeline != this) ? m_BasePipeline->getHandle() : nullptr, m_BasePipelineIndex };

		Device& device = getDevice();
		m_Handle       = device->createRayTracingPipelineKHR(nullptr, nullptr, createInfo, nullptr, device.getDispatcher()).value;
		for (auto shader : m_UsedShaders)
			shader->addChild(this);
		for (auto library : m_UsedLibraries)
			library->addChild(this);
	}

	bool RayTracingPipeline::destroyImpl()
	{
		getDevice()->destroyPipeline(m_Handle);
		for (auto shader : m_UsedShaders)
			shader->removeChild(this);
		m_UsedShaders.clear();
		for (auto library : m_UsedLibraries)
			library->removeChild(this);
		m_UsedLibraries.clear();
		return true;
	}
} // namespace Graphics