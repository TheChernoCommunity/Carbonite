//
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#pragma once

#include "Engine/Renderer/RendererData.h"
#include "Engine/Renderer/Shader/Uniform.h"

#include <stdint.h>
#include <string>
#include <unordered_map>

namespace gp1::renderer::shader
{
	struct Material;

	enum class ShaderType
	{
		COMPUTE,
		VERTEX,
		TESS_CONTROL,
		TESS_EVAL,
		GEOMETRY,
		FRAGMENT
	};

	struct Shader : public Data
	{
	public:
		Shader(const std::string& id);

		// Get the Id of this shader.
		const std::string& GetId() const;

		// Mark this shader dirty for recreation.
		void MarkDirty();
		// Clears this shader's dirtiness.
		void ClearDirty();
		// Is this shader dirty.
		bool IsDirty();

		// Get a uniform location for this shader.
		uint32_t GetUniformLocation(const std::string& id) const;

		// Get all attributes for this shader.
		const std::unordered_map<std::string, uint32_t>& GetAttributes() const;

		// Set the index of an attribute.
		// This function should not be called by anyone.
		void SetAttributeIndex(const std::string& id, uint32_t index);

		// Set the type and location of a uniform.
		// This function should not be called by anyone.
		void SetUniformTypeAndLocation(const std::string& id, UniformType type, uint32_t location);

		friend Material;

	private:
		// Loads attributes and uniforms from the shaders .ini file
		void LoadAttributesAndUniforms();

	public:
		// Get a shader from the id.
		static Shader* GetShader(const std::string& id);
		// Clean up all shaders.
		static void CleanUpShaders();

	protected:
		std::unordered_map<std::string, uint32_t>                         m_Attributes; // All attributes that have been loaded.
		std::unordered_map<std::string, std::pair<UniformType, uint32_t>> m_Uniforms;   // All uniforms that have been loaded.

	private:
		std::string m_Id;           // The id of this shader.
		bool        m_Dirty = true; // Should the program recompile for next render.

	private:
		static std::unordered_map<std::string, Shader*> s_LoadedShaders; // All Shaders that has been loaded.
	};

} // namespace gp1::renderer::shader
