#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Apis/Vulkan/Material/VulkanMaterial.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanStaticMesh.h"
#include "Engine/Renderer/Apis/Vulkan/Shader/VulkanShaderProgram.h"
#include "Engine/Renderer/Apis/Vulkan/VulkanRenderer.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Window/Window.h"

namespace gp1::renderer::vulkan
{
	VulkanRenderer::VulkanRenderer(window::Window* window)
	    : Renderer(window) {}

	StaticMesh* VulkanRenderer::CreateStaticMesh()
	{
		return new VulkanStaticMesh();
	}

	Material* VulkanRenderer::CreateMaterial()
	{
		return new VulkanMaterial();
	}

	ShaderProgram* VulkanRenderer::CreateShader()
	{
		return new VulkanShaderProgram();
	}

	bool VulkanRenderer::IsCompatible() const
	{
		return false;
	}

	void VulkanRenderer::SetWindowHints()
	{
		m_Window->SetWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	void VulkanRenderer::Init()
	{
	}

	void VulkanRenderer::DeInit()
	{
	}

	void VulkanRenderer::Render(scene::Camera* camera)
	{
		[[maybe_unused]] scene::Scene* scene = camera->GetScene();
	}
} // namespace gp1::renderer::vulkan

#endif