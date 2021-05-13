#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLMaterial.h"
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
	OpenGLRenderer::OpenGLRenderer(window::Window* window)
	    : Renderer(window) {}

	StaticMesh* OpenGLRenderer::CreateStaticMesh()
	{
		return new OpenGLStaticMesh();
	}

	Material* OpenGLRenderer::CreateMaterial()
	{
		return new OpenGLMaterial();
	}

	ShaderProgram* OpenGLRenderer::CreateShader()
	{
		return new OpenGLShaderProgram();
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
		m_Window->SetWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		m_Window->SetWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		m_Window->SetWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		m_Window->SetWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_Window->SetWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
	}

	void OpenGLRenderer::Init()
	{
		glfwMakeContextCurrent(m_Window->GetNativeHandle());

		if (GLVersion.major == 0 && GLVersion.minor == 0 && !gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
			throw std::runtime_error("Could not load OpenGL!");
	}

	void OpenGLRenderer::DeInit()
	{
	}

	void OpenGLRenderer::Render(scene::Camera* camera)
	{
		[[maybe_unused]] scene::Scene* scene = camera->GetScene();
	}
} // namespace gp1::renderer::opengl

#endif