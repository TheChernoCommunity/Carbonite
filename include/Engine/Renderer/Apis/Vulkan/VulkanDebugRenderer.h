#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/DebugRenderer.h"

#include <glm.hpp>

namespace gp1::renderer::vulkan
{
	class VulkanDebugRenderer : public DebugRenderer
	{
	public:
		virtual void DrawPoint(const glm::fvec3& position, float duration, const glm::fvec4& color) override;
		virtual void DrawSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color) override;
		virtual void DrawBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color) override;
		virtual void DrawLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color) override;
		
		virtual void Init() override;
		virtual void DeInit() override;
	};
} // namespace gp1::renderer::vulkan
#endif