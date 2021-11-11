#pragma once

#include "Graphics/Common.h"

namespace Graphics
{
	class Pipeline : public Handle<vk::Pipeline, true, false>
	{
	public:
		virtual vk::PipelineBindPoint getBindPoint() = 0;

	public:
		Pipeline*    m_BasePipeline      = nullptr;
		std::int32_t m_BasePipelineIndex = -1;
	};
} // namespace Graphics
