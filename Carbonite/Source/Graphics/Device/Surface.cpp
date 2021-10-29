#include "Graphics/Device/Surface.h"

#include <GLFW/glfw3.h>

namespace Graphics
{
	Surface::Surface(Instance& instance, GLFWwindow* window)
	    : m_Instance(instance), m_Window(window)
	{
		m_Instance.addChild(this);
	}

	Surface::~Surface()
	{
		if (isValid())
			destroy();
		m_Instance.removeChild(this);
	}

	void Surface::setWindow(GLFWwindow* window)
	{
		m_Window = window;
	}

	void Surface::createImpl()
	{
		VkSurfaceKHR surface;

		auto result = glfwCreateWindowSurface(*m_Instance, m_Window, nullptr, &surface);
		if (result == VK_SUCCESS)
			m_Handle = surface;
	}

	bool Surface::destroyImpl()
	{
		m_Instance->destroySurfaceKHR(m_Handle);
		return true;
	}
} // namespace Graphics
