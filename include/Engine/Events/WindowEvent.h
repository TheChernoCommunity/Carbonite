//
// Created by sfulham on 8/10/20.
//

#pragma once

#include "Event.h"

namespace gp1::events::window
{
	class WindowEvent : public Event
	{
	public:
		virtual EventType GetType() = 0;
	};

	class WindowResizeEvent : public WindowEvent
	{
	public:
		WindowResizeEvent(int width, int height)
		    : m_Width(width), m_Height(height) {};
		virtual EventType GetType()
		{
			return EventType::WINDOW_RESIZE_EVENT;
		}
		// Get the type of event.
		static EventType GetTypeS()
		{
			return EventType::WINDOW_RESIZE_EVENT;
		}
		// Get the new width of the window.
		int GetWidth() const
		{
			return this->m_Width;
		}
		// Get the new height of the window.
		int GetHeight() const
		{
			return this->m_Height;
		}

	private:
		int m_Width;  // The new width of the window.
		int m_Height; // The new height of the window.
	};

} // namespace gp1::events::window
