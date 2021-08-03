#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Shader/ShaderProgram.h"

#include <cstdint>
#include <vector>

namespace gp1::renderer::opengl
{
	struct OpenGLUniformBufferInfo
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

		void         Bind();
		void         Unbind();
		virtual void Update() override;

		OpenGLUniformBufferInfo* GetUniformBufferInfo(const std::string& name) const;

	private:
		void GenGLData();
		void CleanUp();

		uint32_t GetGLShaderType(EShaderType shaderType) const;

	protected:
		uint32_t m_ProgramId = 0;

		std::vector<OpenGLUniformBufferInfo> m_UniformBufferInfos;
	};
} // namespace gp1::renderer::opengl

#endif