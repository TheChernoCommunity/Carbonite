//
//	Created by MarcasRealAccount on 13. May. 2021
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Mesh/Mesh.h"

#include <memory>

namespace gp1::renderer::opengl
{
	struct OpenGLMesh
	{
	public:
		virtual ~OpenGLMesh() = default;

		virtual void Render() = 0;

		uint32_t GetGLRenderMode(ERenderMode mode) const;
	};
} // namespace gp1::renderer::opengl

#endif