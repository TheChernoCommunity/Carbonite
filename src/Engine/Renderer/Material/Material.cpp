//
//	Created by MarcasRealAccount on 14. May. 2021
//

#include "Engine/Renderer/Material/Material.h"
#include "Engine/Renderer/Shader/ShaderProgram.h"

namespace gp1::renderer
{
	void Material::SetShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram)
	{
		m_ShaderProgram = shaderProgram;
		m_UniformBuffers.clear();
		if (m_ShaderProgram)
			m_ShaderProgram->CreateUniformBuffers(m_UniformBuffers);
	}

	void Material::UpdateShaderProgram()
	{
		if (m_ShaderProgram)
		{
			std::vector<UniformBuffer> oldBuffers = m_UniformBuffers;
			m_UniformBuffers.clear();
			m_ShaderProgram->CreateUniformBuffers(m_UniformBuffers);
			for (auto& oldBuffer : oldBuffers)
			{
				UniformBuffer* uniformBuffer = GetUniformBuffer(oldBuffer.GetName());
				if (uniformBuffer)
				{
					for (auto& oldBufferUniform : oldBuffer)
					{
						std::shared_ptr<Uniform> uniform = uniformBuffer->GetUniform(oldBufferUniform.first);
						if (uniform)
							uniform->CopyFrom(oldBufferUniform.second.m_Uniform);
					}
				}
			}
		}
		else
		{
			m_UniformBuffers.clear();
		}
	}

	UniformBuffer* Material::GetUniformBuffer(const std::string& name)
	{
		for (auto& uniformBuffer : m_UniformBuffers)
			if (uniformBuffer.GetName() == name)
				return &uniformBuffer;
		return nullptr;
	}

	const UniformBuffer* Material::GetUniformBuffer(const std::string& name) const
	{
		for (auto& uniformBuffer : m_UniformBuffers)
			if (uniformBuffer.GetName() == name)
				return &uniformBuffer;
		return nullptr;
	}

	std::shared_ptr<Uniform> Material::GetUniform(const std::string& bufferName, const std::string& uniformName) const
	{
		const UniformBuffer* uniformBuffer = GetUniformBuffer(bufferName);
		if (uniformBuffer)
			return uniformBuffer->GetUniform(uniformName);
		return nullptr;
	}
} // namespace gp1::renderer