//
// Created by sfulham on 8/10/20.
// Edited by MarcasRealAccount on 4. Nov. 2020.
//

#pragma once

#include "Event.h"

namespace gp1::events::mouse
{
	class MouseEvent : public Event
	{
	public:
		virtual EventType GetType() = 0;
	};

	class MouseButtonPressedEvent : public MouseEvent
	{
	public:
		MouseButtonPressedEvent(int MouseButton)
		    : m_MouseButton(MouseButton) {};
		virtual EventType GetType() override
		{
			return EventType::MOUSE_BUTTON_PRESSED_EVENT;
		};
		// Get the type of event.
		static EventType GetTypeS()
		{
			return EventType::MOUSE_BUTTON_PRESSED_EVENT;
		};
		// Get the button that was pressed.
		int GetButton()
		{
			return m_MouseButton;
		};

	private:
		int m_MouseButton; // The button that was pressed.
	};

	class MouseButtonReleasedEvent : public MouseEvent
	{
	public:
		MouseButtonReleasedEvent(int MouseButton)
		    : m_MouseButton(MouseButton) {};
		virtual EventType GetType() override
		{
			return EventType::MOUSE_BUTTON_RELEASED_EVENT;
		};
		// Get the type of event.
		static EventType GetTypeS()
		{
			return EventType::MOUSE_BUTTON_RELEASED_EVENT;
		};
		// Get the button that was released.
		int GetButton()
		{
			return m_MouseButton;
		};

	private:
		int m_MouseButton; // The button that was released.
	};

	class MouseMovedEvent : public MouseEvent
	{
	public:
		MouseMovedEvent(double x, double y)
		    : m_X(x), m_Y(y) {};
		virtual EventType GetType() override
		{
			return EventType::MOUSE_MOVED_EVENT;
		};
		// Get the type of event.
		static EventType GetTypeS()
		{
			return EventType::MOUSE_MOVED_EVENT;
		};
		// Get the x axis value.
		double GetX()
		{
			return m_X;
		}
		// Get the y axis value.
		double GetY()
		{
			return m_Y;
		}

	private:
		double m_X; // The x axis value.
		double m_Y; // The y axis value.
	};

	class MouseScrollEvent : public MouseEvent
	{
	public:
		MouseScrollEvent(double x, double y)
		    : m_X(x), m_Y(y) {};
		virtual EventType GetType() override
		{
			return EventType::MOUSE_SCROLLED_EVENT;
		};
		// Get the type of event.
		static EventType GetTypeS()
		{
			return EventType::MOUSE_SCROLLED_EVENT;
		};
		// Get the x axis value.
		double GetX()
		{
			return m_X;
		}
		// Get the y axis value.
		double GetY()
		{
			return m_Y;
		}

	private:
		double m_X; // The x axis value.
		double m_Y; // The y axis value.
	};

} // namespace gp1::events::mouse
