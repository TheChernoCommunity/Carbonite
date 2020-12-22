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
		virtual EventType GetType() const = 0;
	};

	class WindowResizeEvent : public WindowEvent
	{
	public:
		WindowResizeEvent(int width, int height);

		virtual EventType GetType() const;
		// Get the type of event.
		static EventType GetTypeS();
		// Get the new width of the window.
		int GetWidth() const;
		// Get the new height of the window.
		int GetHeight() const;

	private:
		int m_Width;  // The new width of the window.
		int m_Height; // The new height of the window.
	};

} // namespace gp1::events::window
