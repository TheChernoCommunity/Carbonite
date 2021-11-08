#include <cstdlib>

#include "Graphics/Window.h"
#include "Log.h"

namespace
{
	static unsigned s_windowCount = 0;
} // namespace


namespace Graphics
{

	Window::Window(Instance& instance, const std::string& title, unsigned width, unsigned height)
	    : m_instance(instance), m_width(width), m_height(height), m_title(title)
	{
		if (s_windowCount == 0)
		{
			if (!glfwInit())
			{
				Log::error("GLFW failed to initialize!");
				std::abort();
			}

			if (!glfwVulkanSupported())
			{
				Log::error("Vulkan is not supported on this system!");
				std::abort();
			}
		}

		m_instance.addChild(this);

		s_windowCount++;
	}

	Instance& Window::getInstance()
	{
		return m_instance;
	}

	void Window::createImpl()
	{
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // TODO(MarcasRealAccount): Disable resizing, enable once the Vulkan Swapchain can be recreated.
		m_Handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	}

	bool Window::destroyImpl()
	{
		glfwDestroyWindow(m_Handle);
		return true;
	}

	Window::~Window()
	{
		s_windowCount--;

		m_instance.removeChild(this);

		if (s_windowCount == 0)
		{
			glfwTerminate();
		}
	}

} // namespace Graphics