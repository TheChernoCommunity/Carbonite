//
//	Created by MarcasRealAccount on 14. May. 2021
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Material/Material.h"

namespace gp1::renderer::vulkan
{
	struct VulkanMaterial : public Material
	{
	};
} // namespace gp1::renderer::vulkan

#endif