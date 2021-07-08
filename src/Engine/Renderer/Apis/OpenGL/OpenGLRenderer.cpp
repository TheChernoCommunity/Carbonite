//
//	Created by MarcasRealAccount on 13. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Application.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLMaterial.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLReservedUniformBuffers.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLUniform.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLUniformBuffer.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLStaticMesh.h"
#include "Engine/Renderer/Apis/OpenGL/OpenGLDebugRenderer.h"
#include "Engine/Renderer/Apis/OpenGL/OpenGLRenderer.h"
#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLShaderProgram.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture2D.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture2DArray.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture3D.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTextureCubeMap.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Window/Window.h"

#include <stdexcept>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace gp1::renderer::opengl
{
	bool OpenGLRenderer::IsCompatible() const
	{
		if (!glfwInit())
			return false;

		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		GLFWwindow* window = glfwCreateWindow(100, 100, "I'm a cool opengl window", nullptr, nullptr);

		glfwMakeContextCurrent(window);

		bool result = static_cast<bool>(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)));

		glfwDestroyWindow(window);

		return result && GLVersion.major >= 4 && GLVersion.minor >= 1;
	}

	void OpenGLRenderer::SetWindowHints()
	{
		window::Window& window = Application::GetInstance()->GetWindow();
		window.SetWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		window.SetWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		window.SetWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		window.SetWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window.SetWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
	}

	std::unique_ptr<StaticMesh> OpenGLRenderer::OnCreateStaticMesh()
	{
		return std::make_unique<OpenGLStaticMesh>();
	}

	std::unique_ptr<Material> OpenGLRenderer::OnCreateMaterial()
	{
		return std::make_unique<OpenGLMaterial>();
	}

	std::unique_ptr<ReservedUniformBuffers> OpenGLRenderer::OnCreateReservedUniformBuffers()
	{
		return std::make_unique<OpenGLReservedUniformBuffers>();
	}

	std::unique_ptr<Uniform> OpenGLRenderer::OnCreateUniform(EUniformType type)
	{
		switch (type)
		{
		case EUniformType::Float: return std::make_unique<OpenGLUniformFloat>();
		case EUniformType::FVec2: return std::make_unique<OpenGLUniformFVec2>();
		case EUniformType::FVec3: return std::make_unique<OpenGLUniformFVec3>();
		case EUniformType::FVec4: return std::make_unique<OpenGLUniformFVec4>();
		case EUniformType::Int: return std::make_unique<OpenGLUniformInt>();
		case EUniformType::IVec2: return std::make_unique<OpenGLUniformIVec2>();
		case EUniformType::IVec3: return std::make_unique<OpenGLUniformIVec3>();
		case EUniformType::IVec4: return std::make_unique<OpenGLUniformIVec4>();
		case EUniformType::UInt: return std::make_unique<OpenGLUniformUInt>();
		case EUniformType::UVec2: return std::make_unique<OpenGLUniformUVec2>();
		case EUniformType::UVec3: return std::make_unique<OpenGLUniformUVec3>();
		case EUniformType::UVec4: return std::make_unique<OpenGLUniformUVec4>();
		case EUniformType::FMat2: return std::make_unique<OpenGLUniformFMat2>();
		case EUniformType::FMat3: return std::make_unique<OpenGLUniformFMat3>();
		case EUniformType::FMat4: return std::make_unique<OpenGLUniformFMat4>();
		case EUniformType::Texture2D: return std::make_unique<OpenGLUniformTexture2D>();
		case EUniformType::Texture2DArray: return std::make_unique<OpenGLUniformTexture2DArray>();
		case EUniformType::Texture3D: return std::make_unique<OpenGLUniformTexture3D>();
		case EUniformType::TextureCubeMap: return std::make_unique<OpenGLUniformTextureCubeMap>();
		default: return nullptr;
		}
	}

	std::unique_ptr<UniformBuffer> OpenGLRenderer::OnCreateUniformBuffer()
	{
		return std::make_unique<OpenGLUniformBuffer>();
	}

	std::unique_ptr<ShaderProgram> OpenGLRenderer::OnCreateShaderProgram()
	{
		return std::make_unique<OpenGLShaderProgram>();
	}

	std::unique_ptr<DebugRenderer> OpenGLRenderer::OnCreateDebugRenderer()
	{
		return std::make_unique<OpenGLDebugRenderer>();
	}

	std::unique_ptr<Texture2D> OpenGLRenderer::OnCreateTexture2D()
	{
		return std::make_unique<OpenGLTexture2D>();
	}

	std::unique_ptr<Texture2DArray> OpenGLRenderer::OnCreateTexture2DArray()
	{
		return std::make_unique<OpenGLTexture2DArray>();
	}

	std::unique_ptr<Texture3D> OpenGLRenderer::OnCreateTexture3D()
	{
		return std::make_unique<OpenGLTexture3D>();
	}

	std::unique_ptr<TextureCubeMap> OpenGLRenderer::OnCreateTextureCubeMap()
	{
		return std::make_unique<OpenGLTextureCubeMap>();
	}

	void OpenGLRenderer::OnInit()
	{
		window::Window& window = Application::GetInstance()->GetWindow();
		glfwMakeContextCurrent(window.GetNativeHandle());

		if (GLVersion.major == 0 && GLVersion.minor == 0 && !gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
			throw std::runtime_error("Could not load OpenGL!");

		Application::GetInstance()->GetWindow().SetVSync(false);
	}

	void OpenGLRenderer::OnDeInit()
	{
	}

	void OpenGLRenderer::OnBeginFrame()
	{
		const window::WindowData& windowData = Application::GetInstance()->GetWindow().GetWindowData();
		glViewport(0, 0, windowData.FramebufferWidth, windowData.FramebufferHeight);
	}

	void OpenGLRenderer::OnEndFrame()
	{
	}

	void OpenGLRenderer::OnRender(scene::Camera* camera)
	{
		if (!camera)
			return;

		//----
		// TODO(MarcasRealAccount): This should only be called for the main camera that's rendering to the window.
		const window::WindowData& windowData = Application::GetInstance()->GetWindow().GetWindowData();
		camera->m_Aspect                     = static_cast<float>(windowData.FramebufferWidth) / static_cast<float>(windowData.FramebufferHeight);
		glClearColor(camera->m_ClearColor.r, camera->m_ClearColor.g, camera->m_ClearColor.b, camera->m_ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		//----

		scene::Scene* scene = camera->GetScene();

		OpenGLReservedUniformBuffers* reservedUniformBuffers = reinterpret_cast<OpenGLReservedUniformBuffers*>(m_ReservedUniformBuffers.get());

		UniformFMat4* projectionViewMatrixUniform = reservedUniformBuffers->GetUniform<UniformFMat4>("Camera", "projectionViewMatrix");
		if (projectionViewMatrixUniform && projectionViewMatrixUniform->GetType() == UniformFMat4::GetTypeS())
			projectionViewMatrixUniform->SetValue(camera->GetProjectionViewMatrix());

		UniformFMat4* projectionMatrixUniform = reservedUniformBuffers->GetUniform<UniformFMat4>("Camera", "projectionMatrix");
		if (projectionMatrixUniform && projectionMatrixUniform->GetType() == UniformFMat4::GetTypeS())
			projectionMatrixUniform->SetValue(camera->GetProjectionMatrix());

		UniformFMat4* viewMatrixUniform = reservedUniformBuffers->GetUniform<UniformFMat4>("Camera", "viewMatrix");
		if (viewMatrixUniform && viewMatrixUniform->GetType() == UniformFMat4::GetTypeS())
			viewMatrixUniform->SetValue(camera->GetTransformationMatrix(true));

		reservedUniformBuffers->Bind();

		for (auto renderable : scene->GetRenderableEntities())
			RenderEntity(renderable);

		OpenGLDebugRenderer* debugRenderer = reinterpret_cast<OpenGLDebugRenderer*>(m_DebugRenderer.get());
		debugRenderer->Render();

		glfwSwapBuffers(Application::GetInstance()->GetWindow().GetNativeHandle());
	}

	void OpenGLRenderer::RenderEntity(scene::RenderableEntity* entity)
	{
		OpenGLMaterial* material = reinterpret_cast<OpenGLMaterial*>(entity->GetMaterial());
		OpenGLMesh*     mesh     = reinterpret_cast<OpenGLMesh*>(entity->GetMesh()->GetNext());

		UniformFMat4* transformationMatrixUniform = material->GetUniform<UniformFMat4>("Object", "transformationMatrix");
		if (transformationMatrixUniform && transformationMatrixUniform->GetType() == UniformFMat4::GetTypeS())
			transformationMatrixUniform->SetValue(entity->GetTransformationMatrix());

		material->Bind();
		mesh->Render();
		material->Unbind();
	}
} // namespace gp1::renderer::opengl

#endif