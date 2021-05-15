//
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Utility/Config/ConfigManager.h"
#include "Engine/Utility/Config/ConfigSection.h"

namespace gp1::renderer::shader
{
	extern EnumVector<UniformType> UniformTypeNames;

	std::unordered_map<std::string, Shader*> Shader::s_LoadedShaders;

	Shader::Shader(const std::string& id)
	    : Data(this), m_Id(id) {}

	const std::string& Shader::GetId() const
	{
		return this->m_Id;
	}

	void Shader::MarkDirty()
	{
		this->m_Dirty = true;
	}

	void Shader::ClearDirty()
	{
		this->m_Dirty = false;
	}

	bool Shader::IsDirty()
	{
		return this->m_Dirty;
	}

	uint32_t Shader::GetUniformLocation(const std::string& id) const
	{
		auto itr = this->m_Uniforms.find(id);
		if (itr != this->m_Uniforms.end()) return itr->second.second;
		return 0;
	}

	const std::unordered_map<std::string, uint32_t>& Shader::GetAttributes() const
	{
		return this->m_Attributes;
	}

	void Shader::SetAttributeIndex(const std::string& id, uint32_t index)
	{
		auto itr = this->m_Attributes.find(id);
		if (itr != this->m_Attributes.end())
			itr->second = index;
		else
			this->m_Attributes.insert({ id, index });
	}

	void Shader::SetUniformTypeAndLocation(const std::string& id, UniformType type, uint32_t location)
	{
		auto itr = this->m_Uniforms.find(id);
		if (itr != this->m_Uniforms.end())
		{
			itr->second.first  = type;
			itr->second.second = location;
		}
		else
		{
			this->m_Uniforms.insert({ id, { type, location } });
		}
	}

	void Shader::LoadAttributesAndUniforms()
	{
		this->m_Attributes.clear();
		this->m_Uniforms.clear();
		config::ConfigFile*    shaderConfig      = config::ConfigManager::GetConfigFilePath("Shaders/" + this->m_Id);
		config::ConfigSection* pShaderAttributes = shaderConfig->GetSection("Attributes");
		if (pShaderAttributes)
		{
			auto shaderAttributes = pShaderAttributes->GetConfigs();
			for (auto attribute : shaderAttributes)
			{
				uint32_t index = pShaderAttributes->GetConfigTyped<uint32_t>(attribute.first, 0);
				this->m_Attributes.insert({ attribute.first, index });
			}
		}
		config::ConfigSection* pShaderUniforms = shaderConfig->GetSection("Uniforms");
		if (pShaderUniforms)
		{
			auto shaderUniforms = pShaderUniforms->GetConfigs();
			for (auto uniform : shaderUniforms)
			{
				this->m_Uniforms.insert({ uniform.first, { pShaderUniforms->GetConfigEnum(uniform.first, UniformType::FLOAT, UniformTypeNames), 0 } });
			}
		}
		delete shaderConfig;
	}

	Shader* Shader::GetShader(const std::string& id)
	{
		auto itr = Shader::s_LoadedShaders.find(id);
		while (itr != Shader::s_LoadedShaders.end())
			return itr->second;

		Shader* shader = new Shader(id);
		shader->LoadAttributesAndUniforms();
		Shader::s_LoadedShaders.insert({ id, shader });
		return shader;
	}

	void Shader::CleanUpShaders()
	{
		for (auto shader : Shader::s_LoadedShaders)
			delete shader.second;

		Shader::s_LoadedShaders.clear();
	}

	// OH GOD NOOOOO NOT AGAIN!
	EnumVector<UniformType> UniformTypeNames = {
		{ UniformType::FLOAT, "Float" },
		{ UniformType::FLOAT_VEC2, "FVec2" },
		{ UniformType::FLOAT_VEC3, "FVec3" },
		{ UniformType::FLOAT_VEC4, "FVec4" },
		{ UniformType::INT, "Int" },
		{ UniformType::INT_VEC2, "IVec2" },
		{ UniformType::INT_VEC3, "IVec3" },
		{ UniformType::INT_VEC4, "IVec4" },
		{ UniformType::UINT, "UInt" },
		{ UniformType::UINT_VEC2, "UVec2" },
		{ UniformType::UINT_VEC3, "UVec3" },
		{ UniformType::UINT_VEC4, "UVec4" },
		{ UniformType::FLOAT_MAT2, "FMat2" },
		{ UniformType::FLOAT_MAT3, "FMat3" },
		{ UniformType::FLOAT_MAT4, "FMat4" },
		{ UniformType::TEXTURE_2D, "Texture2D" },
		{ UniformType::TEXTURE_2D_ARRAY, "Texture2DArray" },
		{ UniformType::TEXTURE_3D, "Texture3D" },
		{ UniformType::TEXTURE_CUBE_MAP, "TextureCubeMap" }
	};

} // namespace gp1::renderer::shader
