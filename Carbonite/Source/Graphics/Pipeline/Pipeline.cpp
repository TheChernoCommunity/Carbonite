#include "PCH.h"

#include <array>

#include "Graphics/Pipeline/Pipeline.h"

namespace Graphics
{
	Pipeline::Pipeline(Swapchain& swapchain, RenderPass& renderPass, std::vector<Shader*>& shaders)
	    : m_swapchain(swapchain), m_device(m_swapchain.getDevice()), m_renderPass(renderPass), m_shaders(shaders)
	{
		for (Shader* shader : m_shaders)
		{
			shader->addChild(this);
		}
	}

	void Pipeline::createImpl()
	{
		std::vector<vk::PipelineShaderStageCreateInfo> shaderStageCreateInfos;

		for (Shader* shader : m_shaders)
		{
			vk::ShaderStageFlagBits shaderStage;

			switch (shader->getType())
			{
			case ShaderType::Vertex:
				shaderStage = vk::ShaderStageFlagBits::eVertex;
				break;

			case ShaderType::Fragment:
				shaderStage = vk::ShaderStageFlagBits::eFragment;
				break;

			default:
				break;
			}

			shaderStageCreateInfos.push_back({ {}, shaderStage, shader->getHandle(), "main" });
		}

		vk::PipelineVertexInputStateCreateInfo   vertexInputInfo; // TODO: actually fill out data when we have vertex buffers
		vk::PipelineInputAssemblyStateCreateInfo inputAssembly = { {}, vk::PrimitiveTopology::eTriangleList, VK_FALSE };

		vk::Viewport viewport = { 0, 0, static_cast<float>(m_swapchain.m_Width), static_cast<float>(m_swapchain.m_Height), 0, 1 };

		// std::array<vk::Viewport, 1> viewports = { viewport };

		vk::PipelineViewportStateCreateInfo viewportState = { {}, 1, &viewport, 1, nullptr };

		vk::PipelineRasterizationStateCreateInfo rasterizer = { {},
			                                                    VK_FALSE,
			                                                    VK_FALSE,
			                                                    vk::PolygonMode::eFill,
			                                                    vk::CullModeFlagBits::eBack,
			                                                    vk::FrontFace::eClockwise,
			                                                    VK_FALSE,
			                                                    0,
			                                                    0,
			                                                    0,
			                                                    1 };

		vk::PipelineMultisampleStateCreateInfo multisampling = { {}, vk::SampleCountFlagBits::e1, VK_FALSE };

		vk::PipelineColorBlendAttachmentState colorBlendAttachment = { VK_TRUE,
			                                                           vk::BlendFactor::eSrcAlpha,
			                                                           vk::BlendFactor::eOneMinusSrcAlpha,
			                                                           vk::BlendOp::eAdd,
			                                                           vk::BlendFactor::eOne,
			                                                           vk::BlendFactor::eZero,
			                                                           vk::BlendOp::eAdd,
			                                                           vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA };

		std::array<vk::PipelineColorBlendAttachmentState, 1> colorBlendAttachments = { colorBlendAttachment };

		vk::PipelineColorBlendStateCreateInfo colorBlending = {
			{},
			VK_FALSE,
			vk::LogicOp::eCopy,
			colorBlendAttachments,
			std::array<float, 4>({ 0, 0, 0, 0 })
		};

		std::array<vk::DynamicState, 3>    dynamicStates          = { vk::DynamicState::eViewport, vk::DynamicState::eScissor, vk::DynamicState::eLineWidth };
		vk::PipelineDynamicStateCreateInfo dynamicStateCreateInfo = { {}, dynamicStates };

		vk::PipelineDepthStencilStateCreateInfo depthStencilStateInfo;

		m_pipelineLayout = m_device->createPipelineLayout(vk::PipelineLayoutCreateInfo());

		vk::GraphicsPipelineCreateInfo createInfo = { {}, shaderStageCreateInfos, &vertexInputInfo, &inputAssembly, nullptr, &viewportState, &rasterizer, &multisampling, &depthStencilStateInfo, &colorBlending, &dynamicStateCreateInfo, m_pipelineLayout, m_renderPass.getHandle(), 0, nullptr, -1 };

		std::array<vk::GraphicsPipelineCreateInfo, 1> createInfos = { createInfo };

		m_Handle = m_device->createGraphicsPipelines(VK_NULL_HANDLE, createInfos).value.front();
	}

	bool Pipeline::destroyImpl()
	{
		m_device->destroy(m_pipelineLayout);
		m_device->destroy(m_Handle);
		return true;
	}

	Pipeline::~Pipeline()
	{
		for (Shader* shader : m_shaders)
		{
			shader->removeChild(this);
		}
	}
} // namespace Graphics
