#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Application.h"
#include "Engine/Renderer/Apis/Vulkan/Material/VulkanMaterial.h"
#include "Engine/Renderer/Apis/Vulkan/Material/VulkanReservedUniformBuffers.h"
#include "Engine/Renderer/Apis/Vulkan/Material/VulkanUniform.h"
#include "Engine/Renderer/Apis/Vulkan/Material/VulkanUniformBuffer.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanStaticMesh.h"
#include "Engine/Renderer/Apis/Vulkan/Shader/VulkanShaderProgram.h"
#include "Engine/Renderer/Apis/Vulkan/Texture/VulkanTexture2D.h"
#include "Engine/Renderer/Apis/Vulkan/Texture/VulkanTexture2DArray.h"
#include "Engine/Renderer/Apis/Vulkan/Texture/VulkanTexture3D.h"
#include "Engine/Renderer/Apis/Vulkan/Texture/VulkanTextureCubeMap.h"
#include "Engine/Renderer/Apis/Vulkan/VulkanDebugRenderer.h"
#include "Engine/Renderer/Apis/Vulkan/VulkanRenderer.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Window/Window.h"

namespace gp1::renderer::vulkan
{
	bool VulkanRenderer::IsCompatible() const
	{
		return false;
	}

	void VulkanRenderer::SetWindowHints()
	{
		window::Window& window = Application::GetInstance()->GetWindow();
		window.SetWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	std::unique_ptr<StaticMesh> VulkanRenderer::OnCreateStaticMesh()
	{
		return std::make_unique<VulkanStaticMesh>();
	}

	std::unique_ptr<Material> VulkanRenderer::OnCreateMaterial()
	{
		return std::make_unique<VulkanMaterial>();
	}

	std::unique_ptr<ReservedUniformBuffers> VulkanRenderer::OnCreateReservedUniformBuffers()
	{
		return std::make_unique<VulkanReservedUniformBuffers>();
	}

	std::unique_ptr<Uniform> VulkanRenderer::OnCreateUniform(EUniformType type)
	{
		switch (type)
		{
		case EUniformType::Float: return std::make_unique<VulkanUniformFloat>();
		case EUniformType::FVec2: return std::make_unique<VulkanUniformFVec2>();
		case EUniformType::FVec3: return std::make_unique<VulkanUniformFVec3>();
		case EUniformType::FVec4: return std::make_unique<VulkanUniformFVec4>();
		case EUniformType::Int: return std::make_unique<VulkanUniformInt>();
		case EUniformType::IVec2: return std::make_unique<VulkanUniformIVec2>();
		case EUniformType::IVec3: return std::make_unique<VulkanUniformIVec3>();
		case EUniformType::IVec4: return std::make_unique<VulkanUniformIVec4>();
		case EUniformType::UInt: return std::make_unique<VulkanUniformUInt>();
		case EUniformType::UVec2: return std::make_unique<VulkanUniformUVec2>();
		case EUniformType::UVec3: return std::make_unique<VulkanUniformUVec3>();
		case EUniformType::UVec4: return std::make_unique<VulkanUniformUVec4>();
		case EUniformType::FMat2: return std::make_unique<VulkanUniformFMat2>();
		case EUniformType::FMat3: return std::make_unique<VulkanUniformFMat3>();
		case EUniformType::FMat4: return std::make_unique<VulkanUniformFMat4>();
		case EUniformType::Texture2D: return std::make_unique<VulkanUniformTexture2D>();
		case EUniformType::Texture2DArray: return std::make_unique<VulkanUniformTexture2DArray>();
		case EUniformType::Texture3D: return std::make_unique<VulkanUniformTexture3D>();
		case EUniformType::TextureCubeMap: return std::make_unique<VulkanUniformTextureCubeMap>();
		default: return nullptr;
		}
	}

	std::unique_ptr<UniformBuffer> VulkanRenderer::OnCreateUniformBuffer()
	{
		return std::make_unique<VulkanUniformBuffer>();
	}

	std::unique_ptr<ShaderProgram> VulkanRenderer::OnCreateShaderProgram()
	{
		return std::make_unique<VulkanShaderProgram>();
	}

	std::unique_ptr<DebugRenderer> VulkanRenderer::OnCreateDebugRenderer()
	{
		return std::make_unique<VulkanDebugRenderer>();
	}

	std::unique_ptr<Texture2D> VulkanRenderer::OnCreateTexture2D()
	{
		return std::make_unique<VulkanTexture2D>();
	}

	std::unique_ptr<Texture2DArray> VulkanRenderer::OnCreateTexture2DArray()
	{
		return std::make_unique<VulkanTexture2DArray>();
	}

	std::unique_ptr<Texture3D> VulkanRenderer::OnCreateTexture3D()
	{
		return std::make_unique<VulkanTexture3D>();
	}

	std::unique_ptr<TextureCubeMap> VulkanRenderer::OnCreateTextureCubeMap()
	{
		return std::make_unique<VulkanTextureCubeMap>();
	}

	void VulkanRenderer::OnInit()
	{
	}

	void VulkanRenderer::OnDeInit()
	{
	}

	void VulkanRenderer::OnBeginFrame()
	{
	}

	void VulkanRenderer::OnEndFrame()
	{
	}

	void VulkanRenderer::OnRender(scene::Camera* camera)
	{
		[[maybe_unused]] scene::Scene* scene = camera->GetScene();
	}
} // namespace gp1::renderer::vulkan

#endif