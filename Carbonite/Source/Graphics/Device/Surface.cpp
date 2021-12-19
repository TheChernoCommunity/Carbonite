#include "PCH.h"

#include "Graphics/Device/Surface.h"
#include "Graphics/Instance.h"
#include "Graphics/Window.h"

namespace Graphics
{
	Surface::Surface(Instance& instance)
	    : m_Instance(instance)
	{
		m_Instance.addChild(this);
	}

	Surface::~Surface()
	{
		if (isValid())
			destroy();
		m_Instance.removeChild(this);
	}

	void Surface::createImpl()
	{
		m_UsedWindow = m_Window;
		VkSurfaceKHR surface;

		m_UsedWindow->addChild(this);
		auto result = glfwCreateWindowSurface(m_Instance.getHandle(), m_UsedWindow->getHandle(), nullptr, &surface);
		if (result == VK_SUCCESS)
			m_Handle = surface;
	}

	bool Surface::destroyImpl()
	{
		m_Instance->destroySurfaceKHR(m_Handle);
		m_UsedWindow->removeChild(this);
		return true;
	}
} // namespace Graphics
