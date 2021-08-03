//
//	Created by MarcasRealAccount on 14. May. 2021
//

#include "Engine/Renderer/Material/Material.h"
#include "Engine/Application.h"
#include "Engine/Renderer/Shader/ShaderProgram.h"

namespace gp1::renderer
{
	std::unique_ptr<Material> Material::Create()
	{
		return Application::GetInstance()->GetRenderer()->CreateMaterial();
	}

	Material::~Material()
	{
		if (m_ShaderProgram)
			m_ShaderProgram->RemoveMaterial(this);
	}

	void Material::SetShaderProgram(ShaderProgram* shaderProgram)
	{
		if (m_ShaderProgram)
			m_ShaderProgram->RemoveMaterial(this);
		m_UniformBuffers.clear();
		m_ShaderProgram = shaderProgram;
		m_ShaderProgram->AddMaterial(this);
	}

	UniformBuffer* Material::GetUniformBuffer(std::string_view name) const
	{
		for (auto& uniformBuffer : m_UniformBuffers)
			if (uniformBuffer.m_Name == name)
				return uniformBuffer.m_UniformBuffer.get();
		return nullptr;
	}

	Uniform* Material::GetUniform(std::string_view bufferName, std::string_view uniformName) const
	{
		UniformBuffer* uniformBuffer = GetUniformBuffer(bufferName);
		if (uniformBuffer)
			return uniformBuffer->GetUniform(uniformName);
		return nullptr;
	}

	void Material::UpdateUniformBuffers(std::vector<std::pair<std::string, std::vector<std::pair<std::string, EUniformType>>>> uniformBuffers)
	{
		{
			std::vector<std::string> seenBufferNames;
			for (auto itr = uniformBuffers.begin(); itr != uniformBuffers.end();)
			{
				bool found = false;
				for (auto seenItr = seenBufferNames.begin(), end = seenBufferNames.end(); seenItr != end; seenItr++)
				{
					if (*seenItr == itr->first)
					{
						found = true;
						break;
					}
				}

				if (found)
				{
					itr = uniformBuffers.erase(itr);
				}
				else
				{
					seenBufferNames.push_back(itr->first);
					itr++;
				}
			}
		}

		for (auto itr = m_UniformBuffers.begin(); itr != m_UniformBuffers.end();)
		{
			bool found = false;
			for (auto bufItr = uniformBuffers.begin(), end = uniformBuffers.end(); bufItr != end; bufItr++)
			{
				if (bufItr->first == itr->m_Name)
				{
					auto& buf = itr->m_UniformBuffer;
					buf->UpdateUniforms(bufItr->second);
					uniformBuffers.erase(bufItr);
					found = true;
					break;
				}
			}

			if (found)
				itr++;
			else
				itr = m_UniformBuffers.erase(itr);
		}

		for (auto& uniformBuffer : uniformBuffers)
		{
			std::unique_ptr<UniformBuffer> buf = UniformBuffer::Create();
			buf->UpdateUniforms(uniformBuffer.second);
			m_UniformBuffers.push_back({ uniformBuffer.first, std::move(buf) });
		}
	}
} // namespace gp1::renderer