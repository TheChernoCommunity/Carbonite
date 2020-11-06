//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Shader/Material.h"
#include "Engine/Renderer/Shader/Shader.h"

#include <glm.hpp>

namespace gp1 {

	Material::~Material() {
		if (this->m_MaterialData) {
			this->m_MaterialData->CleanUp();
			delete m_MaterialData;
		}
	}

	void Material::SetShader(Shader* shader) {
		this->m_Shader = shader;
		this->m_Uniforms.clear();

		if (this->m_Shader) {
			for (auto uniform : this->m_Shader->m_Uniforms) {
				switch (uniform.second.first) {
				case UniformType::FLOAT:
				{
					Uniform<float> uniformFloat(0.0f);
					this->m_Uniforms.insert({ uniform.first, uniformFloat });
					break;
				}
				case UniformType::FLOAT_VEC2:
				{
					Uniform<glm::fvec2> uniformVec2f({ 0.0f, 0.0f });
					this->m_Uniforms.insert({ uniform.first, uniformVec2f });
					break;
				}
				case UniformType::FLOAT_VEC3:
				{
					Uniform<glm::fvec3> uniformVec3f({ 0.0f, 0.0f, 0.0f });
					this->m_Uniforms.insert({ uniform.first, uniformVec3f });
					break;
				}
				case UniformType::FLOAT_VEC4:
				{
					Uniform<glm::fvec4> uniformVec4f({ 0.0f, 0.0f, 0.0f, 0.0f });
					this->m_Uniforms.insert({ uniform.first, uniformVec4f });
					break;
				}
				case UniformType::INT:
				{
					Uniform<int32_t> uniformInt(0);
					this->m_Uniforms.insert({ uniform.first, uniformInt });
					break;
				}
				case UniformType::INT_VEC2:
				{
					Uniform<glm::ivec2> uniformVec2i({ 0, 0 });
					this->m_Uniforms.insert({ uniform.first, uniformVec2i });
					break;
				}
				case UniformType::INT_VEC3:
				{
					Uniform<glm::ivec3> uniformVec3i({ 0, 0, 0 });
					this->m_Uniforms.insert({ uniform.first, uniformVec3i });
					break;
				}
				case UniformType::INT_VEC4:
				{
					Uniform<glm::ivec4> uniformVec4i({ 0, 0, 0, 0 });
					this->m_Uniforms.insert({ uniform.first, uniformVec4i });
					break;
				}
				case UniformType::UINT:
				{
					Uniform<uint32_t> uniformUInt(0);
					this->m_Uniforms.insert({ uniform.first, uniformUInt });
					break;
				}
				case UniformType::UINT_VEC2:
				{
					Uniform<glm::uvec2> uniformVec2u({ 0, 0 });
					this->m_Uniforms.insert({ uniform.first, uniformVec2u });
					break;
				}
				case UniformType::UINT_VEC3:
				{
					Uniform<glm::uvec3> uniformVec3u({ 0, 0, 0 });
					this->m_Uniforms.insert({ uniform.first, uniformVec3u });
					break;
				}
				case UniformType::UINT_VEC4:
				{
					Uniform<glm::uvec4> uniformVec4u({ 0, 0, 0, 0 });
					this->m_Uniforms.insert({ uniform.first, uniformVec4u });
					break;
				}
				case UniformType::FLOAT_MAT2:
				{
					Uniform<glm::fmat2> uniformMat2f({ 1.0f, 0.0f, 0.0f, 1.0f });
					this->m_Uniforms.insert({ uniform.first, uniformMat2f });
					break;
				}
				case UniformType::FLOAT_MAT3:
				{
					Uniform<glm::fmat3> uniformMat3f({ 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f });
					this->m_Uniforms.insert({ uniform.first, uniformMat3f });
					break;
				}
				case UniformType::FLOAT_MAT4:
				{
					Uniform<glm::fmat4> uniformMat4f({ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f });
					this->m_Uniforms.insert({ uniform.first, uniformMat4f });
					break;
				}
				}
			}
		}
	}

	Shader* Material::GetShader() const {
		return this->m_Shader;
	}

	MaterialData* Material::GetMaterialData(Renderer* renderer) {
		if (!this->m_MaterialData || !renderer->IsMaterialDataUsable(this->m_MaterialData)) {
			if (this->m_MaterialData) {
				this->m_MaterialData->CleanUp();
				delete this->m_MaterialData;
			}
			this->m_MaterialData = CreateCustomMaterialData(renderer);
		}
		return this->m_MaterialData;
	}

	MaterialData* Material::CreateCustomMaterialData(Renderer* renderer) {
		return renderer->CreateMaterialData(this);
	}

	MaterialData::MaterialData(Material* material)
		: m_Material(material) {}

	MaterialData::~MaterialData() {
		if (this->m_Material)
			this->m_Material->m_MaterialData = nullptr;
	}

	const std::unordered_map<std::string, std::any>& MaterialData::GetUniforms() const {
		return this->m_Material->m_Uniforms;
	}

} // namespace gp1
