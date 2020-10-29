//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Shader/Uniform.h"
#include "Engine/Renderer/Shader/Material.h"

namespace gp1 {

	UniformType UniformFloat::GetType() {
		return UniformType::FLOAT;
	}

	UniformType UniformVec2f::GetType() {
		return UniformType::FLOAT_VEC2;
	}

	UniformType UniformVec3f::GetType() {
		return UniformType::FLOAT_VEC3;
	}

	UniformType UniformVec4f::GetType() {
		return UniformType::FLOAT_VEC4;
	}

	UniformType UniformInt::GetType() {
		return UniformType::INT;
	}

	UniformType UniformVec2i::GetType() {
		return UniformType::INT_VEC2;
	}

	UniformType UniformVec3i::GetType() {
		return UniformType::INT_VEC3;
	}

	UniformType UniformVec4i::GetType() {
		return UniformType::INT_VEC4;
	}

	UniformType UniformUInt::GetType() {
		return UniformType::UINT;
	}

	UniformType UniformVec2u::GetType() {
		return UniformType::UINT_VEC2;
	}

	UniformType UniformVec3u::GetType() {
		return UniformType::UINT_VEC3;
	}

	UniformType UniformVec4u::GetType() {
		return UniformType::UINT_VEC4;
	}

	UniformType UniformMat2f::GetType() {
		return UniformType::FLOAT_MAT2;
	}

	UniformType UniformMat3f::GetType() {
		return UniformType::FLOAT_MAT3;
	}

	UniformType UniformMat4f::GetType() {
		return UniformType::FLOAT_MAT4;
	}

} // namespace gp1
