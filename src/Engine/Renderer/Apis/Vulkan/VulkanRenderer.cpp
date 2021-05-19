#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Application.h"
#include "Engine/Renderer/Apis/Vulkan/Material/VulkanMaterial.h"
#include "Engine/Renderer/Apis/Vulkan/Material/VulkanReservedUniformBuffers.h"
#include "Engine/Renderer/Apis/Vulkan/Material/VulkanUniform.h"
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

	std::shared_ptr<StaticMesh> VulkanRenderer::OnCreateStaticMesh()
	{
		return std::make_shared<VulkanStaticMesh>();
	}

	std::shared_ptr<Material> VulkanRenderer::OnCreateMaterial()
	{
		return std::make_shared<VulkanMaterial>();
	}

	std::shared_ptr<ReservedUniformBuffers> VulkanRenderer::OnCreateReversedUniformBuffers()
	{
		return std::make_shared<VulkanReservedUniformBuffers>();
	}

	std::shared_ptr<Uniform> VulkanRenderer::OnCreateUniform(EUniformType type)
	{
		switch (type)
		{
		case EUniformType::Float: return std::make_shared<VulkanUniformFloat>();
		case EUniformType::FVec2: return std::make_shared<VulkanUniformFVec2>();
		case EUniformType::FVec3: return std::make_shared<VulkanUniformFVec3>();
		case EUniformType::FVec4: return std::make_shared<VulkanUniformFVec4>();
		case EUniformType::Int: return std::make_shared<VulkanUniformInt>();
		case EUniformType::IVec2: return std::make_shared<VulkanUniformIVec2>();
		case EUniformType::IVec3: return std::make_shared<VulkanUniformIVec3>();
		case EUniformType::IVec4: return std::make_shared<VulkanUniformIVec4>();
		case EUniformType::UInt: return std::make_shared<VulkanUniformUInt>();
		case EUniformType::UVec2: return std::make_shared<VulkanUniformUVec2>();
		case EUniformType::UVec3: return std::make_shared<VulkanUniformUVec3>();
		case EUniformType::UVec4: return std::make_shared<VulkanUniformUVec4>();
		case EUniformType::FMat2: return std::make_shared<VulkanUniformFMat2>();
		case EUniformType::FMat3: return std::make_shared<VulkanUniformFMat3>();
		case EUniformType::FMat4: return std::make_shared<VulkanUniformFMat4>();
		case EUniformType::Texture2D: return std::make_shared<VulkanUniformTexture2D>();
		case EUniformType::Texture2DArray: return std::make_shared<VulkanUniformTexture2DArray>();
		case EUniformType::Texture3D: return std::make_shared<VulkanUniformTexture3D>();
		case EUniformType::TextureCubeMap: return std::make_shared<VulkanUniformTextureCubeMap>();
		default: return nullptr;
		}
	}

	std::shared_ptr<UniformBuffer> VulkanRenderer::OnCreateUniformBuffer()
	{
		return std::make_shared<VulkanUniformBuffer>();
	}

	std::shared_ptr<ShaderProgram> VulkanRenderer::OnCreateShaderProgram()
	{
		return std::make_shared<VulkanShaderProgram>();
	}

	std::shared_ptr<DebugRenderer> VulkanRenderer::OnCreateDebugRenderer()
	{
		return std::make_shared<VulkanDebugRenderer>();
	}

	std::shared_ptr<Texture2D> VulkanRenderer::OnCreateTexture2D()
	{
		return std::make_shared<VulkanTexture2D>();
	}

	std::shared_ptr<Texture2DArray> VulkanRenderer::OnCreateTexture2DArray()
	{
		return std::make_shared<VulkanTexture2DArray>();
	}

	std::shared_ptr<Texture3D> VulkanRenderer::OnCreateTexture3D()
	{
		return std::make_shared<VulkanTexture3D>();
	}

	std::shared_ptr<TextureCubeMap> VulkanRenderer::OnCreateTextureCubeMap()
	{
		return std::make_shared<VulkanTextureCubeMap>();
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

	void VulkanRenderer::OnRender(std::shared_ptr<scene::Camera> camera)
	{
		[[maybe_unused]] scene::Scene* scene = camera->GetScene();
	}
} // namespace gp1::renderer::vulkan

#endif