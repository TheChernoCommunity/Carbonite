//
// Created by sfulham on 8/10/20.
//

#pragma once

#include "Event.h"

namespace gp1
{
	class MouseEvent : public Event
	{
	public:
		virtual EventType GetType() = 0;
	};

	class MouseButtonPressedEvent : public MouseEvent
	{
	public:
		MouseButtonPressedEvent(int MouseButton) : m_MouseButton(MouseButton) {};
		virtual EventType GetType() override { return EventType::MOUSE_BUTTON_PRESSED_EVENT; };
		static EventType GetTypeS() { return EventType::MOUSE_BUTTON_PRESSED_EVENT; };
		int GetButton() { return m_MouseButton; };
	private:
		int m_MouseButton;
	};

	class MouseButtonReleasedEvent : public MouseEvent
	{
	public:
		MouseButtonReleasedEvent(int MouseButton) : m_MouseButton(MouseButton) {};
		virtual EventType GetType() override { return EventType::MOUSE_BUTTON_RELEASED_EVENT; };
		static EventType GetTypeS() { return EventType::MOUSE_BUTTON_RELEASED_EVENT; };
		int GetButton() { return m_MouseButton; };
	private:
		int m_MouseButton;
	};

	class MouseMovedEvent : public MouseEvent
	{
	public:
		MouseMovedEvent(int x, int y) : m_X(x), m_Y(y) {};
		virtual EventType GetType() override { return EventType::MOUSE_MOVED_EVENT; };
		static EventType GetTypeS() { return EventType::MOUSE_MOVED_EVENT; };
		static uint32_t GetXAxisIndex() { return 0; }	// Placeholder function to get the X Axis index -- MarcasRealAccount
		static uint32_t GetYAxisIndex() { return 1; }	// Placeholder function to get the Y Axis index -- MarcasRealAccount
		int GetX() {return m_X;}
		int GetY() {return m_Y;}
	private:
		int m_X, m_Y;
	};
}
