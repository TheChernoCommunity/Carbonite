//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#pragma once
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Shader/Uniform.h"

#include <stdint.h>
#include <string>
#include <unordered_map>

namespace gp1 {

	class Material;

	class ShaderData;

	enum class ShaderType {
		COMPUTE,
		VERTEX,
		TESS_CONTROL,
		TESS_EVAL,
		GEOMETRY,
		FRAGMENT
	};

	class Shader {
	public:
		Shader(const std::string& id);
		virtual ~Shader();

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

		// Get this shader's data.
		ShaderData* GetShaderData(Renderer* renderer);

		friend ShaderData;
		friend Material;

	private:
		// Loads attributes and uniforms from the shaders .ini file
		void LoadAttributesAndUniforms();
		// Create the custom shader data.
		virtual ShaderData* CreateCustomShaderData(Renderer* renderer);

	public:
		// Get a shader from the id.
		static Shader* GetShader(const std::string& id);
		// Clean up all shaders.
		static void CleanUpShaders();

	protected:
		std::unordered_map<std::string, uint32_t> m_Attributes;						// All attributes that have been loaded.
		std::unordered_map<std::string, std::pair<UniformType, uint32_t>> m_Uniforms;	// All uniforms that have been loaded.

	private:
		std::string m_Id;					// The id of this shader.
		bool m_Dirty = true;				// Should the program recompile for next render.

		ShaderData* m_ShaderData = nullptr;	// The graphics specific shader data.

	private:
		static std::unordered_map<std::string, Shader*> m_LoadedShaders;	// All Shaders that has been loaded.
	};

	class ShaderData {
	public:
		ShaderData(Shader* shader);
		virtual ~ShaderData();

		// Get the renderer type for this shader data.
		virtual RendererType GetRendererType() const = 0;
		// Clean up this shader data.
		virtual void CleanUp() {};

	protected:
		// Get the shader this shader data is part of.
		template <typename T>
		T* GetShader() const {
			return reinterpret_cast<T*>(this->m_Shader);
		}

		const std::unordered_map<std::string, uint32_t>& GetAttributes() const;

		void SetAttributeIndex(const std::string& id, uint32_t index);
		void SetUniformTypeAndLocation(const std::string& id, UniformType type, uint32_t location);

	private:
		Shader* m_Shader;
	};

} // namespace gp1
