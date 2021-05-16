#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Shader/ShaderProgram.h"

#include <cstdint>
#include <vector>

namespace gp1::renderer::opengl
{
	struct OpenGLUniformBufferBindingPoint
	{
	public:
		std::string m_Name;
		uint32_t    m_Binding;

		std::vector<std::pair<std::string, uint32_t>> m_Offsets;
	};

	struct OpenGLShaderProgram : public ShaderProgram
	{
	public:
		virtual ~OpenGLShaderProgram();

		void Bind();
		void Unbind();
		bool Update();

		bool     IsUniformBufferValid(const std::string& name) const;
		uint32_t GetUniformBufferBindingPoint(const std::string& name) const;
		uint32_t GetUniformBufferElementOffset(const std::string& bufferName, const std::string& elementName) const;

	private:
		void GenGLData();
		void CleanUp();

		uint32_t GetGLShaderType(EShaderType shaderType) const;

	protected:
		uint32_t m_ProgramId;

		std::vector<OpenGLUniformBufferBindingPoint> m_UniformBufferBindingPoints;
	};
} // namespace gp1::renderer::opengl

#endif