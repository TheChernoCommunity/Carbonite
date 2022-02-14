#pragma once

#include "Pipeline.h"

namespace Graphics
{
	struct Device;
	struct PipelineLayout;
	struct ShaderModule;

	struct ComputePipeline : public Pipeline
	{
	public:
		ComputePipeline(PipelineLayout& pipelineLayout);
		~ComputePipeline();

		virtual vk::PipelineBindPoint getBindPoint() override { return vk::PipelineBindPoint::eCompute; }

		Device& getDevice();
		Device& getDevice() const;
		auto&   getPipelineLayout() { return m_PipelineLayout; }
		auto&   getPipelineLayout() const { return m_PipelineLayout; }

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		ShaderModule* m_ShaderModule = nullptr;

	private:
		PipelineLayout& m_PipelineLayout;
	};
} // namespace Graphics
