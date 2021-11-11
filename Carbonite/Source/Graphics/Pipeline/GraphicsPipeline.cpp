#include "PCH.h"

#include "Graphics/Pipeline/GraphicsPipeline.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Pipeline/PipelineLayout.h"
#include "Graphics/Pipeline/RenderPass.h"
#include "Graphics/Shader.h"

namespace Graphics
{
	GraphicsPipeline::GraphicsPipeline(RenderPass& renderPass, PipelineLayout& pipelineLayout)
	    : m_RenderPass(renderPass), m_PipelineLayout(pipelineLayout)
	{
		m_RenderPass.addChild(this);
		m_PipelineLayout.addChild(this);
	}

	GraphicsPipeline::~GraphicsPipeline()
	{
		if (isValid())
			destroy();

		m_RenderPass.removeChild(this);
		m_PipelineLayout.removeChild(this);
	}

	Device& GraphicsPipeline::getDevice()
	{
		return m_RenderPass.getDevice();
	}

	Device& GraphicsPipeline::getDevice() const
	{
		return m_RenderPass.getDevice();
	}

	void GraphicsPipeline::createImpl()
	{
		m_UsedShaders = m_Shaders;
		std::vector<vk::PipelineShaderStageCreateInfo> shaderStageCreateInfos(m_UsedShaders.size());
		for (std::size_t i = 0; i < m_UsedShaders.size(); ++i)
		{
			auto shader = m_Shaders[i];

			vk::ShaderStageFlagBits shaderStage;

			switch (shader->getType())
			{
			case ShaderType::Vertex:
				shaderStage = vk::ShaderStageFlagBits::eVertex;
				break;
			case ShaderType::TessellationControl:
				shaderStage = vk::ShaderStageFlagBits::eTessellationControl;
				break;
			case ShaderType::TessellationEvaluation:
				shaderStage = vk::ShaderStageFlagBits::eTessellationEvaluation;
				break;
			case ShaderType::Geometry:
				shaderStage = vk::ShaderStageFlagBits::eGeometry;
				break;
			case ShaderType::Fragment:
				shaderStage = vk::ShaderStageFlagBits::eFragment;
				break;
			default:
				return;
			}

			shaderStageCreateInfos[i] = { {}, shaderStage, shader->getHandle(), "main" };
		}

		vk::PipelineVertexInputStateCreateInfo   vertexInputState   = { {}, m_VertexInputState.m_Bindings, m_VertexInputState.m_Attributes };
		vk::PipelineInputAssemblyStateCreateInfo inputAssemblyState = { {}, m_InputAssemblyState.m_Topology, m_InputAssemblyState.m_PrimitiveRestartEnabled };
		vk::PipelineTessellationStateCreateInfo  tessellationState  = { {}, m_TessellationState.m_PatchControlPoints };
		vk::PipelineViewportStateCreateInfo      viewportState      = { {}, m_ViewportState.m_Viewports, m_ViewportState.m_Scissors };
		vk::PipelineRasterizationStateCreateInfo rasterizationState = { {}, m_RasterizationState.m_DepthClampEnabled, m_RasterizationState.m_RasterizerDiscardEnabled, m_RasterizationState.m_PolygonMode, m_RasterizationState.m_CullMode, m_RasterizationState.m_FrontFace, m_RasterizationState.m_DepthBiasEnabled, m_RasterizationState.m_DepthBiasConstantFactor, m_RasterizationState.m_DepthBiasClamp, m_RasterizationState.m_DepthBiasSlopeFactor, m_RasterizationState.m_LineWidth };
		vk::PipelineMultisampleStateCreateInfo   multisampleState   = { {}, m_MultisampleState.m_RasterizationSamples, m_MultisampleState.m_SampleShadingEnabled, m_MultisampleState.m_MinSampleShading, m_MultisampleState.m_SampleMasks.data(), m_MultisampleState.m_AlphaToCoverageEnabled, m_MultisampleState.m_AlphaToOneEnabled };
		vk::PipelineDepthStencilStateCreateInfo  depthStencilState  = { {}, m_DepthStencilState.m_DepthTestEnabled, m_DepthStencilState.m_DepthWriteEnabled, m_DepthStencilState.m_DepthCompareOp, m_DepthStencilState.m_DepthBoundsTestEnabled, m_DepthStencilState.m_StencilTestEnabled, m_DepthStencilState.m_Front, m_DepthStencilState.m_Back, m_DepthStencilState.m_MinDepthBounds, m_DepthStencilState.m_MaxDepthBounds };
		vk::PipelineColorBlendStateCreateInfo    colorBlendState    = { {}, m_ColorBlendState.m_LogicOpEnabled, m_ColorBlendState.m_LogicOp, m_ColorBlendState.m_Attachments, m_ColorBlendState.m_Constants };
		vk::PipelineDynamicStateCreateInfo       dynamicState       = { {}, m_DynamicStates };

		vk::GraphicsPipelineCreateInfo createInfo = { {}, shaderStageCreateInfos, &vertexInputState, &inputAssemblyState, &tessellationState, &viewportState, &rasterizationState, &multisampleState, &depthStencilState, &colorBlendState, &dynamicState, *m_PipelineLayout, *m_RenderPass, 0, (m_BasePipeline && m_BasePipeline != this) ? m_BasePipeline->getHandle() : nullptr, m_BasePipelineIndex };

		m_Handle = getDevice()->createGraphicsPipeline(nullptr, createInfo).value;
		for (auto shader : m_UsedShaders)
			shader->addChild(this);
	}

	bool GraphicsPipeline::destroyImpl()
	{
		getDevice()->destroyPipeline(m_Handle);
		for (auto shader : m_UsedShaders)
			shader->removeChild(this);
		m_UsedShaders.clear();
		return true;
	}
} // namespace Graphics