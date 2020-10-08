//
// Created by sfulham on 8/10/20.
//

#pragma once

#include "Event.h"

namespace gp1
{
	class KeyboardEvent : public Event
	{
	public:
		virtual EventType GetType() = 0;
	};

	class KeyPressedEvent : public KeyboardEvent
	{
	public:
		KeyPressedEvent(int keycode, bool repeat) : m_Keycode(keycode), m_Repeat(repeat) {};
		virtual EventType GetType() override { return EventType::KEY_PRESSED_EVENT; };
		static EventType GetTypeS() { return EventType::KEY_PRESSED_EVENT; };
		int GetKey() { return m_Keycode; };
	private:
		int m_Keycode;
		bool m_Repeat;
	};

	class KeyReleasedEvent : public KeyboardEvent
	{
	public:
		KeyReleasedEvent(int keycode) : m_Keycode(keycode) {};
		virtual EventType GetType() override { return EventType::KEY_RELEASED_EVENT; };
		static EventType GetTypeS() { return EventType::KEY_RELEASED_EVENT; };
		int GetKey() { return m_Keycode; };
	private:
		int m_Keycode;
	};
}
