//
//	Created by MarcasRealAccount on 14. May. 2021
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Shader/ShaderProgram.h"

namespace gp1::renderer::vulkan
{
	struct VulkanShaderProgram : public ShaderProgram
	{
	};
} // namespace gp1::renderer::vulkan

#endif