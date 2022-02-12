#include <shaderc/shaderc.hpp>

#include "GLSLang.h"
#include "Utils/Log.h"

namespace
{
	static shaderc::Compiler s_compiler;
}

GLSLang& GLSLang::Get()
{
	static GLSLang* s_Instance = new GLSLang();
	return *s_Instance;
}

void GLSLang::Destroy()
{
	delete &Get();
}

std::vector<std::uint32_t> GLSLang::compileShader(std::string_view sourceString, Graphics::EShaderType shaderType)
{
	shaderc_shader_kind kind;

	switch (shaderType)
	{
	case Graphics::EShaderType::Vertex:
		kind = shaderc_glsl_vertex_shader;
		break;
	case Graphics::EShaderType::TessControl:
		kind = shaderc_glsl_tess_control_shader;
		break;
	case Graphics::EShaderType::TessEvaluation:
		kind = shaderc_glsl_tess_evaluation_shader;
		break;
	case Graphics::EShaderType::Geometry:
		kind = shaderc_glsl_geometry_shader;
		break;
	case Graphics::EShaderType::Fragment:
		kind = shaderc_glsl_fragment_shader;
		break;
	case Graphics::EShaderType::Compute:
		kind = shaderc_glsl_compute_shader;
		break;
	case Graphics::EShaderType::RTRayGen:
		kind = shaderc_glsl_default_raygen_shader;
		break;
	case Graphics::EShaderType::RTAnyHit:
		kind = shaderc_glsl_default_anyhit_shader;
		break;
	case Graphics::EShaderType::RTClosestHit:
		kind = shaderc_glsl_default_closesthit_shader;
		break;
	case Graphics::EShaderType::RTMiss:
		kind = shaderc_glsl_default_miss_shader;
		break;
	case Graphics::EShaderType::RTIntersection:
		kind = shaderc_glsl_default_intersection_shader;
		break;
	case Graphics::EShaderType::RTCallable:
		kind = shaderc_glsl_default_callable_shader;
		break;
	default:
		kind = shaderc_glsl_infer_from_source;
	}

	std::vector<std::uint32_t> code;

	auto result = s_compiler.CompileGlslToSpv(std::string { sourceString }, kind, "");

	if (result.GetCompilationStatus() == shaderc_compilation_status_success)
	{
		code = { result.begin(), result.end() };
	}
	else
	{
		Log::error(result.GetErrorMessage());
	}

	return code;
}

GLSLang::GLSLang()
{
}

GLSLang::~GLSLang()
{
}