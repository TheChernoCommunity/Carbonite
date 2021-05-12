#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Mesh/Mesh.h"

namespace gp1::renderer::opengl
{
	struct OpenGLMesh
	{
	public:
		virtual void Render() = 0;

		uint32_t GetGLRenderMode(RenderMode mode) const;
	};
} // namespace gp1::renderer::opengl

#endif