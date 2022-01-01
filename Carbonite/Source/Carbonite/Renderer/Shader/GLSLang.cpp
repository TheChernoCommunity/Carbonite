#include "PCH.h"

#include "GLSLang.h"
#include "Utils/Log.h"

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
	if (!m_Initialized)
	{
		glslang::InitializeProcess();
		m_Initialized = true;
	}

	EShLanguage lang;
	switch (shaderType)
	{
	case Graphics::EShaderType::Vertex:
		lang = EShLangVertex;
		break;
	case Graphics::EShaderType::TessControl:
		lang = EShLangTessControl;
		break;
	case Graphics::EShaderType::TessEvaluation:
		lang = EShLangTessEvaluation;
		break;
	case Graphics::EShaderType::Geometry:
		lang = EShLangGeometry;
		break;
	case Graphics::EShaderType::Fragment:
		lang = EShLangFragment;
		break;
	case Graphics::EShaderType::Compute:
		lang = EShLangCompute;
		break;
	case Graphics::EShaderType::RTRayGen:
		lang = EShLangRayGen;
		break;
	case Graphics::EShaderType::RTAnyHit:
		lang = EShLangAnyHit;
		break;
	case Graphics::EShaderType::RTClosestHit:
		lang = EShLangClosestHit;
		break;
	case Graphics::EShaderType::RTMiss:
		lang = EShLangMiss;
		break;
	case Graphics::EShaderType::RTIntersection:
		lang = EShLangIntersect;
		break;
	case Graphics::EShaderType::RTCallable:
		lang = EShLangCallable;
		break;
	default:
		lang = EShLangCompute;
	}

	glslang::TShader  shader(lang);
	glslang::TProgram program;

	EShMessages messages = static_cast<EShMessages>(EShMsgSpvRules | EShMsgVulkanRules);

	const char*  strings[] { sourceString.data() };
	std::int32_t lengths[] { static_cast<std::int32_t>(sourceString.size()) };

	shader.setStringsWithLengths(strings, lengths, sizeof(strings) / sizeof(strings[0]));

	if (!shader.parse(&m_Resources, 100, false, messages))
	{
		Log::error(shader.getInfoLog());
		Log::debug(shader.getInfoDebugLog());
	}

	program.addShader(&shader);

	if (!program.link(messages))
	{
		Log::error(program.getInfoLog());
		Log::debug(program.getInfoDebugLog());
	}

	std::vector<std::uint32_t> code;
	glslang::GlslangToSpv(*program.getIntermediate(lang), code);
	return code;
}

GLSLang::GLSLang()
{
	m_Resources.maxLights                                   = 32;
	m_Resources.maxClipPlanes                               = 6;
	m_Resources.maxTextureUnits                             = 32;
	m_Resources.maxTextureCoords                            = 32;
	m_Resources.maxVertexAttribs                            = 64;
	m_Resources.maxVertexUniformComponents                  = 4096;
	m_Resources.maxVaryingFloats                            = 64;
	m_Resources.maxVertexTextureImageUnits                  = 32;
	m_Resources.maxCombinedTextureImageUnits                = 80;
	m_Resources.maxTextureImageUnits                        = 32;
	m_Resources.maxFragmentUniformComponents                = 4096;
	m_Resources.maxDrawBuffers                              = 32;
	m_Resources.maxVertexUniformVectors                     = 128;
	m_Resources.maxVaryingVectors                           = 8;
	m_Resources.maxFragmentUniformVectors                   = 16;
	m_Resources.maxVertexOutputVectors                      = 16;
	m_Resources.maxFragmentInputVectors                     = 15;
	m_Resources.minProgramTexelOffset                       = -8;
	m_Resources.maxProgramTexelOffset                       = 7;
	m_Resources.maxClipDistances                            = 8;
	m_Resources.maxComputeWorkGroupCountX                   = 65535;
	m_Resources.maxComputeWorkGroupCountY                   = 65535;
	m_Resources.maxComputeWorkGroupCountZ                   = 65535;
	m_Resources.maxComputeWorkGroupSizeX                    = 1024;
	m_Resources.maxComputeWorkGroupSizeY                    = 1024;
	m_Resources.maxComputeWorkGroupSizeZ                    = 64;
	m_Resources.maxComputeUniformComponents                 = 1024;
	m_Resources.maxComputeTextureImageUnits                 = 16;
	m_Resources.maxComputeImageUniforms                     = 8;
	m_Resources.maxComputeAtomicCounters                    = 8;
	m_Resources.maxComputeAtomicCounterBuffers              = 1;
	m_Resources.maxVaryingComponents                        = 60;
	m_Resources.maxVertexOutputComponents                   = 64;
	m_Resources.maxGeometryInputComponents                  = 64;
	m_Resources.maxGeometryOutputComponents                 = 128;
	m_Resources.maxFragmentInputComponents                  = 128;
	m_Resources.maxImageUnits                               = 8;
	m_Resources.maxCombinedImageUnitsAndFragmentOutputs     = 8;
	m_Resources.maxCombinedShaderOutputResources            = 8;
	m_Resources.maxImageSamples                             = 0;
	m_Resources.maxVertexImageUniforms                      = 0;
	m_Resources.maxTessControlImageUniforms                 = 0;
	m_Resources.maxTessEvaluationImageUniforms              = 0;
	m_Resources.maxGeometryImageUniforms                    = 0;
	m_Resources.maxFragmentImageUniforms                    = 8;
	m_Resources.maxCombinedImageUniforms                    = 8;
	m_Resources.maxGeometryTextureImageUnits                = 16;
	m_Resources.maxGeometryOutputVertices                   = 256;
	m_Resources.maxGeometryTotalOutputComponents            = 1024;
	m_Resources.maxGeometryUniformComponents                = 1024;
	m_Resources.maxGeometryVaryingComponents                = 64;
	m_Resources.maxTessControlInputComponents               = 128;
	m_Resources.maxTessControlOutputComponents              = 128;
	m_Resources.maxTessControlTextureImageUnits             = 16;
	m_Resources.maxTessControlUniformComponents             = 1024;
	m_Resources.maxTessControlTotalOutputComponents         = 4096;
	m_Resources.maxTessEvaluationInputComponents            = 128;
	m_Resources.maxTessEvaluationOutputComponents           = 128;
	m_Resources.maxTessEvaluationTextureImageUnits          = 16;
	m_Resources.maxTessEvaluationUniformComponents          = 1024;
	m_Resources.maxTessPatchComponents                      = 120;
	m_Resources.maxPatchVertices                            = 32;
	m_Resources.maxTessGenLevel                             = 64;
	m_Resources.maxViewports                                = 16;
	m_Resources.maxVertexAtomicCounters                     = 0;
	m_Resources.maxTessControlAtomicCounters                = 0;
	m_Resources.maxTessEvaluationAtomicCounters             = 0;
	m_Resources.maxGeometryAtomicCounters                   = 0;
	m_Resources.maxFragmentAtomicCounters                   = 8;
	m_Resources.maxCombinedAtomicCounters                   = 8;
	m_Resources.maxAtomicCounterBindings                    = 1;
	m_Resources.maxVertexAtomicCounterBuffers               = 0;
	m_Resources.maxTessControlAtomicCounterBuffers          = 0;
	m_Resources.maxTessEvaluationAtomicCounterBuffers       = 0;
	m_Resources.maxGeometryAtomicCounterBuffers             = 0;
	m_Resources.maxFragmentAtomicCounterBuffers             = 1;
	m_Resources.maxCombinedAtomicCounterBuffers             = 1;
	m_Resources.maxAtomicCounterBufferSize                  = 16384;
	m_Resources.maxTransformFeedbackBuffers                 = 4;
	m_Resources.maxTransformFeedbackInterleavedComponents   = 64;
	m_Resources.maxCullDistances                            = 8;
	m_Resources.maxCombinedClipAndCullDistances             = 8;
	m_Resources.maxSamples                                  = 4;
	m_Resources.maxMeshOutputVerticesNV                     = 256;
	m_Resources.maxMeshOutputPrimitivesNV                   = 512;
	m_Resources.maxMeshWorkGroupSizeX_NV                    = 32;
	m_Resources.maxMeshWorkGroupSizeY_NV                    = 1;
	m_Resources.maxMeshWorkGroupSizeZ_NV                    = 1;
	m_Resources.maxTaskWorkGroupSizeX_NV                    = 32;
	m_Resources.maxTaskWorkGroupSizeY_NV                    = 1;
	m_Resources.maxTaskWorkGroupSizeZ_NV                    = 1;
	m_Resources.maxMeshViewCountNV                          = 4;
	m_Resources.limits.nonInductiveForLoops                 = 1;
	m_Resources.limits.whileLoops                           = 1;
	m_Resources.limits.doWhileLoops                         = 1;
	m_Resources.limits.generalUniformIndexing               = 1;
	m_Resources.limits.generalAttributeMatrixVectorIndexing = 1;
	m_Resources.limits.generalVaryingIndexing               = 1;
	m_Resources.limits.generalSamplerIndexing               = 1;
	m_Resources.limits.generalVariableIndexing              = 1;
	m_Resources.limits.generalConstantMatrixVectorIndexing  = 1;
}

GLSLang::~GLSLang()
{
	if (m_Initialized)
	{
		glslang::FinalizeProcess();
		m_Initialized = false;
	}
}