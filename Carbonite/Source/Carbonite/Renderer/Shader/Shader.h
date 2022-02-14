#pragma once

#include "Graphics/Pipeline/ShaderModule.h"

#include <filesystem>

struct Shader
{
public:
	Shader(Graphics::Device& device);

	void updateShader();

	auto& getShaderModule() { return m_ShaderModule; }
	auto& getShaderModule() const { return m_ShaderModule; }

public:
	std::filesystem::path m_ShaderFile;

private:
	Graphics::ShaderModule m_ShaderModule;
};