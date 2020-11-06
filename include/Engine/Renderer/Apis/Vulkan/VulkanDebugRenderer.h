//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#pragma once

#include "Engine/Renderer/DebugRenderer.h"

namespace gp1 {

	class VulkanRenderer;

	class VulkanDebugRenderer : public DebugRenderer {
	public:
		VulkanDebugRenderer(Renderer* renderer);

		virtual RendererType GetRendererType() override;

		friend VulkanRenderer;
	private:
		virtual void DebugPoint(const glm::fvec3& point, float duration, const glm::fvec4& color);
		virtual void DebugSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color) override;
		virtual void DebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color) override;
		virtual void DebugLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color) override;

		virtual void Init() override;
		virtual void DeInit() override;
	};

} // namespace gp1
