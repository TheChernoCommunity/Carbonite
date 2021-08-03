//
// Created by MarcasRealAccount on 21. Dec. 2020.
//

#include "Engine/Events/WindowEvent.h"

namespace gp1::events::window
{
	WindowResizeEvent::WindowResizeEvent(int width, int height)
	    : m_Width(width), m_Height(height) {}

	EventType WindowResizeEvent::GetType() const
	{
		return EventType::WINDOW_RESIZE_EVENT;
	}

	EventType WindowResizeEvent::GetTypeS()
	{
		return EventType::WINDOW_RESIZE_EVENT;
	}

	int WindowResizeEvent::GetWidth() const
	{
		return this->m_Width;
	}

	int WindowResizeEvent::GetHeight() const
	{
		return this->m_Height;
	}
} // namespace gp1::events::window
