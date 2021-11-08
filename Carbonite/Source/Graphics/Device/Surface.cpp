#include "PCH.h"

#include "Graphics/Device/Surface.h"
#include "Graphics/Instance.h"

namespace Graphics
{
	Surface::Surface(Window& window)
	    : m_window(window)
	{
		m_window.addChild(this);
	}

	Surface::~Surface()
	{
		if (isValid())
			destroy();
		m_window.removeChild(this);
	}

	void Surface::createImpl()
	{
		VkSurfaceKHR surface;

		auto result = glfwCreateWindowSurface(m_window.getInstance().getHandle(), m_window.getHandle(), nullptr, &surface);
		if (result == VK_SUCCESS)
			m_Handle = surface;
	}

	bool Surface::destroyImpl()
	{
		m_window.getInstance().getHandle().destroySurfaceKHR(m_Handle);
		return true;
	}
} // namespace Graphics
