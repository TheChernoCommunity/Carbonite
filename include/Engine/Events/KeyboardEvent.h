//
// Created by sfulham on 8/10/20.
//

#pragma once

#include "Event.h"

namespace gp1::events::keyboard
{
	class KeyboardEvent : public Event
	{
	public:
		virtual EventType GetType() = 0;
	};

	class KeyPressedEvent : public KeyboardEvent
	{
	public:
		KeyPressedEvent(int keycode, bool repeat)
		    : m_Keycode(keycode), m_Repeat(repeat) {};
		virtual EventType GetType() override
		{
			return EventType::KEY_PRESSED_EVENT;
		};
		// Get the type of event.
		static EventType GetTypeS()
		{
			return EventType::KEY_PRESSED_EVENT;
		};
		// Get the key that was pressed.
		int GetKey()
		{
			return m_Keycode;
		};
		// Is this a repeat event.
		bool IsRepeat()
		{
			return m_Repeat;
		};

	private:
		int  m_Keycode; // The key that was pressed.
		bool m_Repeat;  // Is this a repeat event.
	};

	class KeyReleasedEvent : public KeyboardEvent
	{
	public:
		KeyReleasedEvent(int keycode)
		    : m_Keycode(keycode) {};
		virtual EventType GetType() override
		{
			return EventType::KEY_RELEASED_EVENT;
		};
		// Get the type of event.
		static EventType GetTypeS()
		{
			return EventType::KEY_RELEASED_EVENT;
		};
		// Get the key that was released.
		int GetKey()
		{
			return m_Keycode;
		};

	private:
		int m_Keycode; // The key that was released.
	};

} // namespace gp1::events::keyboard
