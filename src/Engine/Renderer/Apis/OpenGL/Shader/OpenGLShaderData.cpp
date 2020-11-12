//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLShaderData.h"

namespace gp1 {

	Logger OpenGLShaderData::m_Logger("OpenGL Shader");

	OpenGLShaderData::OpenGLShaderData(Shader* shader)
		: ShaderData(shader) {}

	RendererType OpenGLShaderData::GetRendererType() const {
		return RendererType::OPENGL;
	}

	void OpenGLShaderData::CleanUp() {
		if (this->m_ProgramID) {
			glDeleteProgram(this->m_ProgramID);
			this->m_ProgramID = 0;
		}
		this->m_Shaders.clear();
	}

	uint32_t OpenGLShaderData::GetProgramID() {
		if (GetShader<Shader>()->IsDirty()) {
			InitGLData();
		}
		return this->m_ProgramID;
	}

	void OpenGLShaderData::InitGLData() {
		if (this->m_ProgramID)
			CleanUp();

		ShaderType types[]{ ShaderType::COMPUTE, ShaderType::VERTEX, ShaderType::TESS_CONTROL, ShaderType::TESS_EVAL, ShaderType::GEOMETRY, ShaderType::FRAGMENT };
		for (ShaderType type : types) {
			FILE* file = fopen(("Shaders/" + GetShader<Shader>()->GetId() + GetShaderTypeExtensionName(type)).c_str(), "r");
			if (file) {
				this->m_Shaders.insert({ type, false });
				fclose(file);
			}
		}

		std::unordered_map<ShaderType, uint32_t> shaders;
		this->m_ProgramID = glCreateProgram();
		for (auto& shader : this->m_Shaders) {
			uint32_t shaderId = LoadShader(shader.first);
			if (shaderId > 0) {
				shader.second = true;
				shaders.insert({ shader.first, shaderId });
				glAttachShader(this->m_ProgramID, shaderId);
			}
		}
		{
			auto attribs = GetAttributes();
			auto itr = attribs.begin();
			while (itr != attribs.end()) {
				glBindAttribLocation(this->m_ProgramID, itr->second, itr->first.c_str());
				itr++;
			}
		}
		glLinkProgram(this->m_ProgramID);
		GLint linkStatus;
		glGetProgramiv(this->m_ProgramID, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE) {
			GLint length;
			GLchar infoLog[1024];
			glGetProgramInfoLog(this->m_ProgramID, 1024, &length, infoLog);
			OpenGLShaderData::m_Logger.LogError("%s link failed:\n%s", GetShader<Shader>()->GetId().c_str(), infoLog);
			for (auto shader : shaders) {
				glDetachShader(this->m_ProgramID, shader.second);
				glDeleteShader(shader.second);
			}
			CleanUp();
			GetShader<Shader>()->ClearDirty();
			return;
		}
		for (auto shader : shaders) {
			glDetachShader(this->m_ProgramID, shader.second);
			glDeleteShader(shader.second);
		}
		int32_t count;
		glGetProgramiv(this->m_ProgramID, GL_ACTIVE_UNIFORMS, &count);
		for (GLint i = 0; i < count; i++) {
			GLsizei length;
			GLint size;
			GLenum type;
			char name[128];

			glGetActiveUniform(this->m_ProgramID, static_cast<GLuint>(i), 128, &length, &size, &type, name);
			SetUniformTypeAndLocation(name, GetUniformType(type), i);
		}
		GetShader<Shader>()->ClearDirty();
	}

	void OpenGLShaderData::Start() {
		glUseProgram(GetProgramID());
	}

	void OpenGLShaderData::Stop() {
		glUseProgram(0);
	}

	uint32_t OpenGLShaderData::LoadShader(ShaderType type) {
		uint32_t shaderID = glCreateShader(static_cast<GLenum>(GetShaderTypeId(type)));

		FILE* file = fopen(("Shaders/" + GetShader<Shader>()->GetId() + GetShaderTypeExtensionName(type)).c_str(), "r");
		if (!file)
			return 0;

		fseek(file, 0, SEEK_END);
		uint32_t len = ftell(file);
		fseek(file, 0, SEEK_SET);
		char* buf = new char[len];
		len = static_cast<uint32_t>(fread(buf, sizeof(char), len, file));
		buf[len] = '\0';
		fclose(file);

		GLchar* const pShaderSource[1]{ buf };
		GLint pLengths[1]{ static_cast<GLint>(len) };

		glShaderSource(shaderID, 1, pShaderSource, pLengths);
		glCompileShader(shaderID);
		GLint compileStatus;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE) {
			GLint length;
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, &length, infoLog);
			OpenGLShaderData::m_Logger.LogError("%s at %s compile failed:\n%s", GetShaderTypeName(type), ("Shaders/" + GetShader<Shader>()->GetId() + GetShaderTypeExtensionName(type)).c_str(), infoLog);
			glDeleteShader(shaderID);
			delete[] buf;
			return 0;
		}
		delete[] buf;
		return shaderID;
	}

	uint32_t OpenGLShaderData::GetShaderTypeId(ShaderType type) {
		switch (type) {
		case ShaderType::COMPUTE:
			return GL_COMPUTE_SHADER;
		case ShaderType::VERTEX:
			return GL_VERTEX_SHADER;
		case ShaderType::TESS_CONTROL:
			return GL_TESS_CONTROL_SHADER;
		case ShaderType::TESS_EVAL:
			return GL_TESS_EVALUATION_SHADER;
		case ShaderType::GEOMETRY:
			return GL_GEOMETRY_SHADER;
		case ShaderType::FRAGMENT:
			return GL_FRAGMENT_SHADER;
		default:
			return 0;
		}
	}

	const char* OpenGLShaderData::GetShaderTypeName(ShaderType type) {
		switch (type) {
		case ShaderType::COMPUTE:
			return "Compute Shader";
		case ShaderType::VERTEX:
			return "Vertex Shader";
		case ShaderType::TESS_CONTROL:
			return "Tesselation Control Shader";
		case ShaderType::TESS_EVAL:
			return "Tesselation Evaluation Shader";
		case ShaderType::GEOMETRY:
			return "Geometry Shader";
		case ShaderType::FRAGMENT:
			return "Fragment Shader";
		default:
			return "Unknown Shader";
		}
	}

	const char* OpenGLShaderData::GetShaderTypeExtensionName(ShaderType type) {
		switch (type) {
		case ShaderType::COMPUTE:
			return ".comp";
		case ShaderType::VERTEX:
			return ".vert";
		case ShaderType::TESS_CONTROL:
			return ".tessc";
		case ShaderType::TESS_EVAL:
			return ".tessv";
		case ShaderType::GEOMETRY:
			return ".geom";
		case ShaderType::FRAGMENT:
			return ".frag";
		default:
			return "Unknown Shader";
		}
	}

	UniformType OpenGLShaderData::GetUniformType(GLenum type) {
		switch (type) {
		case GL_FLOAT:
			return UniformType::FLOAT;
		case GL_FLOAT_VEC2:
			return UniformType::FLOAT_VEC2;
		case GL_FLOAT_VEC3:
			return UniformType::FLOAT_VEC3;
		case GL_FLOAT_VEC4:
			return UniformType::FLOAT_VEC4;
		case GL_INT:
			return UniformType::INT;
		case GL_INT_VEC2:
			return UniformType::INT_VEC2;
		case GL_INT_VEC3:
			return UniformType::INT_VEC3;
		case GL_INT_VEC4:
			return UniformType::INT_VEC4;
		case GL_UNSIGNED_INT:
			return UniformType::UINT;
		case GL_UNSIGNED_INT_VEC2:
			return UniformType::UINT_VEC2;
		case GL_UNSIGNED_INT_VEC3:
			return UniformType::UINT_VEC3;
		case GL_UNSIGNED_INT_VEC4:
			return UniformType::UINT_VEC4;
		case GL_FLOAT_MAT2:
			return UniformType::FLOAT_MAT2;
		case GL_FLOAT_MAT3:
			return UniformType::FLOAT_MAT3;
		case GL_FLOAT_MAT4:
			return UniformType::FLOAT_MAT4;
		default:
			return UniformType::FLOAT;
		}
	}

} // namespace gp1
