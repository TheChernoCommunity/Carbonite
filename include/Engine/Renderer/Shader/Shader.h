//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#pragma once
#include "Engine/Utility/Logger.h"

#include <stdint.h>
#include <string>
#include <unordered_map>

#include <glad/glad.h>

namespace gp1 {

	class Renderer;
	class Material;

	enum class ShaderType : GLenum {
		COMPUTE = GL_COMPUTE_SHADER,
		VERTEX = GL_VERTEX_SHADER,
		TESS_CONTROL = GL_TESS_CONTROL_SHADER,
		TESS_EVAL = GL_TESS_EVALUATION_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER
	};

	class Shader {
	public:
		// Get a shader from the id.
		static Shader* GetShader(std::string id);

		// Get all available uniforms of this shader.
		const std::unordered_map<std::string, std::pair<uint32_t, uint32_t>>& GetAllAvailableUniforms() const;

		// Mark this shader dirty (reloads and recompiles the shader).
		void MarkDirty();

		// Start using this shader.
		void Start();
		// Stop using this shader.
		void Stop();

		friend Renderer;
		friend Material;

	private:
		Shader(std::string id);
		~Shader();

		// Get the program id.
		uint32_t GetProgramID();
		// Initialize GL data.
		void InitGLData();
		// Clean up GL data.
		void CleanUpGLData();

		// Clean up all shaders.
		static void CleanUpShaders();

		// Get the name of a shader type.
		static const char* GetShaderTypeName(ShaderType type);
		// Get the extension name of a shader type.
		static const char* GetShaderTypeExtensionName(ShaderType type);
		// Load and compile a shader type.
		static uint32_t LoadShader(std::string path, ShaderType type);

	private:
		std::string m_Id;			// The id of this shader.
		uint32_t m_ProgramID = 0;	// The program ID of this shader.

		bool m_Dirty = false;		// Should the program recompile for next render.

		std::unordered_map<ShaderType, bool> m_Shaders;									// All shader types that have been loaded.
		std::unordered_map<std::string, uint32_t> m_Attributes;							// All attributes that have been loaded.
		std::unordered_map<std::string, std::pair<uint32_t, uint32_t>> m_UniformIds;	// All uniforms that have been loaded.

	private:
		static std::unordered_map<std::string, Shader*> m_LoadedShaders;	// All Shaders that has been loaded.

		static Logger m_Logger;	// The shader's logger.
	};

} // namespace gp1
