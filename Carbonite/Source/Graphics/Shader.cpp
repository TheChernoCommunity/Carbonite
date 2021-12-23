#include "PCH.h"

#include <glslang/Include/ResourceLimits.h>
#include <glslang/SPIRV/GlslangToSpv.h>

#include "Graphics/Shader.h"
#include "Log.h"

namespace
{
	unsigned m_ShaderCount = 0;

	void initResources(TBuiltInResource& Resources)
	{
		Resources.maxLights                                   = 32;
		Resources.maxClipPlanes                               = 6;
		Resources.maxTextureUnits                             = 32;
		Resources.maxTextureCoords                            = 32;
		Resources.maxVertexAttribs                            = 64;
		Resources.maxVertexUniformComponents                  = 4096;
		Resources.maxVaryingFloats                            = 64;
		Resources.maxVertexTextureImageUnits                  = 32;
		Resources.maxCombinedTextureImageUnits                = 80;
		Resources.maxTextureImageUnits                        = 32;
		Resources.maxFragmentUniformComponents                = 4096;
		Resources.maxDrawBuffers                              = 32;
		Resources.maxVertexUniformVectors                     = 128;
		Resources.maxVaryingVectors                           = 8;
		Resources.maxFragmentUniformVectors                   = 16;
		Resources.maxVertexOutputVectors                      = 16;
		Resources.maxFragmentInputVectors                     = 15;
		Resources.minProgramTexelOffset                       = -8;
		Resources.maxProgramTexelOffset                       = 7;
		Resources.maxClipDistances                            = 8;
		Resources.maxComputeWorkGroupCountX                   = 65535;
		Resources.maxComputeWorkGroupCountY                   = 65535;
		Resources.maxComputeWorkGroupCountZ                   = 65535;
		Resources.maxComputeWorkGroupSizeX                    = 1024;
		Resources.maxComputeWorkGroupSizeY                    = 1024;
		Resources.maxComputeWorkGroupSizeZ                    = 64;
		Resources.maxComputeUniformComponents                 = 1024;
		Resources.maxComputeTextureImageUnits                 = 16;
		Resources.maxComputeImageUniforms                     = 8;
		Resources.maxComputeAtomicCounters                    = 8;
		Resources.maxComputeAtomicCounterBuffers              = 1;
		Resources.maxVaryingComponents                        = 60;
		Resources.maxVertexOutputComponents                   = 64;
		Resources.maxGeometryInputComponents                  = 64;
		Resources.maxGeometryOutputComponents                 = 128;
		Resources.maxFragmentInputComponents                  = 128;
		Resources.maxImageUnits                               = 8;
		Resources.maxCombinedImageUnitsAndFragmentOutputs     = 8;
		Resources.maxCombinedShaderOutputResources            = 8;
		Resources.maxImageSamples                             = 0;
		Resources.maxVertexImageUniforms                      = 0;
		Resources.maxTessControlImageUniforms                 = 0;
		Resources.maxTessEvaluationImageUniforms              = 0;
		Resources.maxGeometryImageUniforms                    = 0;
		Resources.maxFragmentImageUniforms                    = 8;
		Resources.maxCombinedImageUniforms                    = 8;
		Resources.maxGeometryTextureImageUnits                = 16;
		Resources.maxGeometryOutputVertices                   = 256;
		Resources.maxGeometryTotalOutputComponents            = 1024;
		Resources.maxGeometryUniformComponents                = 1024;
		Resources.maxGeometryVaryingComponents                = 64;
		Resources.maxTessControlInputComponents               = 128;
		Resources.maxTessControlOutputComponents              = 128;
		Resources.maxTessControlTextureImageUnits             = 16;
		Resources.maxTessControlUniformComponents             = 1024;
		Resources.maxTessControlTotalOutputComponents         = 4096;
		Resources.maxTessEvaluationInputComponents            = 128;
		Resources.maxTessEvaluationOutputComponents           = 128;
		Resources.maxTessEvaluationTextureImageUnits          = 16;
		Resources.maxTessEvaluationUniformComponents          = 1024;
		Resources.maxTessPatchComponents                      = 120;
		Resources.maxPatchVertices                            = 32;
		Resources.maxTessGenLevel                             = 64;
		Resources.maxViewports                                = 16;
		Resources.maxVertexAtomicCounters                     = 0;
		Resources.maxTessControlAtomicCounters                = 0;
		Resources.maxTessEvaluationAtomicCounters             = 0;
		Resources.maxGeometryAtomicCounters                   = 0;
		Resources.maxFragmentAtomicCounters                   = 8;
		Resources.maxCombinedAtomicCounters                   = 8;
		Resources.maxAtomicCounterBindings                    = 1;
		Resources.maxVertexAtomicCounterBuffers               = 0;
		Resources.maxTessControlAtomicCounterBuffers          = 0;
		Resources.maxTessEvaluationAtomicCounterBuffers       = 0;
		Resources.maxGeometryAtomicCounterBuffers             = 0;
		Resources.maxFragmentAtomicCounterBuffers             = 1;
		Resources.maxCombinedAtomicCounterBuffers             = 1;
		Resources.maxAtomicCounterBufferSize                  = 16384;
		Resources.maxTransformFeedbackBuffers                 = 4;
		Resources.maxTransformFeedbackInterleavedComponents   = 64;
		Resources.maxCullDistances                            = 8;
		Resources.maxCombinedClipAndCullDistances             = 8;
		Resources.maxSamples                                  = 4;
		Resources.maxMeshOutputVerticesNV                     = 256;
		Resources.maxMeshOutputPrimitivesNV                   = 512;
		Resources.maxMeshWorkGroupSizeX_NV                    = 32;
		Resources.maxMeshWorkGroupSizeY_NV                    = 1;
		Resources.maxMeshWorkGroupSizeZ_NV                    = 1;
		Resources.maxTaskWorkGroupSizeX_NV                    = 32;
		Resources.maxTaskWorkGroupSizeY_NV                    = 1;
		Resources.maxTaskWorkGroupSizeZ_NV                    = 1;
		Resources.maxMeshViewCountNV                          = 4;
		Resources.limits.nonInductiveForLoops                 = 1;
		Resources.limits.whileLoops                           = 1;
		Resources.limits.doWhileLoops                         = 1;
		Resources.limits.generalUniformIndexing               = 1;
		Resources.limits.generalAttributeMatrixVectorIndexing = 1;
		Resources.limits.generalVaryingIndexing               = 1;
		Resources.limits.generalSamplerIndexing               = 1;
		Resources.limits.generalVariableIndexing              = 1;
		Resources.limits.generalConstantMatrixVectorIndexing  = 1;
	}

} // namespace

namespace Graphics
{
	Shader::Shader(Device& device, const Asset asset)
	    : m_device(device), m_sourceStr(asset.data.get()), m_type(static_cast<ShaderType>(asset.type))
	{
		if (m_ShaderCount == 0)
		{
			glslang::InitializeProcess();
		}

		m_device.addChild(this);

		m_ShaderCount++;
	}

	Shader::Shader(Device& device, const std::string& source, const ShaderType type)
	    : m_device(device), m_sourceStr(source), m_type(type)
	{
		if (m_ShaderCount == 0)
		{
			glslang::InitializeProcess();
		}

		m_device.addChild(this);

		m_ShaderCount++;
	}

	void Shader::createImpl()
	{
		EShLanguage lang;

		switch (m_type)
		{
		case ShaderType::Vertex:
			lang = EShLangVertex;
			break;
		case ShaderType::Fragment:
			lang = EShLangFragment;
			break;
		case ShaderType::TessellationControl:
			lang = EShLangTessControl;
			break;
		case ShaderType::TessellationEvaluation:
			lang = EShLangTessEvaluation;
			break;
		case ShaderType::Geometry:
			lang = EShLangGeometry;
			break;
		case ShaderType::Compute:
			lang = EShLangCompute;
			break;
		default:
			return;
		}

		glslang::TShader  shader(lang);
		glslang::TProgram program;

		TBuiltInResource Resources = {};
		initResources(Resources);

		EShMessages messages = (EShMessages) (EShMsgSpvRules | EShMsgVulkanRules);

		const char* string = m_sourceStr.c_str();
		const int   length = static_cast<int>(m_sourceStr.length());

		shader.setStringsWithLengths(&string, &length, 1);

		if (!shader.parse(&Resources, 100, false, messages))
		{
			Log::error(shader.getInfoLog());
			Log::debug(shader.getInfoDebugLog());
		}

		program.addShader(&shader);

		if (program.link(messages))
		{
			std::vector<unsigned int> spirv;
			glslang::GlslangToSpv(*(program.getIntermediate(lang)), spirv);
			vk::ShaderModuleCreateInfo createInfo = { {}, spirv };
			m_Handle                              = m_device->createShaderModule(createInfo);

			Log::debug("Compiled shaders!");
		}
		else
		{
			Log::error(shader.getInfoLog());
			Log::debug(shader.getInfoDebugLog());
		}
	}

	void Shader::setSourceStr(const std::string& source)
	{
		m_sourceStr = source;
	}

	ShaderType Shader::getType() const
	{
		return m_type;
	}

	bool Shader::destroyImpl()
	{
		m_device->destroy(m_Handle);
		return true;
	}

	Shader::~Shader()
	{
		if (isValid())
			destroy();

		m_ShaderCount--;

		if (m_ShaderCount == 0)
		{
			glslang::FinalizeProcess();
		}

		m_device.removeChild(this);
	}

} // namespace Graphics
