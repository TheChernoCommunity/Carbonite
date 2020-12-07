//
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#include "Engine/Renderer/Shader/Material.h"
#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Renderer/Texture/Texture2DArray.h"
#include "Engine/Renderer/Texture/Texture3D.h"
#include "Engine/Renderer/Texture/TextureCubeMap.h"

#include <glm.hpp>

namespace gp1::renderer::shader
{
	Material::Material()
	    : Data(this) {}

	void Material::SetShader(Shader* shader)
	{
		this->m_Shader = shader;
		this->m_Uniforms.clear();

		if (this->m_Shader)
		{
			for (auto uniform : this->m_Shader->m_Uniforms)
			{
				switch (uniform.second.first)
				{
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
				case UniformType::TEXTURE_2D:
				{
					Uniform<texture::Texture2D*> uniformTexture2D(nullptr);
					this->m_Uniforms.insert({ uniform.first, uniformTexture2D });
					break;
				}
				case UniformType::TEXTURE_2D_ARRAY:
				{
					Uniform<texture::Texture2DArray*> uniformTexture2DArray(nullptr);
					this->m_Uniforms.insert({ uniform.first, uniformTexture2DArray });
					break;
				}
				case UniformType::TEXTURE_3D:
				{
					Uniform<texture::Texture3D*> uniformTexture3D(nullptr);
					this->m_Uniforms.insert({ uniform.first, uniformTexture3D });
					break;
				}
				case UniformType::TEXTURE_CUBE_MAP:
				{
					Uniform<texture::TextureCubeMap*> uniformTextureCubeMap(nullptr);
					this->m_Uniforms.insert({ uniform.first, uniformTextureCubeMap });
					break;
				}
				}
			}
		}
	}

	Shader* Material::GetShader() const
	{
		return this->m_Shader;
	}

	const std::unordered_map<std::string, std::any>& Material::GetUniforms() const
	{
		return this->m_Uniforms;
	}

} // namespace gp1::renderer::shader
