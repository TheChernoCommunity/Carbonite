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
		virtual EventType GetType() const = 0;
	};

	class KeyPressedEvent : public KeyboardEvent
	{
	public:
		KeyPressedEvent(int keycode, bool repeat);

		virtual EventType GetType() const override;
		// Get the type of event.
		static EventType GetTypeS();
		// Get the key that was pressed.
		int GetKey() const;
		// Is this a repeat event.
		bool IsRepeat() const;

	private:
		int  m_Keycode; // The key that was pressed.
		bool m_Repeat;  // Is this a repeat event.
	};

	class KeyReleasedEvent : public KeyboardEvent
	{
	public:
		KeyReleasedEvent(int keycode);

		virtual EventType GetType() const override;
		// Get the type of event.
		static EventType GetTypeS();
		// Get the key that was released.
		int GetKey() const;

	private:
		int m_Keycode; // The key that was released.
	};

} // namespace gp1::events::keyboard
