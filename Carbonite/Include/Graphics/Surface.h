#pragma once

#include "Instance.h"

struct GLFWwindow;

namespace Graphics
{
	struct Surface : public Handle<vk::SurfaceKHR>
	{
	public:
		Surface(Instance& instance, GLFWwindow* window);
		~Surface();

		auto getInstance() const
		{
			return m_Instance;
		}

		void setWindow(GLFWwindow* window);
		auto getWindow() const
		{
			return m_Window;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	private:
		Instance*   m_Instance;
		GLFWwindow* m_Window;
	};
} // namespace Graphics