//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLShaderData.h"

namespace gp1::renderer::apis::opengl::shader
{
	Logger OpenGLShaderData::s_Logger("OpenGL Shader");

	OpenGLShaderData::OpenGLShaderData(renderer::shader::Shader* shader)
	    : OpenGLRendererData(shader) {}

	void OpenGLShaderData::CleanUp()
	{
		if (this->m_ProgramID)
		{
			glDeleteProgram(this->m_ProgramID);
			this->m_ProgramID = 0;
		}
		this->m_Shaders.clear();
	}

	uint32_t OpenGLShaderData::GetProgramID()
	{
		if (GetDataUnsafe<renderer::shader::Shader>()->IsDirty())
		{
			InitGLData();
		}
		return this->m_ProgramID;
	}

	void OpenGLShaderData::InitGLData()
	{
		if (this->m_ProgramID) CleanUp();

		using namespace renderer::shader;
		Shader* shader = GetDataUnsafe<Shader>();
		if (!shader) return;

		ShaderType types[] { ShaderType::COMPUTE, ShaderType::VERTEX, ShaderType::TESS_CONTROL, ShaderType::TESS_EVAL, ShaderType::GEOMETRY, ShaderType::FRAGMENT };
		for (ShaderType type : types)
		{
			FILE* file = fopen(("Shaders/" + shader->GetId() + GetShaderTypeExtensionName(type)).c_str(), "r");
			if (file)
			{
				this->m_Shaders.insert({ type, false });
				fclose(file);
			}
		}

		std::unordered_map<ShaderType, uint32_t> shaders;
		this->m_ProgramID = glCreateProgram();
		for (auto& shaderCode : this->m_Shaders)
		{
			uint32_t shaderId = LoadShader(shaderCode.first);
			if (shaderId > 0)
			{
				shaderCode.second = true;
				shaders.insert({ shaderCode.first, shaderId });
				glAttachShader(this->m_ProgramID, shaderId);
			}
		}
		{
			auto attribs = shader->GetAttributes();
			auto itr     = attribs.begin();
			while (itr != attribs.end())
			{
				glBindAttribLocation(this->m_ProgramID, itr->second, itr->first.c_str());
				itr++;
			}
		}
		glLinkProgram(this->m_ProgramID);
		GLint linkStatus;
		glGetProgramiv(this->m_ProgramID, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE)
		{
			GLint  length;
			GLchar infoLog[1024];
			glGetProgramInfoLog(this->m_ProgramID, 1024, &length, infoLog);
			OpenGLShaderData::s_Logger.LogError("%s link failed:\n%s", shader->GetId().c_str(), infoLog);
			for (auto shaderCode : shaders)
			{
				glDetachShader(this->m_ProgramID, shaderCode.second);
				glDeleteShader(shaderCode.second);
			}
			CleanUp();
			shader->ClearDirty();
			return;
		}
		for (auto shaderCode : shaders)
		{
			glDetachShader(this->m_ProgramID, shaderCode.second);
			glDeleteShader(shaderCode.second);
		}
		int32_t count;
		glGetProgramiv(this->m_ProgramID, GL_ACTIVE_UNIFORMS, &count);
		for (GLint i = 0; i < count; i++)
		{
			GLsizei length;
			GLint   size;
			GLenum  type;
			char    name[128];

			glGetActiveUniform(this->m_ProgramID, static_cast<GLuint>(i), 128, &length, &size, &type, name);
			shader->SetUniformTypeAndLocation(name, GetUniformType(type), i);
		}
		shader->ClearDirty();
	}

	void OpenGLShaderData::Start()
	{
		glUseProgram(GetProgramID());
	}

	void OpenGLShaderData::Stop()
	{
		glUseProgram(0);
	}

	uint32_t OpenGLShaderData::LoadShader(renderer::shader::ShaderType type)
	{
		using namespace renderer::shader;
		Shader* shader = GetDataUnsafe<Shader>();
		if (!shader) return 0;

		uint32_t shaderID = glCreateShader(static_cast<GLenum>(GetShaderTypeId(type)));

        std::string filename = "Shaders/" + shader->GetId() + GetShaderTypeExtensionName(type);
		FILE* file = fopen(filename.c_str(), "r");
		if (!file)
			return 0;

		fseek(file, 0, SEEK_END);
		uint32_t len = static_cast<uint32_t>(ftell(file));
		fseek(file, 0, SEEK_SET);
        std::string filecontent(len, '\0');
		len       = static_cast<uint32_t>(fread(filecontent.data(), sizeof(char), len, file));
		fclose(file);

		GLchar* const pShaderSource[1] { filecontent.data() };
		GLint         pLengths[1] { static_cast<GLint>(len) };

		glShaderSource(shaderID, 1, pShaderSource, pLengths);
		glCompileShader(shaderID);
		GLint compileStatus;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE)
		{
			GLint  length;
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, &length, infoLog);
			OpenGLShaderData::s_Logger.LogError("%s at %s compile failed:\n%s", GetShaderTypeName(type), ("Shaders/" + shader->GetId() + GetShaderTypeExtensionName(type)).c_str(), infoLog);
			glDeleteShader(shaderID);
			return 0;
		}
		return shaderID;
	}

	uint32_t OpenGLShaderData::GetShaderTypeId(renderer::shader::ShaderType type)
	{
		switch (type)
		{
		case renderer::shader::ShaderType::COMPUTE:
			return GL_COMPUTE_SHADER;
		case renderer::shader::ShaderType::VERTEX:
			return GL_VERTEX_SHADER;
		case renderer::shader::ShaderType::TESS_CONTROL:
			return GL_TESS_CONTROL_SHADER;
		case renderer::shader::ShaderType::TESS_EVAL:
			return GL_TESS_EVALUATION_SHADER;
		case renderer::shader::ShaderType::GEOMETRY:
			return GL_GEOMETRY_SHADER;
		case renderer::shader::ShaderType::FRAGMENT:
			return GL_FRAGMENT_SHADER;
		default:
			return 0;
		}
	}

	const char* OpenGLShaderData::GetShaderTypeName(renderer::shader::ShaderType type)
	{
		switch (type)
		{
		case renderer::shader::ShaderType::COMPUTE:
			return "Compute Shader";
		case renderer::shader::ShaderType::VERTEX:
			return "Vertex Shader";
		case renderer::shader::ShaderType::TESS_CONTROL:
			return "Tesselation Control Shader";
		case renderer::shader::ShaderType::TESS_EVAL:
			return "Tesselation Evaluation Shader";
		case renderer::shader::ShaderType::GEOMETRY:
			return "Geometry Shader";
		case renderer::shader::ShaderType::FRAGMENT:
			return "Fragment Shader";
		default:
			return "Unknown Shader";
		}
	}

	const char* OpenGLShaderData::GetShaderTypeExtensionName(renderer::shader::ShaderType type)
	{
		switch (type)
		{
		case renderer::shader::ShaderType::COMPUTE:
			return ".comp";
		case renderer::shader::ShaderType::VERTEX:
			return ".vert";
		case renderer::shader::ShaderType::TESS_CONTROL:
			return ".tessc";
		case renderer::shader::ShaderType::TESS_EVAL:
			return ".tessv";
		case renderer::shader::ShaderType::GEOMETRY:
			return ".geom";
		case renderer::shader::ShaderType::FRAGMENT:
			return ".frag";
		default:
			return "Unknown Shader";
		}
	}

	renderer::shader::UniformType OpenGLShaderData::GetUniformType(GLenum type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return renderer::shader::UniformType::FLOAT;
		case GL_FLOAT_VEC2:
			return renderer::shader::UniformType::FLOAT_VEC2;
		case GL_FLOAT_VEC3:
			return renderer::shader::UniformType::FLOAT_VEC3;
		case GL_FLOAT_VEC4:
			return renderer::shader::UniformType::FLOAT_VEC4;
		case GL_INT:
			return renderer::shader::UniformType::INT;
		case GL_INT_VEC2:
			return renderer::shader::UniformType::INT_VEC2;
		case GL_INT_VEC3:
			return renderer::shader::UniformType::INT_VEC3;
		case GL_INT_VEC4:
			return renderer::shader::UniformType::INT_VEC4;
		case GL_UNSIGNED_INT:
			return renderer::shader::UniformType::UINT;
		case GL_UNSIGNED_INT_VEC2:
			return renderer::shader::UniformType::UINT_VEC2;
		case GL_UNSIGNED_INT_VEC3:
			return renderer::shader::UniformType::UINT_VEC3;
		case GL_UNSIGNED_INT_VEC4:
			return renderer::shader::UniformType::UINT_VEC4;
		case GL_FLOAT_MAT2:
			return renderer::shader::UniformType::FLOAT_MAT2;
		case GL_FLOAT_MAT3:
			return renderer::shader::UniformType::FLOAT_MAT3;
		case GL_FLOAT_MAT4:
			return renderer::shader::UniformType::FLOAT_MAT4;
		default:
			return renderer::shader::UniformType::FLOAT;
		}
	}

} // namespace gp1::renderer::apis::opengl::shader
