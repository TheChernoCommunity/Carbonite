//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/DebugRenderer.h"
#include "Engine/Renderer/Apis/OpenGL/OpenGLRenderer.h"
#include "Engine/Renderer/Apis/Vulkan/VulkanRenderer.h"
#include "Engine/Renderer/Mesh/Mesh.h"
#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Renderer/Shader/Material.h"
#include "Engine/Window/Window.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Camera.h"

namespace gp1 {

	Renderer::Renderer(Window* window)
		: m_Window(window) {}

	void Renderer::Init() {
		InitRenderer();
		DebugRenderer::SetDebugRenderer(CreateDebugRenderer());
	}

	void Renderer::DeInit() {
		DebugRenderer::CleanUp();
		DeInitRenderer();
	}

	void Renderer::Render(Scene* scene) {
		Camera* mainCamera = scene->GetMainCamera();
		if (mainCamera) {
			mainCamera->m_Aspect = (float)m_Window->m_WindowData.FramebufferWidth / m_Window->m_WindowData.FramebufferHeight;
			RenderScene(scene, m_Window->m_WindowData.FramebufferWidth, m_Window->m_WindowData.FramebufferHeight);
		}
	}

	bool Renderer::IsDebugRendererUsable(DebugRenderer* debugRenderer) {
		return debugRenderer->GetRendererType() == GetRendererType();
	}

	bool Renderer::IsMeshDataUsable(MeshData* meshData) {
		return meshData->GetRendererType() == GetRendererType();
	}

	bool Renderer::IsShaderDataUsable(ShaderData* shaderData) {
		return shaderData->GetRendererType() == GetRendererType();
	}

	bool Renderer::IsMaterialDataUsable(MaterialData* materialData) {
		return materialData->GetRendererType() == GetRendererType();
	}

	GLFWwindow* Renderer::GetNativeWindowHandle() const {
		return this->m_Window->m_NativeHandle;
	}

	DebugRenderer* Renderer::GetDebugRenderer() {
		return DebugRenderer::m_DebugRenderer;
	}

	Renderer* Renderer::GetRenderer(RendererType rendererType, Window* window) {
		switch (rendererType) {
		case RendererType::OPENGL:
			return new OpenGLRenderer(window);
		case RendererType::VULKAN:
			return new VulkanRenderer(window);
		}
		return nullptr;
	}

} // namespace gp1
