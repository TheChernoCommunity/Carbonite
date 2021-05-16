//
//	Created by MarcasRealAccount on 13. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Application.h"
#include "Engine/Renderer/Apis/Vulkan/Material/VulkanMaterial.h"
#include "Engine/Renderer/Apis/Vulkan/Material/VulkanReservedUniformBuffers.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanStaticMesh.h"
#include "Engine/Renderer/Apis/Vulkan/Shader/VulkanShaderProgram.h"
#include "Engine/Renderer/Apis/Vulkan/VulkanRenderer.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Window/Window.h"

namespace gp1::renderer::vulkan
{
	std::shared_ptr<StaticMesh> VulkanRenderer::CreateStaticMesh()
	{
		return std::make_shared<VulkanStaticMesh>();
	}

	std::shared_ptr<Material> VulkanRenderer::CreateMaterial()
	{
		return std::make_shared<VulkanMaterial>();
	}

	std::shared_ptr<ShaderProgram> VulkanRenderer::CreateShader()
	{
		return std::make_shared<VulkanShaderProgram>();
	}

	bool VulkanRenderer::IsCompatible() const
	{
		return false;
	}

	void VulkanRenderer::SetWindowHints()
	{
		window::Window& window = Application::GetInstance()->GetWindow();
		window.SetWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	void VulkanRenderer::Init()
	{
		m_ReservedUniformBuffers = new VulkanReservedUniformBuffers();
	}

	void VulkanRenderer::DeInit()
	{
		delete m_ReservedUniformBuffers;
	}

	void VulkanRenderer::Render(scene::Camera* camera)
	{
		[[maybe_unused]] scene::Scene* scene = camera->GetScene();
	}
} // namespace gp1::renderer::vulkan

#endif