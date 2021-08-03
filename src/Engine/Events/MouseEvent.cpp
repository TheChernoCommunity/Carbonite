//
// Created by MarcasRealAccount on 21. Dec. 2020.
//

#include "Engine/Events/MouseEvent.h"

namespace gp1::events::mouse
{
	MouseButtonPressedEvent::MouseButtonPressedEvent(int MouseButton)
	    : m_MouseButton(MouseButton) {}

	EventType MouseButtonPressedEvent::GetType() const
	{
		return EventType::MOUSE_BUTTON_PRESSED_EVENT;
	}

	EventType MouseButtonPressedEvent::GetTypeS()
	{
		return EventType::MOUSE_BUTTON_PRESSED_EVENT;
	}

	int MouseButtonPressedEvent::GetButton() const
	{
		return m_MouseButton;
	}

	MouseButtonReleasedEvent::MouseButtonReleasedEvent(int MouseButton)
	    : m_MouseButton(MouseButton) {}

	EventType MouseButtonReleasedEvent::GetType() const
	{
		return EventType::MOUSE_BUTTON_RELEASED_EVENT;
	}

	EventType MouseButtonReleasedEvent::GetTypeS()
	{
		return EventType::MOUSE_BUTTON_RELEASED_EVENT;
	}

	int MouseButtonReleasedEvent::GetButton() const
	{
		return m_MouseButton;
	}

	MouseMovedEvent::MouseMovedEvent(double x, double y)
	    : m_X(x), m_Y(y) {}

	EventType MouseMovedEvent::GetType() const
	{
		return EventType::MOUSE_MOVED_EVENT;
	}

	EventType MouseMovedEvent::GetTypeS()
	{
		return EventType::MOUSE_MOVED_EVENT;
	}

	double MouseMovedEvent::GetX() const
	{
		return m_X;
	}

	double MouseMovedEvent::GetY() const
	{
		return m_Y;
	}

	MouseScrollEvent::MouseScrollEvent(double x, double y)
	    : m_X(x), m_Y(y) {}

	EventType MouseScrollEvent::GetType() const
	{
		return EventType::MOUSE_SCROLLED_EVENT;
	}

	EventType MouseScrollEvent::GetTypeS()
	{
		return EventType::MOUSE_SCROLLED_EVENT;
	}

	double MouseScrollEvent::GetX() const
	{
		return m_X;
	}

	double MouseScrollEvent::GetY() const
	{
		return m_Y;
	}

} // namespace gp1::events::mouse
