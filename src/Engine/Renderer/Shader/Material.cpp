//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Shader/Material.h"
#include "Engine/Renderer/Shader/Shader.h"

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
					Uniform<Vec2f> uniformVec2f({ 0.0f, 0.0f });
					this->m_Uniforms.insert({ uniform.first, uniformVec2f });
					break;
				}
				case UniformType::FLOAT_VEC3:
				{
					Uniform<Vec3f> uniformVec3f({ 0.0f, 0.0f, 0.0f });
					this->m_Uniforms.insert({ uniform.first, uniformVec3f });
					break;
				}
				case UniformType::FLOAT_VEC4:
				{
					Uniform<Vec4f> uniformVec4f({ 0.0f, 0.0f, 0.0f, 0.0f });
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
					Uniform<Vec2i> uniformVec2i({ 0, 0 });
					this->m_Uniforms.insert({ uniform.first, uniformVec2i });
					break;
				}
				case UniformType::INT_VEC3:
				{
					Uniform<Vec3i> uniformVec3i({ 0, 0, 0 });
					this->m_Uniforms.insert({ uniform.first, uniformVec3i });
					break;
				}
				case UniformType::INT_VEC4:
				{
					Uniform<Vec4i> uniformVec4i({ 0, 0, 0, 0 });
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
					Uniform<Vec2u> uniformVec2u({ 0, 0 });
					this->m_Uniforms.insert({ uniform.first, uniformVec2u });
					break;
				}
				case UniformType::UINT_VEC3:
				{
					Uniform<Vec3u> uniformVec3u({ 0, 0, 0 });
					this->m_Uniforms.insert({ uniform.first, uniformVec3u });
					break;
				}
				case UniformType::UINT_VEC4:
				{
					Uniform<Vec4u> uniformVec4u({ 0, 0, 0, 0 });
					this->m_Uniforms.insert({ uniform.first, uniformVec4u });
					break;
				}
				case UniformType::FLOAT_MAT2:
				{
					Uniform<Mat2f> uniformMat2f({ 1.0f, 0.0f, 0.0f, 1.0f });
					this->m_Uniforms.insert({ uniform.first, uniformMat2f });
					break;
				}
				case UniformType::FLOAT_MAT3:
				{
					Uniform<Mat3f> uniformMat3f({ 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f });
					this->m_Uniforms.insert({ uniform.first, uniformMat3f });
					break;
				}
				case UniformType::FLOAT_MAT4:
				{
					Uniform<Mat4f> uniformMat4f({ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f });
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
