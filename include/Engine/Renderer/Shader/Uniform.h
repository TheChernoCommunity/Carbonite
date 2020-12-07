//
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#pragma once

#include <stdint.h>

namespace gp1::renderer::shader
{
	enum class UniformType : uint32_t
	{
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
		FLOAT_MAT4,
		TEXTURE_2D,
		TEXTURE_2D_ARRAY,
		TEXTURE_3D,
		TEXTURE_CUBE_MAP
	};

	template <typename T>
	struct Uniform
	{
	public:
		Uniform(T defaultValue)
		    : m_Value(defaultValue) {}

	public:
		T m_Value; // The value of this uniform.
	};

} // namespace gp1::renderer::shader
