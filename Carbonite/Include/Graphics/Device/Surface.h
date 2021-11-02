#pragma once

#include "Graphics/Common.h"

struct GLFWwindow;

namespace Graphics
{
	struct Instance;

	struct Surface : public Handle<vk::SurfaceKHR, true, false>
	{
	public:
		Surface(Instance& instance, GLFWwindow* window);
		~Surface();

		auto& getInstance()
		{
			return m_Instance;
		}
		auto& getInstance() const
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
		Instance&   m_Instance;
		GLFWwindow* m_Window;
	};
} // namespace Graphics
