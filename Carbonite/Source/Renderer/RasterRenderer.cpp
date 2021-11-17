#include "PCH.h"

#include "Log.h"
#include "Renderer/RasterRenderer.h"

RasterRenderer::RasterRenderer()
    : m_VertexShader(m_Device, { "Assets/test.vert" }),
      m_FragmentShader(m_Device, { "Assets/test.frag" }),
      m_PipelineLayout(m_Device),
      m_Pipeline(m_RenderPass, m_PipelineLayout)
{
}

void RasterRenderer::initImpl()
{
	Log::trace("RasterRenderer init");

	if (!m_VertexShader.create())
		throw std::runtime_error("Failed to create vertex shader");

	if (!m_FragmentShader.create())
		throw std::runtime_error("Failed to create fragment shader");

	if (!m_PipelineLayout.create())
		throw std::runtime_error("Failed to create vulkan pipeline layout");
	m_Device.setDebugName(m_PipelineLayout, "m_PipelineLayout");

	m_Pipeline.m_Shaders.push_back(&m_VertexShader);
	m_Pipeline.m_Shaders.push_back(&m_FragmentShader);

	m_Pipeline.m_ViewportState.m_Viewports = { { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f } };
	m_Pipeline.m_ViewportState.m_Scissors  = { { { 0, 0 }, { 0, 0 } } };

	m_Pipeline.m_ColorBlendState.m_Attachments.emplace_back(true, vk::BlendFactor::eSrcAlpha, vk::BlendFactor::eOneMinusSrcAlpha, vk::BlendOp::eAdd, vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd, vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);

	m_Pipeline.m_DynamicStates.push_back(vk::DynamicState::eViewport);
	m_Pipeline.m_DynamicStates.push_back(vk::DynamicState::eScissor);
	m_Pipeline.m_DynamicStates.push_back(vk::DynamicState::eLineWidth);

	if (!m_Pipeline.create())
		throw std::runtime_error("Failed to create vulkan graphics pipeline");
	m_Device.setDebugName(m_Pipeline, "m_Pipeline");
}

void RasterRenderer::deinitImpl()
{
	Log::trace("RasterRenderer deinit");
}

void RasterRenderer::renderImpl()
{
	auto& currentCommandPool = *getCurrentCommandPool();
	auto& currentCommandBuffer = *currentCommandPool.getCommandBuffer(vk::CommandBufferLevel::ePrimary, 0);
	if (currentCommandBuffer.begin())
	{
		currentCommandBuffer.cmdBeginRenderPass(m_RenderPass, m_Framebuffers[m_CurrentImage], { { 0, 0 }, { m_Swapchain.m_Width, m_Swapchain.m_Height } }, { vk::ClearColorValue(std::array<float, 4> { 0.1f, 0.1f, 0.1f, 1.0f }), vk::ClearDepthStencilValue(1.0f, 0) });

		currentCommandBuffer.cmdSetViewports({ { 0.0f, 0.0f, static_cast<float>(m_Swapchain.m_Width), static_cast<float>(m_Swapchain.m_Height), 0.0f, 1.0f } });
		currentCommandBuffer.cmdSetScissors({ { { 0, 0 }, { m_Swapchain.m_Width, m_Swapchain.m_Height } } });
		currentCommandBuffer.cmdSetLineWidth(1.0f);
		currentCommandBuffer.cmdBindPipeline(m_Pipeline);

		currentCommandBuffer.cmdDraw(3, 1, 0, 0);
		currentCommandBuffer.cmdEndRenderPass();
		currentCommandBuffer.end();
	}
}
