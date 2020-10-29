//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Utility/Config/ConfigManager.h"
#include "Engine/Utility/Config/ConfigSection.h"

namespace gp1 {

	std::unordered_map<std::string, Shader*> Shader::m_LoadedShaders;

	Logger Shader::m_Logger = Logger("Shader");

	Shader* Shader::GetShader(std::string id) {
		auto itr = Shader::m_LoadedShaders.find(id);
		while (itr != Shader::m_LoadedShaders.end())
			return itr->second;

		Shader* shader = new Shader(id);
		shader->InitGLData();
		Shader::m_LoadedShaders.insert({ id, shader });
		return shader;
	}

	const std::unordered_map<std::string, std::pair<uint32_t, uint32_t>>& Shader::GetAllAvailableUniforms() const {
		return this->m_UniformIds;
	}

	void Shader::MarkDirty() {
		this->m_Dirty = true;
	}

	void Shader::Start() {
		glUseProgram(GetProgramID());
	}

	void Shader::Stop() {
		glUseProgram(0);
	}

	Shader::Shader(std::string id)
		: m_Id(id) {}

	Shader::~Shader() {
		CleanUpGLData();

		auto itr = Shader::m_LoadedShaders.find(this->m_Id);
		while (itr != Shader::m_LoadedShaders.end())
			Shader::m_LoadedShaders.erase(itr);
	}

	const char* Shader::GetShaderTypeName(ShaderType type) {
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

	const char* Shader::GetShaderTypeExtensionName(ShaderType type) {
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

	uint32_t Shader::LoadShader(std::string id, ShaderType type) {
		uint32_t shaderID = glCreateShader((GLenum)type);

		FILE* file = fopen(("Shaders/" + id + GetShaderTypeExtensionName(type)).c_str(), "r");
		if (!file)
			return 0;

		fseek(file, 0, SEEK_END);
		uint32_t len = ftell(file);
		fseek(file, 0, SEEK_SET);
		char* buf = new char[len];
		len = (uint32_t)fread(buf, sizeof(char), len, file);
		buf[len] = '\0';
		fclose(file);

		GLchar* const pShaderSource[1]{ buf };
		GLint pLengths[1]{ (GLint)len };

		glShaderSource(shaderID, 1, pShaderSource, pLengths);
		glCompileShader(shaderID);
		GLint compileStatus;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE) {
			GLint length;
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, &length, infoLog);
			Shader::m_Logger.LogError("%s at %s compile failed:\n%s", GetShaderTypeName(type), ("Shaders/" + id + GetShaderTypeExtensionName(type)).c_str(), infoLog);
			glDeleteShader(shaderID);
			delete[] buf;
			return 0;
		}
		delete[] buf;
		return shaderID;
	}

	uint32_t Shader::GetProgramID() {
		if (this->m_Dirty)
			InitGLData();
		return this->m_ProgramID;
	}

	void Shader::InitGLData() {
		if (this->m_ProgramID)
			CleanUpGLData();

		ShaderType types[]{ ShaderType::COMPUTE, ShaderType::VERTEX, ShaderType::TESS_CONTROL, ShaderType::TESS_EVAL, ShaderType::GEOMETRY, ShaderType::FRAGMENT };
		for (ShaderType type : types) {
			FILE* file = fopen(("Shaders/" + this->m_Id + GetShaderTypeExtensionName(type)).c_str(), "r");
			if (file) {
				this->m_Shaders.insert({ type, false });
				fclose(file);
			}
		}
		config::ConfigFile* shaderConfig = config::ConfigManager::GetConfigFilePath("Shaders/" + this->m_Id);
		config::ConfigSection* pShaderAttributes = shaderConfig->GetSection("Attributes");
		if (pShaderAttributes) {
			auto shaderAttributes = pShaderAttributes->GetConfigs();
			for (auto attribute : shaderAttributes) {
				uint32_t index = (uint32_t)pShaderAttributes->GetConfigUInt(attribute.first);
				this->m_Attributes.insert({ attribute.first, index });
			}
		}
		delete shaderConfig;

		std::unordered_map<ShaderType, uint32_t> shaders;
		this->m_ProgramID = glCreateProgram();
		for (auto& shader : this->m_Shaders) {
			uint32_t shaderId = LoadShader(this->m_Id, shader.first);
			if (shaderId > 0) {
				shader.second = true;
				shaders.insert({ shader.first, shaderId });
				glAttachShader(this->m_ProgramID, shaderId);
			}
		}
		{
			auto itr = this->m_Attributes.begin();
			while (itr != this->m_Attributes.end()) {
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
			Shader::m_Logger.LogError("%s link failed:\n%s", this->m_Id.c_str(), infoLog);
			for (auto shader : shaders) {
				glDetachShader(this->m_ProgramID, shader.second);
				glDeleteShader(shader.second);
			}
			CleanUpGLData();
			this->m_Dirty = false;
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

			glGetActiveUniform(this->m_ProgramID, (GLuint)i, 128, &length, &size, &type, name);
			this->m_UniformIds.insert({ std::string(name), { i, type } });
		}
		this->m_Dirty = false;
	}

	void Shader::CleanUpGLData() {
		Stop();
		if (this->m_ProgramID)
			glDeleteProgram(this->m_ProgramID);

		for (auto& shader : this->m_Shaders)
			shader.second = false;

		this->m_UniformIds.clear();

		this->m_ProgramID = 0;
	}

	void Shader::CleanUpShaders() {
		for (auto shader : Shader::m_LoadedShaders)
			shader.second->CleanUpGLData();
	}

} // namespace gp1
