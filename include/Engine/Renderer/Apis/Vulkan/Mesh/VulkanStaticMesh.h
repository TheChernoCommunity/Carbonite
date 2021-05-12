#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Mesh/StaticMesh.h"

namespace gp1::renderer::vulkan
{
	struct VulkanStaticMesh : public StaticMesh
	{
	};
} // namespace gp1::renderer::vulkan

#endif