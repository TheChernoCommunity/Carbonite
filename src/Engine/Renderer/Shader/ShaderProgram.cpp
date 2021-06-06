//
//	Created by MarcasRealAccount on 14. May. 2021
//

#include "Engine/Renderer/Shader/ShaderProgram.h"
#include "Engine/Application.h"

namespace gp1::renderer
{
	void UniformBufferTemplate::AddElement(const std::string& name, EUniformType type)
	{
		for (auto& element : m_Elements)
			if (element.m_Name == name)
				return;

		m_Elements.push_back({ name, type });
		m_Dirty = true;
	}

	void UniformBufferTemplate::RemoveElement(const std::string& name)
	{
		for (auto itr = m_Elements.begin(), end = m_Elements.end(); itr != end; itr++)
		{
			if (itr->m_Name == name)
			{
				m_Elements.erase(itr);
				m_Dirty = true;
				break;
			}
		}
	}

	const UniformBufferElementTemplate* UniformBufferTemplate::GetElement(const std::string& name) const
	{
		for (auto itr = m_Elements.begin(), end = m_Elements.end(); itr != end; itr++)
			if (itr->m_Name == name)
				return &*itr;
		return nullptr;
	}

	void UniformBufferTemplate::AddUniforms(std::vector<std::pair<std::string, EUniformType>>& uniforms) const
	{
		uniforms.reserve(m_Elements.size());
		for (auto& element : m_Elements)
			uniforms.push_back({ element.m_Name, element.m_Type });
	}

	std::unique_ptr<ShaderProgram> ShaderProgram::Create()
	{
		return Application::GetInstance()->GetRenderer()->CreateShaderProgram();
	}

	void ShaderProgram::RemoveShader(EShaderType shaderType)
	{
		auto itr = m_Shaders.begin();
		for (; itr != m_Shaders.end(); itr++)
		{
			if (itr->m_Type == shaderType)
			{
				m_Shaders.erase(itr);
				break;
			}
		}
	}

	Shader* ShaderProgram::AddShader(EShaderType shaderType)
	{
		auto itr = m_Shaders.begin();
		for (; itr != m_Shaders.end(); itr++)
			if (itr->m_Type == shaderType)
				return &*itr;

		m_Shaders.push_back(Shader(shaderType));
		return &m_Shaders[m_Shaders.size() - 1];
	}

	bool ShaderProgram::IsUniformBufferTemplateDirty() const
	{
		if (m_UniformBuffersDirty)
			return true;

		for (auto& uniformBuffer : m_UniformBuffers)
			if (uniformBuffer.m_Dirty)
				return true;
		return false;
	}

	void ShaderProgram::Update()
	{
		if (IsUniformBufferTemplateDirty())
		{
			std::vector<std::pair<std::string, std::vector<std::pair<std::string, EUniformType>>>> uniformBuffers;
			AddUniformBuffers(uniformBuffers);
			for (auto mat : m_Materials)
				mat->UpdateUniformBuffers(uniformBuffers);

			m_UniformBuffersDirty = false;
			for (auto& uniformBuffer : m_UniformBuffers)
				uniformBuffer.m_Dirty = false;
		}
	}

	void ShaderProgram::AddUniformBuffer(const std::string& name)
	{
		for (auto& uniformBuffer : m_UniformBuffers)
			if (uniformBuffer.m_Name == name)
				return;

		m_UniformBuffers.push_back({ name, {} });
		m_UniformBuffersDirty = true;
	}

	void ShaderProgram::AddUniformBufferElement(const std::string& bufferName, const std::string& elementName, EUniformType elementType)
	{
		UniformBufferTemplate* buffer = GetUniformBuffer(bufferName);
		if (buffer)
		{
			buffer->AddElement(elementName, elementType);
			m_UniformBuffersDirty = true;
		}
	}

	void ShaderProgram::RemoveUniformBuffer(const std::string& name)
	{
		for (auto itr = m_UniformBuffers.begin(), end = m_UniformBuffers.end(); itr != end; itr++)
		{
			if (itr->m_Name == name)
			{
				m_UniformBuffers.erase(itr);
				m_UniformBuffersDirty = true;
				break;
			}
		}
	}

	void ShaderProgram::RemoveUniformBufferElement(const std::string& bufferName, const std::string& elementName)
	{
		UniformBufferTemplate* buffer = GetUniformBuffer(bufferName);
		if (buffer)
		{
			buffer->RemoveElement(elementName);
			m_UniformBuffersDirty = true;
		}
	}

	UniformBufferTemplate* ShaderProgram::GetUniformBuffer(const std::string& bufferName)
	{
		for (auto& uniformBuffer : m_UniformBuffers)
			if (uniformBuffer.m_Name == bufferName)
				return &uniformBuffer;
		return nullptr;
	}

	const UniformBufferTemplate* ShaderProgram::GetUniformBuffer(const std::string& bufferName) const
	{
		for (auto& uniformBuffer : m_UniformBuffers)
			if (uniformBuffer.m_Name == bufferName)
				return &uniformBuffer;
		return nullptr;
	}

	const UniformBufferElementTemplate* ShaderProgram::GetUniformBufferElement(const std::string& bufferName, const std::string& elementName) const
	{
		const UniformBufferTemplate* uniformBuffer = GetUniformBuffer(bufferName);
		if (uniformBuffer)
			return uniformBuffer->GetElement(elementName);
		return nullptr;
	}

	void ShaderProgram::AddUniformBuffers(std::vector<std::pair<std::string, std::vector<std::pair<std::string, EUniformType>>>>& uniformBuffer) const
	{
		uniformBuffer.reserve(m_UniformBuffers.size());
		for (auto& buf : m_UniformBuffers)
		{
			std::vector<std::pair<std::string, EUniformType>> uniforms;
			buf.AddUniforms(uniforms);
			uniformBuffer.push_back({ buf.m_Name, uniforms });
		}
	}

	void ShaderProgram::AddMaterial(Material* material)
	{
		m_Materials.push_back(material);
		std::vector<std::pair<std::string, std::vector<std::pair<std::string, EUniformType>>>> uniformBuffers;
		AddUniformBuffers(uniformBuffers);
		material->UpdateUniformBuffers(uniformBuffers);
	}

	void ShaderProgram::RemoveMaterial(Material* material)
	{
		auto itr = std::find(m_Materials.begin(), m_Materials.end(), material);
		if (itr != m_Materials.end())
			m_Materials.erase(itr);
	}
} // namespace gp1::renderer