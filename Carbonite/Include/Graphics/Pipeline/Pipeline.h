#pragma once

#include <vector>

#include "Graphics/Common.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Shader.h"
#include "Graphics/Swapchain/Swapchain.h"

#include "RenderPass.h"

namespace Graphics
{
	class Pipeline : public Handle<vk::Pipeline, true, false>
	{
	public:
		Pipeline(Swapchain& swapchain, RenderPass& renderPass, std::vector<Shader*>& shaders);
		~Pipeline();

	private:
		Swapchain&            m_swapchain;
		Device&               m_device;
		RenderPass&           m_renderPass;
		std::vector<Shader*>& m_shaders;
		vk::PipelineLayout    m_pipelineLayout;

		virtual void createImpl() override;
		virtual bool destroyImpl() override;
	};

} // namespace Graphics
