#include "Window.h"
#include "Utils/Log.h"

#include <cstdlib>

#include <stdexcept>

namespace
{
	static unsigned s_windowCount = 0;
} // namespace

namespace Graphics
{
	Window::Window(const std::string& title, unsigned width, unsigned height)
	    : m_width(width), m_height(height), m_title(title)
	{
		if (s_windowCount == 0)
		{
			if (!glfwInit())
				throw std::runtime_error("GLFW failed to initialize");

			if (!glfwVulkanSupported())
				throw std::runtime_error("Vulkan is not supported on this system!");
		}

		s_windowCount++;
	}

	Window::~Window()
	{
		s_windowCount--;

		if (s_windowCount == 0)
			glfwTerminate();
	}

	void Window::createImpl()
	{
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
		m_Handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	}

	bool Window::destroyImpl()
	{
		glfwDestroyWindow(m_Handle);
		return true;
	}
} // namespace Graphics