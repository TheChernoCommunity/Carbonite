#pragma once

#include "Graphics/Common.h"

namespace Graphics
{
	struct Instance;
	struct Window;

	struct Surface : public Handle<vk::SurfaceKHR, true, false>
	{
	public:
		Surface(Instance& window);
		~Surface();

		auto& getInstance()
		{
			return m_Instance;
		}
		auto& getInstance() const
		{
			return m_Instance;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		Window* m_Window;

	private:
		Instance& m_Instance;

		Window* m_UsedWindow;
	};
} // namespace Graphics
