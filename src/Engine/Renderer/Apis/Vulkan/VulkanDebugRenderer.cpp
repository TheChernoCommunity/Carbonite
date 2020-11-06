//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Renderer/Apis/Vulkan/VulkanDebugRenderer.h"

namespace gp1 {

	VulkanDebugRenderer::VulkanDebugRenderer(Renderer* renderer)
		: DebugRenderer(renderer) {}

	RendererType VulkanDebugRenderer::GetRendererType() {
		return RendererType::VULKAN;
	}

	void VulkanDebugRenderer::DebugPoint(const glm::fvec3& point, float duration, const glm::fvec4& color) {
		_CRT_UNUSED(point);
		_CRT_UNUSED(duration);
		_CRT_UNUSED(color);
	}

	void VulkanDebugRenderer::DebugSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color) {
		_CRT_UNUSED(origin);
		_CRT_UNUSED(radius);
		_CRT_UNUSED(duration);
		_CRT_UNUSED(color);
	}

	void VulkanDebugRenderer::DebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color) {
		_CRT_UNUSED(origin);
		_CRT_UNUSED(extents);
		_CRT_UNUSED(rotation);
		_CRT_UNUSED(duration);
		_CRT_UNUSED(color);
	}

	void VulkanDebugRenderer::DebugLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color) {
		_CRT_UNUSED(start);
		_CRT_UNUSED(end);
		_CRT_UNUSED(duration);
		_CRT_UNUSED(color);
	}

	void VulkanDebugRenderer::Init() {

	}

	void VulkanDebugRenderer::DeInit() {

	}

} // namespace gp1
