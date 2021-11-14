#pragma once

#include <GLFW/glfw3.h>

#include "Common.h"
#include "Instance.h"

namespace Graphics
{
	class Window : public Handle<GLFWwindow*, true, false>
	{
	public:
		Window(Instance& instance, const std::string& title, unsigned width = 1280, unsigned height = 720);
		Instance& getInstance();
		~Window();

	private:
		Instance&   m_instance;
		unsigned    m_width, m_height;
		std::string m_title;

		virtual void createImpl() override;
		virtual bool destroyImpl() override;
	};

} // namespace Graphics
