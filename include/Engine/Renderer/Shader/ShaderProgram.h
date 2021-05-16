//
//	Created by MarcasRealAccount on 14. May. 2021
//

#pragma once

#include "Engine/Renderer/Material/Uniform.h"
#include "Engine/Renderer/RendererData.h"
#include "Engine/Renderer/Shader/Shader.h"

#include <string>
#include <vector>

namespace gp1::renderer
{
	struct UniformBufferElementTemplate
	{
	public:
		std::string  m_Name;
		EUniformType m_Type;
	};

	struct UniformBufferTemplate
	{
	public:
		inline const std::vector<UniformBufferElementTemplate>& GetElements() const
		{
			return m_Elements;
		}

		void AddElement(const std::string& elementName, EUniformType elementType);
		void RemoveElement(const std::string& elementName);

		const UniformBufferElementTemplate* GetElement(const std::string& name) const;

		UniformBuffer CreateBuffer() const;

	public:
		std::string                               m_Name;
		std::vector<UniformBufferElementTemplate> m_Elements;
	};

	struct ShaderProgram : public RendererData
	{
	public:
		virtual ~ShaderProgram() = default;

		void    RemoveShader(EShaderType shaderType);
		Shader* GetShader(EShaderType shaderType);

		void CreateUniformBuffers(std::vector<UniformBuffer>& uniformBuffers) const;

		void AddUniformBuffer(const std::string& name);
		void AddUniformBufferElement(const std::string& bufferName, const std::string& elementName, EUniformType elementType);
		void RemoveUniformBuffer(const std::string& name);
		void RemoveUniformBufferElement(const std::string& bufferName, const std::string& elementName);

		UniformBufferTemplate*              GetUniformBuffer(const std::string& bufferName);
		const UniformBufferTemplate*        GetUniformBuffer(const std::string& bufferName) const;
		const UniformBufferElementTemplate* GetUniformBufferElement(const std::string& bufferName, const std::string& elementName) const;

	protected:
		std::vector<Shader>                m_Shaders;
		std::vector<UniformBufferTemplate> m_UniformBuffers;
	};
} // namespace gp1::renderer