//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Renderer/Apis/Vulkan/VulkanDebugRenderer.h"

namespace gp1::renderer::apis::vulkan::debug
{
	VulkanDebugRenderer::VulkanDebugRenderer(Renderer* renderer)
	    : DebugRenderer(renderer) {}

	RendererType VulkanDebugRenderer::GetRendererType()
	{
		return RendererType::VULKAN;
	}

	void VulkanDebugRenderer::DebugPoint([[maybe_unused]] const glm::fvec3& point, [[maybe_unused]] float duration, [[maybe_unused]] const glm::fvec4& color)
	{
	}

	void VulkanDebugRenderer::DebugSphere([[maybe_unused]] const glm::fvec3& origin, [[maybe_unused]] float radius, [[maybe_unused]] float duration, [[maybe_unused]] const glm::fvec4& color)
	{
	}

	void VulkanDebugRenderer::DebugBox([[maybe_unused]] const glm::fvec3& origin, [[maybe_unused]] const glm::fvec3& extents, [[maybe_unused]] const glm::fvec3& rotation, [[maybe_unused]] float duration, [[maybe_unused]] const glm::fvec4& color)
	{
	}

	void VulkanDebugRenderer::DebugLine([[maybe_unused]] const glm::fvec3& start, [[maybe_unused]] const glm::fvec3& end, [[maybe_unused]] float duration, [[maybe_unused]] const glm::fvec4& color)
	{
	}

	void VulkanDebugRenderer::Init()
	{
	}

	void VulkanDebugRenderer::DeInit()
	{
	}

} // namespace gp1::renderer::apis::vulkan::debug
