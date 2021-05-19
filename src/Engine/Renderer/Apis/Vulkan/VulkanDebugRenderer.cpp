#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Apis/Vulkan/VulkanDebugRenderer.h"

namespace gp1::renderer::vulkan
{
	void VulkanDebugRenderer::DrawPoint([[maybe_unused]] const glm::fvec3& position, [[maybe_unused]] float duration, [[maybe_unused]] const glm::fvec4& color)
	{
	}

	void VulkanDebugRenderer::DrawSphere([[maybe_unused]] const glm::fvec3& origin, [[maybe_unused]] float radius, [[maybe_unused]] float duration, [[maybe_unused]] const glm::fvec4& color)
	{
	}

	void VulkanDebugRenderer::DrawBox([[maybe_unused]] const glm::fvec3& origin, [[maybe_unused]] const glm::fvec3& extents, [[maybe_unused]] const glm::fvec3& rotation, [[maybe_unused]] float duration, [[maybe_unused]] const glm::fvec4& color)
	{
	}

	void VulkanDebugRenderer::DrawLine([[maybe_unused]] const glm::fvec3& start, [[maybe_unused]] const glm::fvec3& end, [[maybe_unused]] float duration, [[maybe_unused]] const glm::fvec4& color)
	{
	}

	void VulkanDebugRenderer::Init()
	{
	}

	void VulkanDebugRenderer::DeInit()
	{
	}
} // namespace gp1::renderer::vulkan
#endif