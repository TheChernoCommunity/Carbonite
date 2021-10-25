#include "Graphics/Device/Surface.h"

#include <GLFW/glfw3.h>

namespace Graphics
{
	Surface::Surface(Instance& instance, GLFWwindow* window)
	    : Handle({ &instance }), m_Instance(&instance), m_Window(window)
	{
	}

	Surface::~Surface()
	{
		if (isCreated())
			destroy();
	}

	void Surface::setWindow(GLFWwindow* window)
	{
		m_Window = window;
	}

	void Surface::createImpl()
	{
		VkSurfaceKHR surface;

		auto result = glfwCreateWindowSurface(m_Instance->getHandle(), m_Window, nullptr, &surface);
		if (result == VK_SUCCESS)
			m_Handle = surface;
	}

	bool Surface::destroyImpl()
	{
		m_Instance->getHandle().destroySurfaceKHR(m_Handle);
		return true;
	}
} // namespace Graphics