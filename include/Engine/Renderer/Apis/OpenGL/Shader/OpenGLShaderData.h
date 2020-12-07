//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#pragma once

#include "Engine/Renderer/Apis/OpenGL/OpenGLRendererData.h"
#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Utility/Logger.h"

#include <glad/glad.h>

namespace gp1::renderer::apis::opengl::shader
{
	class OpenGLShaderData : public OpenGLRendererData
	{
	public:
		OpenGLShaderData(renderer::shader::Shader* shader);

		virtual void CleanUp() override;

		// Get the program id.
		uint32_t GetProgramID();
		// Initialize GL data.
		void InitGLData();

		// Start using this shader.
		void Start();
		// Stop using this shader.
		void Stop();

		friend OpenGLRenderer;

	protected:
		// Load and compile a shader type.
		uint32_t LoadShader(renderer::shader::ShaderType type);

	protected:
		// Get the id of the shader type.
		static uint32_t GetShaderTypeId(renderer::shader::ShaderType type);
		// Get the name of a shader type.
		static const char* GetShaderTypeName(renderer::shader::ShaderType type);
		// Get the extension name of a shader type.
		static const char* GetShaderTypeExtensionName(renderer::shader::ShaderType type);

		static renderer::shader::UniformType GetUniformType(GLenum type);

	private:
		uint32_t m_ProgramID = 0; // The program ID of this shader.

		std::unordered_map<renderer::shader::ShaderType, bool> m_Shaders; // All shader types that have been loaded.
	private:
		static Logger s_Logger; // The shader's logger.
	};

} // namespace gp1::renderer::apis::opengl::shader
