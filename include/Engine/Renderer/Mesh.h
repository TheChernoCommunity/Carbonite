//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once
#include <stdint.h>
#include <vector>

#include <glad/glad.h>

namespace gp1 {

	class Renderer;

	enum class TriangleFace : GLenum {
		BACK = GL_BACK,
		FRONT = GL_FRONT,
		FRONT_AND_BACK = GL_FRONT_AND_BACK
	};

	enum class BlendFunc : GLenum {
		ZERO = GL_ZERO,
		ONE = GL_ONE,
		SRC_COLOR = GL_SRC_COLOR,
		ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
		DST_COLOR = GL_DST_COLOR,
		ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
		SRC_ALPHA = GL_SRC_ALPHA,
		ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
		DST_ALPHA = GL_DST_ALPHA,
		ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
		CONSTANT_COLOR = GL_CONSTANT_COLOR,
		ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
		CONSTANT_ALPHA = GL_CONSTANT_COLOR,
		ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
		SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE,
		SRC1_COLOR = GL_SRC1_COLOR,
		ONE_MINUS_SRC1_COLOR = GL_ONE_MINUS_SRC1_COLOR,
		SRC1_ALPHA = GL_SRC1_ALPHA,
		ONE_MINUS_SRC1_ALPHA = GL_ONE_MINUS_SRC1_ALPHA,
	};

	enum class PolygonMode : GLenum {
		POINT = GL_POINT,
		LINE = GL_LINE,
		FILL = GL_FILL
	};

	struct Vertex {
		struct { float x, y, z; } Position{ 0.0f, 0.0f, 0.0f };	// The position for this vertex.
		struct { float x, y, z; } Normal{ 0.0f, 0.0f, 0.0f };	// The normal for this vertex.
		struct { float x, y; } UV{ 0.0f, 0.0f };				// The uv for this vertex.
	};

	struct Mesh {
	public:
		~Mesh();

		// Mark this mesh dirty for recreation.
		void MarkDirty();

		friend Renderer;

	private:
		// Get this mesh's VAO.
		uint32_t GetVAO();

		// Initialize GL data.
		void InitGLData();
		// Clean up GL data.
		void CleanUpGLData();

	public:
		std::vector<Vertex> m_Vertices;		// This mesh's vertices.
		std::vector<uint32_t> m_Indices;	// This mesh's indices.

	private:
		uint32_t m_VAO = 0;				// This mesh's VAO.
		uint32_t m_VBOs[2]{ 0, 0 };		// This mesh's VBOs.
		uint32_t m_BufferSize = 0;		// This mesh's Buffer Size. (i.e. the number of vertices/indices)

		bool m_HasIndices = false;		// Does this mesh have indices.

		bool m_Dirty = true;			// Should this mesh be recreated.
		bool m_IsDynamic = false;		// Is this mesh dynamic. (i.e. should the vertices and indices be kept after initialization of GL data)

		struct {
			bool m_Enabled = true;						// Is face culling enabled.
			TriangleFace m_Face = TriangleFace::BACK;	// The face to cull.
		} m_CullMode;					// This mesh's cullmode.

		bool m_DepthTest = true;		// Is depth testing enabled.

		struct {
			bool m_Enabled = true;									// Is blending enabled.
			BlendFunc m_SrcFunc = BlendFunc::SRC_ALPHA;				// The blend function's source function.
			BlendFunc m_DstFunc = BlendFunc::ONE_MINUS_SRC_ALPHA;	// The blend function's destination function.
		} m_BlendFunc;					// The mesh's blend function.

		struct {
			bool m_Enabled = true;									// Is polygon mode enabled.
			TriangleFace m_Face = TriangleFace::FRONT_AND_BACK;		// The face to render with this mode.
			PolygonMode m_Mode = PolygonMode::FILL;					// The polygon mode.
		} m_PolygonMode;				// The mesh's polygon mode.
	};

} // namespace gp1
