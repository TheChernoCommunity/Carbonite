#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLMesh.h"

#include <glad/glad.h>

namespace gp1::renderer::opengl
{
	uint32_t OpenGLMesh::GetGLRenderMode(RenderMode mode) const
	{
		switch (mode)
		{
		case RenderMode::POINTS: return GL_POINTS;
		case RenderMode::LINE_STRIP: return GL_LINE_STRIP;
		case RenderMode::LINE_LOOP: return GL_LINE_LOOP;
		case RenderMode::LINES: return GL_LINES;
		case RenderMode::LINE_STRIP_ADJACENCY: return GL_LINE_STRIP_ADJACENCY;
		case RenderMode::LINES_ADJACENCY: return GL_LINES_ADJACENCY;
		case RenderMode::TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
		case RenderMode::TRIANGLE_FAN: return GL_TRIANGLE_FAN;
		case RenderMode::TRIANGLES: return GL_TRIANGLES;
		case RenderMode::TRIANGLE_STRIP_ADJACENCY: return GL_TRIANGLE_STRIP_ADJACENCY;
		case RenderMode::TRIANGLES_ADJACENCY: return GL_TRIANGLES_ADJACENCY;
		case RenderMode::PATCHES: return GL_PATCHES;
		default: return 0;
		}
	}
} // namespace gp1::renderer::opengl

#endif