//
//	Created by MarcasRealAccount on 14. May. 2021
//

#pragma once

#include "Engine/Renderer/DynamicRendererData.h"
#include "Engine/Renderer/Material/Uniform.h"
#include "Engine/Renderer/Shader/Shader.h"

#include <memory>
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

		void AddUniforms(std::vector<std::pair<std::string, EUniformType>>& uniforms) const;

	public:
		std::string                               m_Name;
		std::vector<UniformBufferElementTemplate> m_Elements;

		bool m_Dirty = true;
	};

	struct Material;

	struct ShaderProgram : public DynamicRendererData
	{
	public:
		friend Material;

		static std::shared_ptr<ShaderProgram> Create();

	public:
		virtual ~ShaderProgram() = default;

		void    RemoveShader(EShaderType shaderType);
		Shader* AddShader(EShaderType shaderType);

		bool IsUniformBufferTemplateDirty() const;

		virtual void Update() override;

		void AddUniformBuffer(const std::string& name);
		void AddUniformBufferElement(const std::string& bufferName, const std::string& elementName, EUniformType elementType);
		void RemoveUniformBuffer(const std::string& name);
		void RemoveUniformBufferElement(const std::string& bufferName, const std::string& elementName);

		UniformBufferTemplate*              GetUniformBuffer(const std::string& bufferName);
		const UniformBufferTemplate*        GetUniformBuffer(const std::string& bufferName) const;
		const UniformBufferElementTemplate* GetUniformBufferElement(const std::string& bufferName, const std::string& elementName) const;

		void AddUniformBuffers(std::vector<std::pair<std::string, std::vector<std::pair<std::string, EUniformType>>>>& uniformBuffer) const;

	protected:
		ShaderProgram() = default;

		void AddMaterial(std::shared_ptr<Material> material);
		void RemoveMaterial(std::shared_ptr<Material> material);

	protected:
		std::vector<Shader>                  m_Shaders;
		std::vector<UniformBufferTemplate>   m_UniformBuffers;
		std::vector<std::weak_ptr<Material>> m_Materials;

		bool m_UniformBuffersDirty = true;
	};
} // namespace gp1::renderer

#include "Engine/Renderer/Material/Material.h"