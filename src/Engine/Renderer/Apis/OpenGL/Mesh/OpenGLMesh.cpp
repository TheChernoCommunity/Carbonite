//
//	Created by MarcasRealAccount on 13. May. 2021
//

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
		case RenderMode::Points: return GL_POINTS;
		case RenderMode::LineStrip: return GL_LINE_STRIP;
		case RenderMode::LineLoop: return GL_LINE_LOOP;
		case RenderMode::Lines: return GL_LINES;
		case RenderMode::LineStripAdjacency: return GL_LINE_STRIP_ADJACENCY;
		case RenderMode::LinesAdjacency: return GL_LINES_ADJACENCY;
		case RenderMode::TriangleStrip: return GL_TRIANGLE_STRIP;
		case RenderMode::TriangleFan: return GL_TRIANGLE_FAN;
		case RenderMode::Triangles: return GL_TRIANGLES;
		case RenderMode::TriangleStripAdjacency: return GL_TRIANGLE_STRIP_ADJACENCY;
		case RenderMode::TrianglesAdjacency: return GL_TRIANGLES_ADJACENCY;
		case RenderMode::Patches: return GL_PATCHES;
		default: return 0;
		}
	}
} // namespace gp1::renderer::opengl

#endif