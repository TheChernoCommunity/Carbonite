//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Apis/OpenGL/OpenGLRenderer.h"
#include "Engine/Renderer/Apis/Vulkan/VulkanRenderer.h"
#include "Engine/Renderer/Mesh/Mesh.h"
#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Renderer/Shader/Material.h"
#include "Engine/Window/Window.h"

namespace gp1 {

	Renderer::Renderer(Window* window)
		: m_Window(window) {}

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
