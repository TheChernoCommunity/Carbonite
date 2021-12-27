#pragma once

#include "Pipeline.h"

#include <vector>

namespace Graphics
{
	struct Device;
	struct PipelineLayout;
	struct ShaderModule;

	struct RayTracingPipeline : Pipeline
	{
	public:
		RayTracingPipeline(PipelineLayout& pipelineLayout);
		~RayTracingPipeline();

		virtual vk::PipelineBindPoint getBindPoint() override { return vk::PipelineBindPoint::eRayTracingKHR; }

		Device& getDevice();
		Device& getDevice() const;
		auto&   getPipelineLayout() { return m_PipelineLayout; }
		auto&   getPipelineLayout() const { return m_PipelineLayout; }

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		std::uint32_t m_MaxPipelineRayRecursionDepth   = 8;
		std::uint32_t m_MaxPipelineRayPayloadSize      = 1;
		std::uint32_t m_MaxPipelineRayHitAttributeSize = 1;

		std::vector<ShaderModule*> m_ShaderStages;
		std::vector<Pipeline*>     m_Libraries;

		std::vector<vk::RayTracingShaderGroupCreateInfoKHR> m_Groups;

		std::vector<vk::DynamicState> m_DynamicStates;

	private:
		PipelineLayout& m_PipelineLayout;

		std::vector<Pipeline*> m_UsedLibraries;
	};
} // namespace Graphics
