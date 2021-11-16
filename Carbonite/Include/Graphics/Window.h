#pragma once

#include <GLFW/glfw3.h>

#include "Common.h"

namespace Graphics
{
	struct Window : public Handle<GLFWwindow*, true, false>
	{
	public:
		Window(const std::string& title, unsigned width = 1280, unsigned height = 720);
		~Window();

	private:
		unsigned    m_width, m_height;
		std::string m_title;

		virtual void createImpl() override;
		virtual bool destroyImpl() override;
	};
} // namespace Graphics
