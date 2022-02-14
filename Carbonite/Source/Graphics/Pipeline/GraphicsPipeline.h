#pragma once

#include "Pipeline.h"

#include <vector>

namespace Graphics
{
	struct GraphicsPipelineVertexInputState
	{
	public:
		std::vector<vk::VertexInputBindingDescription>   m_Bindings;
		std::vector<vk::VertexInputAttributeDescription> m_Attributes;
	};

	struct GraphicsPipelineInputAssemblyState
	{
	public:
		vk::PrimitiveTopology m_Topology = vk::PrimitiveTopology::eTriangleList;

		bool m_PrimitiveRestartEnabled = false;
	};

	struct GraphicsPipelineTessellationState
	{
	public:
		std::uint32_t m_PatchControlPoints = 1;
	};

	struct GraphicsPipelineViewportState
	{
	public:
		std::vector<vk::Viewport> m_Viewports;
		std::vector<vk::Rect2D>   m_Scissors;
	};

	struct GraphicsPipelineRasterizationState
	{
	public:
		bool m_DepthClampEnabled        = false;
		bool m_RasterizerDiscardEnabled = false;

		vk::PolygonMode   m_PolygonMode = vk::PolygonMode::eFill;
		vk::CullModeFlags m_CullMode    = vk::CullModeFlagBits::eBack;
		vk::FrontFace     m_FrontFace   = vk::FrontFace::eClockwise;

		bool  m_DepthBiasEnabled        = false;
		float m_DepthBiasConstantFactor = 0.0f;
		float m_DepthBiasClamp          = 0.0f;
		float m_DepthBiasSlopeFactor    = 0.0f;
		float m_LineWidth               = 1.0f;
	};

	struct GraphicsPipelineMultisampleState
	{
	public:
		vk::SampleCountFlagBits m_RasterizationSamples = vk::SampleCountFlagBits::e1;

		bool  m_SampleShadingEnabled   = false;
		float m_MinSampleShading       = 1.0f;
		bool  m_AlphaToCoverageEnabled = false;
		bool  m_AlphaToOneEnabled      = false;

		std::vector<vk::SampleMask> m_SampleMasks;
	};

	struct GraphicsPipelineDepthStencilState
	{
	public:
		bool          m_DepthTestEnabled       = true;
		bool          m_DepthWriteEnabled      = true;
		vk::CompareOp m_DepthCompareOp         = vk::CompareOp::eLess;
		bool          m_DepthBoundsTestEnabled = false;
		bool          m_StencilTestEnabled     = false;

		vk::StencilOpState m_Front = { vk::StencilOp::eKeep, vk::StencilOp::eReplace, vk::StencilOp::eKeep, vk::CompareOp::eLess, ~0U, ~0U, ~0U };
		vk::StencilOpState m_Back  = { vk::StencilOp::eKeep, vk::StencilOp::eReplace, vk::StencilOp::eKeep, vk::CompareOp::eLess, ~0U, ~0U, ~0U };

		float m_MinDepthBounds = 0.0f;
		float m_MaxDepthBounds = 1.0f;
	};

	struct GraphicsPipelineColorBlendState
	{
	public:
		bool        m_LogicOpEnabled = false;
		vk::LogicOp m_LogicOp        = vk::LogicOp::eCopy;

		std::vector<vk::PipelineColorBlendAttachmentState> m_Attachments;

		std::array<float, 4> m_Constants = { 0.0f, 0.0f, 0.0f, 0.0f };
	};

	struct Device;
	struct RenderPass;
	struct PipelineLayout;
	struct ShaderModule;

	struct GraphicsPipeline : public Pipeline
	{
	public:
		GraphicsPipeline(RenderPass& renderPass, PipelineLayout& pipelineLayout);
		~GraphicsPipeline();

		virtual vk::PipelineBindPoint getBindPoint() override { return vk::PipelineBindPoint::eGraphics; }

		Device& getDevice();
		Device& getDevice() const;
		auto&   getRenderPass() { return m_RenderPass; }
		auto&   getRenderPass() const { return m_RenderPass; }
		auto&   getPipelineLayout() { return m_PipelineLayout; }
		auto&   getPipelineLayout() const { return m_PipelineLayout; }

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		GraphicsPipelineVertexInputState   m_VertexInputState;
		GraphicsPipelineInputAssemblyState m_InputAssemblyState;
		GraphicsPipelineTessellationState  m_TessellationState;
		GraphicsPipelineViewportState      m_ViewportState;
		GraphicsPipelineRasterizationState m_RasterizationState;
		GraphicsPipelineMultisampleState   m_MultisampleState;
		GraphicsPipelineDepthStencilState  m_DepthStencilState;
		GraphicsPipelineColorBlendState    m_ColorBlendState;
		std::vector<vk::DynamicState>      m_DynamicStates;

		std::vector<ShaderModule*> m_ShaderStages;

	private:
		RenderPass&     m_RenderPass;
		PipelineLayout& m_PipelineLayout;
	};
} // namespace Graphics
