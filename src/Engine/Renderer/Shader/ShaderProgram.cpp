#include "Engine/Renderer/Shader/ShaderProgram.h"

namespace gp1::renderer
{
	void UniformBufferTemplate::AddElement(const std::string& name, EUniformType type)
	{
		for (auto& element : m_Elements)
			if (element.m_Name == name)
				return;

		m_Elements.push_back({ name, type });
	}

	void UniformBufferTemplate::RemoveElement(const std::string& name)
	{
		for (auto itr = m_Elements.begin(), end = m_Elements.end(); itr != end; itr++)
		{
			if (itr->m_Name == name)
			{
				m_Elements.erase(itr);
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

	UniformBuffer UniformBufferTemplate::CreateBuffer() const
	{
		std::vector<std::pair<std::string, UniformBuffer::UniformInfo>> uniforms;
		uniforms.reserve(m_Elements.size());
		for (auto& element : m_Elements)
			uniforms.push_back({ element.m_Name, UniformBuffer::UniformInfo(element.m_Type) });
		return UniformBuffer(m_Name, uniforms);
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

	Shader* ShaderProgram::GetShader(EShaderType shaderType)
	{
		auto itr = m_Shaders.begin();
		for (; itr != m_Shaders.end(); itr++)
			if (itr->m_Type == shaderType)
				return &*itr;

		m_Shaders.push_back(Shader(shaderType));
		return &m_Shaders[m_Shaders.size() - 1];
	}

	void ShaderProgram::CreateUniformBuffers(std::vector<UniformBuffer>& uniformBuffers) const
	{
		uniformBuffers.reserve(m_UniformBuffers.size());
		for (auto& uniformBuffer : m_UniformBuffers)
			uniformBuffers.push_back(uniformBuffer.CreateBuffer());
	}

	void ShaderProgram::AddUniformBuffer(const std::string& name)
	{
		for (auto& uniformBuffer : m_UniformBuffers)
			if (uniformBuffer.m_Name == name)
				return;

		m_UniformBuffers.push_back({ name });
	}

	void ShaderProgram::AddUniformBufferElement(const std::string& bufferName, const std::string& elementName, EUniformType elementType)
	{
		UniformBufferTemplate* buffer = GetUniformBuffer(bufferName);
		if (buffer)
			buffer->AddElement(elementName, elementType);
	}

	void ShaderProgram::RemoveUniformBuffer(const std::string& name)
	{
		for (auto itr = m_UniformBuffers.begin(), end = m_UniformBuffers.end(); itr != end; itr++)
		{
			if (itr->m_Name == name)
			{
				m_UniformBuffers.erase(itr);
				break;
			}
		}
	}

	void ShaderProgram::RemoveUniformBufferElement(const std::string& bufferName, const std::string& elementName)
	{
		UniformBufferTemplate* buffer = GetUniformBuffer(bufferName);
		if (buffer)
			buffer->RemoveElement(elementName);
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
} // namespace gp1