//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once

#include <stdint.h>

#include <glad/glad.h>

namespace gp1 {

	class Material;
	class OpenGLMaterial;

	enum class UniformType : uint32_t {
		FLOAT,
		FLOAT_VEC2,
		FLOAT_VEC3,
		FLOAT_VEC4,
		INT,
		INT_VEC2,
		INT_VEC3,
		INT_VEC4,
		UINT,
		UINT_VEC2,
		UINT_VEC3,
		UINT_VEC4,
		FLOAT_MAT2,
		FLOAT_MAT3,
		FLOAT_MAT4
	};

	template <typename T>
	struct Uniform {
	public:
		Uniform(T defaultValue) : m_Value(defaultValue) {}

		friend Material;
		friend OpenGLMaterial;

	public:
		T m_Value;			// The value of this uniform.
	};

} // namespace gp1
