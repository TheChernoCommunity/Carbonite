//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Shader/Material.h"
#include "Engine/Renderer/Shader/Uniform.h"
#include "Engine/Renderer/Shader/Shader.h"

#include <glad/glad.h>

namespace gp1 {

	void Material::SetShader(Shader* shader) {
		this->m_Shader = shader;
		for (auto uniform : m_Uniforms)
			delete uniform.second;
		this->m_Uniforms.clear();

		if (this->m_Shader) {
			for (auto uniform : this->m_Shader->m_UniformIds) {
				Uniform* pUniform = nullptr;
				switch (uniform.second.second) {
				case (uint32_t)UniformType::FLOAT:
					pUniform = new UniformFloat(uniform.second.first);
					break;
				case (uint32_t)UniformType::FLOAT_VEC2:
					pUniform = new UniformVec2f(uniform.second.first);
					break;
				case (uint32_t)UniformType::FLOAT_VEC3:
					pUniform = new UniformVec3f(uniform.second.first);
					break;
				case (uint32_t)UniformType::FLOAT_VEC4:
					pUniform = new UniformVec4f(uniform.second.first);
					break;
				case (uint32_t)UniformType::INT:
					pUniform = new UniformInt(uniform.second.first);
					break;
				case (uint32_t)UniformType::INT_VEC2:
					pUniform = new UniformVec2i(uniform.second.first);
					break;
				case (uint32_t)UniformType::INT_VEC3:
					pUniform = new UniformVec3i(uniform.second.first);
					break;
				case (uint32_t)UniformType::INT_VEC4:
					pUniform = new UniformVec4i(uniform.second.first);
					break;
				case (uint32_t)UniformType::UINT:
					pUniform = new UniformUInt(uniform.second.first);
					break;
				case (uint32_t)UniformType::UINT_VEC2:
					pUniform = new UniformVec2u(uniform.second.first);
					break;
				case (uint32_t)UniformType::UINT_VEC3:
					pUniform = new UniformVec3u(uniform.second.first);
					break;
				case (uint32_t)UniformType::UINT_VEC4:
					pUniform = new UniformVec4u(uniform.second.first);
					break;
				case (uint32_t)UniformType::FLOAT_MAT2:
					pUniform = new UniformMat2f(uniform.second.first);
					break;
				case (uint32_t)UniformType::FLOAT_MAT3:
					pUniform = new UniformMat3f(uniform.second.first);
					break;
				case (uint32_t)UniformType::FLOAT_MAT4:
					pUniform = new UniformMat4f(uniform.second.first);
					break;
				}

				if (pUniform) {
					this->m_Uniforms.insert({ uniform.first, pUniform });
				}
			}
		}
	}

	Shader* Material::GetShader() const {
		return this->m_Shader;
	}

	Uniform* Material::GetUniform(std::string id) {
		if (!this->m_Shader)
			return nullptr;

		auto itr = this->m_Uniforms.find(id);
		if (itr != this->m_Uniforms.end())
			return itr->second;
		return nullptr;
	}

	void Material::SetAllUniforms() {
		if (!this->m_Shader)
			return;

		for (auto uniform : m_Uniforms) {
			uint32_t location = uniform.second->m_Location;
			UniformType type = uniform.second->GetType();

			switch (type) {
			case UniformType::FLOAT:
				glUniform1f(location, ((UniformFloat*)uniform.second)->m_Value);
				break;
			case UniformType::FLOAT_VEC2:
			{
				UniformVec2f* pUn = (UniformVec2f*)uniform.second;
				glUniform2f(location, pUn->m_Value.x, pUn->m_Value.y);
				break;
			}
			case UniformType::FLOAT_VEC3:
			{
				UniformVec3f* pUn = (UniformVec3f*)uniform.second;
				glUniform3f(location, pUn->m_Value.x, pUn->m_Value.y, pUn->m_Value.z);
				break;
			}
			case UniformType::FLOAT_VEC4:
			{
				UniformVec4f* pUn = (UniformVec4f*)uniform.second;
				glUniform4f(location, pUn->m_Value.x, pUn->m_Value.y, pUn->m_Value.z, pUn->m_Value.w);
				break;
			}
			case UniformType::INT:
				glUniform1i(location, ((UniformInt*)uniform.second)->m_Value);
				break;
			case UniformType::INT_VEC2:
			{
				UniformVec2i* pUn = (UniformVec2i*)uniform.second;
				glUniform2i(location, pUn->m_Value.x, pUn->m_Value.y);
				break;
			}
			case UniformType::INT_VEC3:
			{
				UniformVec3i* pUn = (UniformVec3i*)uniform.second;
				glUniform3i(location, pUn->m_Value.x, pUn->m_Value.y, pUn->m_Value.z);
				break;
			}
			case UniformType::INT_VEC4:
			{
				UniformVec4i* pUn = (UniformVec4i*)uniform.second;
				glUniform4i(location, pUn->m_Value.x, pUn->m_Value.y, pUn->m_Value.z, pUn->m_Value.w);
				break;
			}
			case UniformType::UINT:
				glUniform1ui(location, ((UniformUInt*)uniform.second)->m_Value);
				break;
			case UniformType::UINT_VEC2:
			{
				UniformVec2u* pUn = (UniformVec2u*)uniform.second;
				glUniform2ui(location, pUn->m_Value.x, pUn->m_Value.y);
				break;
			}
			case UniformType::UINT_VEC3:
			{
				UniformVec3u* pUn = (UniformVec3u*)uniform.second;
				glUniform3ui(location, pUn->m_Value.x, pUn->m_Value.y, pUn->m_Value.z);
				break;
			}
			case UniformType::UINT_VEC4:
			{
				UniformVec4u* pUn = (UniformVec4u*)uniform.second;
				glUniform4ui(location, pUn->m_Value.x, pUn->m_Value.y, pUn->m_Value.z, pUn->m_Value.w);
				break;
			}
			case UniformType::FLOAT_MAT2:
			{
				UniformMat2f* pUn = (UniformMat2f*)uniform.second;
				glUniformMatrix2fv(location, 1, pUn->m_Transpose, (float*)&pUn->m_Value);
				break;
			}
			case UniformType::FLOAT_MAT3:
			{
				UniformMat3f* pUn = (UniformMat3f*)uniform.second;
				glUniformMatrix3fv(location, 1, pUn->m_Transpose, (float*)&pUn->m_Value);
				break;
			}
			case UniformType::FLOAT_MAT4:
			{
				UniformMat4f* pUn = (UniformMat4f*)uniform.second;
				glUniformMatrix4fv(location, 1, pUn->m_Transpose, (float*)&pUn->m_Value);
				break;
			}
			}
		}
	}

} // namespace gp1
