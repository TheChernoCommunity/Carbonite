//
//	Created by MarcasRealAccount on 13. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLMesh.h"

#include <glad/glad.h>

namespace gp1::renderer::opengl
{
	uint32_t OpenGLMesh::GetGLRenderMode(ERenderMode mode) const
	{
		switch (mode)
		{
		case ERenderMode::Points: return GL_POINTS;
		case ERenderMode::LineStrip: return GL_LINE_STRIP;
		case ERenderMode::LineLoop: return GL_LINE_LOOP;
		case ERenderMode::Lines: return GL_LINES;
		case ERenderMode::LineStripAdjacency: return GL_LINE_STRIP_ADJACENCY;
		case ERenderMode::LinesAdjacency: return GL_LINES_ADJACENCY;
		case ERenderMode::TriangleStrip: return GL_TRIANGLE_STRIP;
		case ERenderMode::TriangleFan: return GL_TRIANGLE_FAN;
		case ERenderMode::Triangles: return GL_TRIANGLES;
		case ERenderMode::TriangleStripAdjacency: return GL_TRIANGLE_STRIP_ADJACENCY;
		case ERenderMode::TrianglesAdjacency: return GL_TRIANGLES_ADJACENCY;
		case ERenderMode::Patches: return GL_PATCHES;
		default: return 0;
		}
	}
} // namespace gp1::renderer::opengl

#endif