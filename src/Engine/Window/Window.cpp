//
//	Created by rtryan98 on 21. Oct. 2020
//	Edited by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Window/Window.h"
#include "Engine/Utility/Logger.h"

#include "Engine/Events/EventHandler.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/WindowEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gp1
{
	Window::Window(const WindowData& p_WindowData)
		: m_WindowData{ p_WindowData }, m_Logger{ "Window" }
	{

	}

	void Window::Init()
	{
		if (!glfwInit())
		{
			m_Logger.Log(Severity::Error, "Failed to initialize GLFW!");
		}

		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);

		GLFWmonitor* monitor{ glfwGetPrimaryMonitor() };
		const GLFWvidmode* mode{ glfwGetVideoMode(monitor) };

		switch (m_WindowData.Mode)
		{
		case WindowMode::FULLSCREEN:
			m_NativeHandle = glfwCreateWindow(mode->width, mode->height, m_WindowData.Title.c_str(), monitor, nullptr);
			break;
		case WindowMode::BORDERLESS:
			// while following the official guide, this is not the completely desired effect of a borderless window
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
			m_NativeHandle = glfwCreateWindow(mode->width, mode->height, m_WindowData.Title.c_str(), monitor, nullptr);
			break;
		default:
			m_NativeHandle = glfwCreateWindow(m_WindowData.Width, m_WindowData.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
			break;
		}

		glfwSetWindowUserPointer(m_NativeHandle, &m_WindowData);

		glfwSetWindowSizeCallback(m_NativeHandle, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data.Width = width;
				data.Height = height;
				WindowResizeEvent event{ width, height };
				EventHandler::PushEvent(event);
			});

		glfwSetFramebufferSizeCallback(m_NativeHandle, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data.FramebufferWidth = width;
				data.FramebufferHeight = height;
			});

		glfwSetKeyCallback(m_NativeHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event{ key, false };
					EventHandler::PushEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event{ key };
					EventHandler::PushEvent(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event{ key, true };
					EventHandler::PushEvent(event);
					break;
				}
				default:
				{
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_NativeHandle, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event{ button };
					EventHandler::PushEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event{ button };
					EventHandler::PushEvent(event);
					break;
				}
				default:
				{
					break;
				}
				}
			});

		glfwSetCursorPosCallback(m_NativeHandle, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				MouseMovedEvent event{ static_cast<int>(xPos), static_cast<int>(yPos) };
				EventHandler::PushEvent(event);
			});

		glfwSetScrollCallback(m_NativeHandle, [](GLFWwindow* window, double x, double y)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				MouseScrollEvent event{ x, y };
				EventHandler::PushEvent(event);
			});

		glfwMakeContextCurrent(m_NativeHandle);
		if (!gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress) )
		{
			m_Logger.Log(Severity::Error, "Failed to initialize GLAD!");
		}

		m_Logger.Log(Severity::Trace, "Window was created successfully.");
	}

	void Window::DeInit()
	{
		glfwDestroyWindow(m_NativeHandle);
		glfwTerminate();
		m_Logger.Log(Severity::Trace, "Window terminated.");
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
	}

	void Window::SetVSync(const bool p_VSync)
	{
		m_WindowData.VSync = p_VSync;
		if (p_VSync)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
	}

	void Window::SetWidth(const int p_Width)
	{
		m_WindowData.Width = p_Width;
		glfwSetWindowSize(m_NativeHandle, m_WindowData.Width, m_WindowData.Height);
	}

	void Window::SetHeight(const int p_Height)
	{
		m_WindowData.Height = p_Height;
		glfwSetWindowSize(m_NativeHandle, m_WindowData.Width, m_WindowData.Height);
	}

	void Window::SetSize(const int p_Width, const int p_Height)
	{
		m_WindowData.Width = p_Width;
		m_WindowData.Height = p_Height;
		glfwSetWindowSize(m_NativeHandle, m_WindowData.Width, m_WindowData.Height);
	}

	void Window::SetTitle(const std::string& p_Title)
	{
		m_WindowData.Title = p_Title;
		glfwSetWindowTitle(m_NativeHandle, m_WindowData.Title.c_str());
	}

	const WindowData& Window::GetWindowData() const
	{
		return m_WindowData;
	}

	const bool Window::IsCloseRequested() const
	{
		return glfwWindowShouldClose(m_NativeHandle);
	}

} // namespace gp1
