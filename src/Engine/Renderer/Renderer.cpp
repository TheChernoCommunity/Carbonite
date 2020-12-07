//
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Apis/OpenGL/OpenGLRenderer.h"
#include "Engine/Renderer/Apis/Vulkan/VulkanRenderer.h"
#include "Engine/Renderer/DebugRenderer.h"
#include "Engine/Renderer/RendererData.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Window/Window.h"

namespace gp1::renderer
{
	Renderer::Renderer(window::Window* window)
	    : m_Window(window) {}

	void Renderer::Init()
	{
		InitRenderer();
		debug::DebugRenderer::SetDebugRenderer(CreateDebugRenderer());
	}

	void Renderer::DeInit()
	{
		debug::DebugRenderer::CleanUp();
		DeInitRenderer();
	}

	void Renderer::Render(scene::Scene* scene)
	{
		scene::Camera* mainCamera = scene->GetMainCamera();
		if (mainCamera)
		{
			mainCamera->m_Aspect = (float) m_Window->m_WindowData.FramebufferWidth / m_Window->m_WindowData.FramebufferHeight;
			RenderScene(scene, m_Window->m_WindowData.FramebufferWidth, m_Window->m_WindowData.FramebufferHeight);
		}
	}

	bool Renderer::IsDebugRendererUsable(debug::DebugRenderer* debugRenderer)
	{
		return debugRenderer->GetRendererType() == GetRendererType();
	}

	bool Renderer::IsRendererDataUsable(RendererData* rendererData)
	{
		return rendererData->GetRendererType() == GetRendererType();
	}

	GLFWwindow* Renderer::GetNativeWindowHandle() const
	{
		return this->m_Window->m_NativeHandle;
	}

	debug::DebugRenderer* Renderer::GetDebugRenderer()
	{
		return debug::DebugRenderer::s_DebugRenderer;
	}

	Renderer* Renderer::GetRenderer(RendererType rendererType, window::Window* window)
	{
		switch (rendererType)
		{
		case RendererType::OPENGL:
			return new apis::opengl::OpenGLRenderer(window);
		case RendererType::VULKAN:
			return new apis::vulkan::VulkanRenderer(window);
		}
		return nullptr;
	}

} // namespace gp1::renderer
