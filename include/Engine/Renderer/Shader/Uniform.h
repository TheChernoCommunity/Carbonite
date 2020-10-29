//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once

#include <stdint.h>

#include <glad/glad.h>

namespace gp1 {

	class Material;

	enum class UniformType : uint32_t {
		FLOAT = GL_FLOAT,
		FLOAT_VEC2 = GL_FLOAT_VEC2,
		FLOAT_VEC3 = GL_FLOAT_VEC3,
		FLOAT_VEC4 = GL_FLOAT_VEC4,
		INT = GL_INT,
		INT_VEC2 = GL_INT_VEC2,
		INT_VEC3 = GL_INT_VEC3,
		INT_VEC4 = GL_INT_VEC4,
		UINT = GL_UNSIGNED_INT,
		UINT_VEC2 = GL_UNSIGNED_INT_VEC2,
		UINT_VEC3 = GL_UNSIGNED_INT_VEC3,
		UINT_VEC4 = GL_UNSIGNED_INT_VEC4,
		FLOAT_MAT2 = GL_FLOAT_MAT2,
		FLOAT_MAT3 = GL_FLOAT_MAT3,
		FLOAT_MAT4 = GL_FLOAT_MAT4
	};

	struct Uniform {
	public:
		Uniform(uint32_t location) : m_Location(location) {}
		virtual ~Uniform() {};

		// Get the type of this uniform.
		virtual UniformType GetType() = 0;

		friend Material;

	private:
		uint32_t m_Location;
	};

	struct UniformFloat : public Uniform {
	public:
		UniformFloat(uint32_t location) : Uniform(location) {}
		virtual ~UniformFloat() override {};

		virtual UniformType GetType() override;

		float m_Value = 0.0f;
	};

	struct UniformVec2f : public Uniform {
	public:
		UniformVec2f(uint32_t location) : Uniform(location) {}
		virtual ~UniformVec2f() override {};

		virtual UniformType GetType() override;

		struct { float x, y; } m_Value{ 0.0f, 0.0f };
	};

	struct UniformVec3f : public Uniform {
	public:
		UniformVec3f(uint32_t location) : Uniform(location) {}
		virtual ~UniformVec3f() override {};

		virtual UniformType GetType() override;

		struct { float x, y, z; } m_Value{ 0.0f, 0.0f, 0.0f };
	};

	struct UniformVec4f : public Uniform {
	public:
		UniformVec4f(uint32_t location) : Uniform(location) {}
		virtual ~UniformVec4f() override {};

		virtual UniformType GetType() override;

		struct { float x, y, z, w; } m_Value{ 0.0f, 0.0f, 0.0f, 0.0f };
	};

	struct UniformInt : public Uniform {
	public:
		UniformInt(uint32_t location) : Uniform(location) {}
		virtual ~UniformInt() override {};

		virtual UniformType GetType() override;

		int32_t m_Value = 0;
	};

	struct UniformVec2i : public Uniform {
	public:
		UniformVec2i(uint32_t location) : Uniform(location) {}
		virtual ~UniformVec2i() override {};

		virtual UniformType GetType() override;

		struct { int32_t x, y; } m_Value{ 0, 0 };
	};

	struct UniformVec3i : public Uniform {
	public:
		UniformVec3i(uint32_t location) : Uniform(location) {}
		virtual ~UniformVec3i() override {};

		virtual UniformType GetType() override;

		struct { int32_t x, y, z; } m_Value{ 0, 0, 0 };
	};

	struct UniformVec4i : public Uniform {
	public:
		UniformVec4i(uint32_t location) : Uniform(location) {}
		virtual ~UniformVec4i() override {};

		virtual UniformType GetType() override;

		struct { int32_t x, y, z, w; } m_Value{ 0, 0, 0, 0 };
	};

	struct UniformUInt : public Uniform {
	public:
		UniformUInt(uint32_t location) : Uniform(location) {}
		virtual ~UniformUInt() override {};

		virtual UniformType GetType() override;

		uint32_t m_Value = 0;
	};

	struct UniformVec2u : public Uniform {
	public:
		UniformVec2u(uint32_t location) : Uniform(location) {}
		virtual ~UniformVec2u() override {};

		virtual UniformType GetType() override;

		struct { uint32_t x, y; } m_Value{ 0, 0 };
	};

	struct UniformVec3u : public Uniform {
	public:
		UniformVec3u(uint32_t location) : Uniform(location) {}
		virtual ~UniformVec3u() override {};

		virtual UniformType GetType() override;

		struct { uint32_t x, y, z; } m_Value{ 0, 0, 0 };
	};

	struct UniformVec4u : public Uniform {
	public:
		UniformVec4u(uint32_t location) : Uniform(location) {}
		virtual ~UniformVec4u() override {};

		virtual UniformType GetType() override;

		struct { uint32_t x, y, z, w; } m_Value{ 0, 0, 0, 0 };
	};

	struct UniformMat2f : public Uniform {
	public:
		UniformMat2f(uint32_t location) : Uniform(location) {}
		virtual ~UniformMat2f() override {};

		virtual UniformType GetType() override;

		bool m_Transpose = false;
		struct { float m00, m01, m10, m11; } m_Value{ 1.0f, 0.0f, 0.0f, 1.0f };
	};

	struct UniformMat3f : public Uniform {
	public:
		UniformMat3f(uint32_t location) : Uniform(location) {}
		virtual ~UniformMat3f() override {};

		virtual UniformType GetType() override;

		bool m_Transpose = false;
		struct { float m00, m01, m02, m10, m11, m12, m20, m21, m22; } m_Value{ 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	};

	struct UniformMat4f : public Uniform {
	public:
		UniformMat4f(uint32_t location) : Uniform(location) {}
		virtual ~UniformMat4f() override {};

		virtual UniformType GetType() override;

		bool m_Transpose = false;
		struct { float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33; } m_Value{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	};

} // namespace gp1
