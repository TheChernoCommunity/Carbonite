//
// Created by sfulham on 8/10/20.
//

#pragma once

#include "Event.h"

namespace gp1
{
	class WindowEvent : public Event
	{
	public:
		virtual EventType GetType() = 0;
	};

	class WindowResizeEvent : public WindowEvent
	{
	public:
		WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {};
		virtual EventType GetType() {return EventType::WINDOW_RESIZE_EVENT;}
		static EventType GetTypeS() {return EventType::WINDOW_RESIZE_EVENT;}
	private:
		int m_Width, m_Height;
	};
}
