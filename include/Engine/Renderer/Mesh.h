//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

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
		struct { float x, y, z; } Position;
		struct { float x, y, z; } Normal;
		struct { float x, y; } UV;
	};

	struct Mesh {
	public:
		void MarkDirty();

		friend Renderer;

	private:
		uint32_t GetVAO();

		void InitGLData();
		void CleanUpGLData();

	public:
		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;

	private:
		uint32_t m_VAO = 0;
		uint32_t m_VBOs[2]{ 0, 0 };
		uint32_t m_BufferSize = 0;

		bool m_HasIndices = false;

		bool m_Dirty = true;
		bool m_IsDynamic = false;

		struct {
			bool m_Enabled = true;
			TriangleFace m_Face = TriangleFace::BACK;
		} m_CullMode;

		bool m_DepthTest = true;

		struct {
			bool m_Enabled = true;
			BlendFunc m_SrcFunc = BlendFunc::SRC_ALPHA;
			BlendFunc m_DstFunc = BlendFunc::ONE_MINUS_SRC_ALPHA;
		} m_BlendFunc;

		struct {
			bool m_Enabled = true;
			TriangleFace m_Face = TriangleFace::FRONT_AND_BACK;
			PolygonMode m_Mode = PolygonMode::FILL;
		} m_PolygonMode;
	};

} // namespace gp1
