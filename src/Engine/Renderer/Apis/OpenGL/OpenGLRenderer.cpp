//
//	Created by MarcasRealAccount on 13. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Application.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLMaterial.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLReservedUniformBuffers.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLStaticMesh.h"
#include "Engine/Renderer/Apis/OpenGL/OpenGLDebugRenderer.h"
#include "Engine/Renderer/Apis/OpenGL/OpenGLRenderer.h"
#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLShaderProgram.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Window/Window.h"

#include <sstream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace gp1::renderer::opengl
{
	std::shared_ptr<StaticMesh> OpenGLRenderer::CreateStaticMesh()
	{
		return std::make_shared<OpenGLStaticMesh>();
	}

	std::shared_ptr<Material> OpenGLRenderer::CreateMaterial()
	{
		return std::make_shared<OpenGLMaterial>();
	}

	std::shared_ptr<ShaderProgram> OpenGLRenderer::CreateShaderProgram()
	{
		std::shared_ptr<OpenGLShaderProgram> shaderProgram = std::make_shared<OpenGLShaderProgram>();
		m_ShaderPrograms.push_back(shaderProgram);
		return shaderProgram;
	}

	bool OpenGLRenderer::IsCompatible() const
	{
		if (!glfwInit())
			return false;

		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		GLFWwindow* window = glfwCreateWindow(100, 100, "Hey", nullptr, nullptr);

		glfwMakeContextCurrent(window);

		bool result = static_cast<bool>(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)));

		glfwDestroyWindow(window);

		return result && GLVersion.major >= 4 && GLVersion.minor >= 3;
	}

	void OpenGLRenderer::SetWindowHints()
	{
		window::Window& window = Application::GetInstance()->GetWindow();
		window.SetWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		window.SetWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		window.SetWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		window.SetWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window.SetWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
	}

	void OpenGLRenderer::Init()
	{
		window::Window& window = Application::GetInstance()->GetWindow();
		glfwMakeContextCurrent(window.GetNativeHandle());

		if (GLVersion.major == 0 && GLVersion.minor == 0 && !gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
			throw std::runtime_error("Could not load OpenGL!");

		m_DebugRenderer = std::make_shared<OpenGLDebugRenderer>();
		DebugRenderer::SetDebugRenderer(m_DebugRenderer);

		// TODO(MarcasRealAccount): Maybe move this somewhere else
		m_ReservedUniformBuffers = std::make_shared<OpenGLReservedUniformBuffers>();
	}

	void OpenGLRenderer::DeInit()
	{
		std::shared_ptr<OpenGLReservedUniformBuffers> reservedUniformBuffers = std::reinterpret_pointer_cast<OpenGLReservedUniformBuffers>(m_ReservedUniformBuffers);
		reservedUniformBuffers->CleanUp();

		DebugRenderer::SetDebugRenderer(nullptr);
	}

	void OpenGLRenderer::Render(std::shared_ptr<scene::Camera> camera)
	{
		if (!camera)
			return;

		//----
		// TODO(MarcasRealAccount): This should only be called for the main camera that's rendering to the window.
		const window::WindowData& windowData = Application::GetInstance()->GetWindow().GetWindowData();
		camera->m_Aspect                     = static_cast<float>(windowData.FramebufferWidth) / static_cast<float>(windowData.FramebufferHeight);
		glViewport(0, 0, windowData.FramebufferWidth, windowData.FramebufferHeight);
		glClearColor(camera->m_ClearColor.r, camera->m_ClearColor.g, camera->m_ClearColor.b, camera->m_ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		for (auto itr = m_ShaderPrograms.begin(); itr != m_ShaderPrograms.end();)
		{
			if (itr->expired())
			{
				itr = m_ShaderPrograms.erase(itr);
			}
			else
			{
				std::shared_ptr<OpenGLShaderProgram> shaderProgram = itr->lock();
				shaderProgram->ResetHasChanged();
				itr++;
			}
		}
		//----

		scene::Scene* scene = camera->GetScene();

		std::shared_ptr<OpenGLReservedUniformBuffers> reservedUniformBuffers = std::reinterpret_pointer_cast<OpenGLReservedUniformBuffers>(m_ReservedUniformBuffers);

		std::shared_ptr<UniformFMat4> projectionViewMatrixUniform = reservedUniformBuffers->GetUniform<UniformFMat4>("Camera", "projectionViewMatrix");
		if (projectionViewMatrixUniform && projectionViewMatrixUniform->GetType() == UniformFMat4::GetTypeS())
			projectionViewMatrixUniform->SetValue(camera->GetProjectionViewMatrix());

		reservedUniformBuffers->Bind();

		for (auto& weakEntity : scene->GetEntities())
		{
			if (!weakEntity.expired())
			{
				std::shared_ptr<scene::Entity> entity = weakEntity.lock();
				if (entity->IsRenderable())
					RenderEntity(std::reinterpret_pointer_cast<scene::RenderableEntity>(entity));
			}
		}

		std::shared_ptr<OpenGLDebugRenderer> debugRenderer = std::reinterpret_pointer_cast<OpenGLDebugRenderer>(m_DebugRenderer);
		debugRenderer->Render();

		glfwSwapBuffers(Application::GetInstance()->GetWindow().GetNativeHandle());
	}

	void OpenGLRenderer::RenderEntity(std::shared_ptr<scene::RenderableEntity> entity)
	{
		std::shared_ptr<OpenGLMaterial> material = std::reinterpret_pointer_cast<OpenGLMaterial>(entity->GetMaterial());
		OpenGLMesh*                     mesh     = reinterpret_cast<OpenGLMesh*>(entity->GetMesh()->GetNext());

		std::shared_ptr<UniformFMat4> transformationMatrixUniform = material->GetUniform<UniformFMat4>("Object", "transformationMatrix");
		if (transformationMatrixUniform && transformationMatrixUniform->GetType() == UniformFMat4::GetTypeS())
			transformationMatrixUniform->SetValue(entity->GetTransformationMatrix());

		material->Bind();
		mesh->Render();
		material->Unbind();
	}
} // namespace gp1::renderer::opengl

#endif