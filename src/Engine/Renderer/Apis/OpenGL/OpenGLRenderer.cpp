//
//	Created by MarcasRealAccount on 13. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Application.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLMaterial.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLReservedUniformBuffers.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLStaticMesh.h"
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

	std::shared_ptr<ShaderProgram> OpenGLRenderer::CreateShader()
	{
		return std::make_shared<OpenGLShaderProgram>();
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

		// TODO(MarcasRealAccount): Maybe move this somewhere else
		m_ReservedUniformBuffers = new OpenGLReservedUniformBuffers();
	}

	void OpenGLRenderer::DeInit()
	{
		OpenGLReservedUniformBuffers* reservedUniformBuffers = reinterpret_cast<OpenGLReservedUniformBuffers*>(m_ReservedUniformBuffers);
		reservedUniformBuffers->CleanUp();
	}

	void OpenGLRenderer::Render(scene::Camera* camera)
	{
		[[maybe_unused]] scene::Scene* scene = camera->GetScene();

		OpenGLReservedUniformBuffers* reservedUniformBuffers = reinterpret_cast<OpenGLReservedUniformBuffers*>(m_ReservedUniformBuffers);
		reservedUniformBuffers->Bind();
	}
} // namespace gp1::renderer::opengl

#endif