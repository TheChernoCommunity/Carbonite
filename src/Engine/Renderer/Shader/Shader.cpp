//
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Utility/Config/ConfigManager.h"
#include "Engine/Utility/Config/ConfigSection.h"

namespace gp1 {

extern std::vector<std::pair<UniformType, std::string>> UniformTypeNames;

std::unordered_map<std::string, Shader*> Shader::m_LoadedShaders;

Shader::Shader(const std::string& id)
    : m_Id(id) {}

Shader::~Shader() {
    if (this->m_ShaderData) {
        this->m_ShaderData->CleanUp();
        delete this->m_ShaderData;
    }
}

const std::string& Shader::GetId() const {
    return this->m_Id;
}

void Shader::MarkDirty() {
    this->m_Dirty = true;
}

void Shader::ClearDirty() {
    this->m_Dirty = false;
}

bool Shader::IsDirty() {
    return this->m_Dirty;
}

uint32_t Shader::GetUniformLocation(const std::string& id) const {
    auto itr = this->m_Uniforms.find(id);
    if (itr != this->m_Uniforms.end()) {
        return itr->second.second;
    }
    return 0;
}

ShaderData* Shader::GetShaderData(Renderer* renderer) {
    if (!this->m_ShaderData || !renderer->IsShaderDataUsable(this->m_ShaderData)) {
        if (this->m_ShaderData) {
            this->m_ShaderData->CleanUp();
            delete this->m_ShaderData;
            LoadAttributesAndUniforms();
        }
        this->m_ShaderData = CreateCustomShaderData(renderer);
    }
    return this->m_ShaderData;
}

void Shader::LoadAttributesAndUniforms() {
    this->m_Attributes.clear();
    this->m_Uniforms.clear();
    config::ConfigFile* shaderConfig = config::ConfigManager::GetConfigFilePath("Shaders/" + this->m_Id);
    config::ConfigSection* pShaderAttributes = shaderConfig->GetSection("Attributes");
    if (pShaderAttributes) {
        auto shaderAttributes = pShaderAttributes->GetConfigs();
        for (auto attribute : shaderAttributes) {
            uint32_t index = pShaderAttributes->GetConfigTyped<uint32_t>(attribute.first, 0);
            this->m_Attributes.insert({ attribute.first, index });
        }
    }
    config::ConfigSection* pShaderUniforms = shaderConfig->GetSection("Uniforms");
    if (pShaderUniforms) {
        auto shaderUniforms = pShaderUniforms->GetConfigs();
        for (auto uniform : shaderUniforms) {
            this->m_Uniforms.insert({ uniform.first, { pShaderUniforms->GetConfigEnum(uniform.first, UniformType::FLOAT, UniformTypeNames), 0 } });
        }
    }
    delete shaderConfig;
}

ShaderData* Shader::CreateCustomShaderData(Renderer* renderer) {
    return renderer->CreateShaderData(this);
}

Shader* Shader::GetShader(const std::string& id) {
    auto itr = Shader::m_LoadedShaders.find(id);
    while (itr != Shader::m_LoadedShaders.end())
        return itr->second;

    Shader* shader = new Shader(id);
    shader->LoadAttributesAndUniforms();
    Shader::m_LoadedShaders.insert({ id, shader });
    return shader;
}

void Shader::CleanUpShaders() {
    for (auto shader : Shader::m_LoadedShaders) {
        if (shader.second->m_ShaderData) {
            delete shader.second;
        }
    }

    Shader::m_LoadedShaders.clear();
}

ShaderData::ShaderData(Shader* shader)
    : m_Shader(shader) {}

ShaderData::~ShaderData() {
    if (this->m_Shader)
        this->m_Shader->m_ShaderData = nullptr;
}

const std::unordered_map<std::string, uint32_t>& ShaderData::GetAttributes() const {
    return this->m_Shader->m_Attributes;
}

void ShaderData::SetAttributeIndex(const std::string& id, uint32_t index) {
    auto itr = this->m_Shader->m_Attributes.find(id);
    if (itr != this->m_Shader->m_Attributes.end())
        itr->second = index;
    else
        this->m_Shader->m_Attributes.insert({ id, index });
}

void ShaderData::SetUniformTypeAndLocation(const std::string& id, UniformType type, uint32_t location) {
    auto itr = this->m_Shader->m_Uniforms.find(id);
    if (itr != this->m_Shader->m_Uniforms.end()) {
        itr->second.first = type;
        itr->second.second = location;
    } else
        this->m_Shader->m_Uniforms.insert({ id, { type, location } });
}

// OH GOD NOOOOO NOT AGAIN!
std::vector<std::pair<UniformType, std::string>> UniformTypeNames = {
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
    { UniformType::FLOAT_MAT4, "FMat4" }
};

} // namespace gp1
