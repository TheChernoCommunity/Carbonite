#pragma once

#include "Graphics/Common.h"
#include "Graphics/Window.h"

struct GLFWwindow;

namespace Graphics
{
	struct Instance;

	struct Surface : public Handle<vk::SurfaceKHR, true, false>
	{
	public:
		Surface(Window& window);
		~Surface();

		auto& getInstance()
		{
			return m_window.getInstance();
		}
		auto& getInstance() const
		{
			return m_window.getInstance();
		}

		auto getWindow() const
		{
			return m_window;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	private:
		Window& m_window;
	};
} // namespace Graphics
