//
// Created by MarcasRealAccount on 21. Dec. 2020.
//

#include "Engine/Events/KeyboardEvent.h"

namespace gp1::events::keyboard
{
	KeyPressedEvent::KeyPressedEvent(int keycode, bool repeat)
	    : m_Keycode(keycode), m_Repeat(repeat) {}

	EventType KeyPressedEvent::GetType() const
	{
		return EventType::KEY_PRESSED_EVENT;
	}

	EventType KeyPressedEvent::GetTypeS()
	{
		return EventType::KEY_PRESSED_EVENT;
	}

	int KeyPressedEvent::GetKey() const
	{
		return m_Keycode;
	}

	bool KeyPressedEvent::IsRepeat() const
	{
		return m_Repeat;
	}

	KeyReleasedEvent::KeyReleasedEvent(int keycode)
	    : m_Keycode(keycode) {}

	EventType KeyReleasedEvent::GetType() const
	{
		return EventType::KEY_RELEASED_EVENT;
	}

	EventType KeyReleasedEvent::GetTypeS()
	{
		return EventType::KEY_RELEASED_EVENT;
	}

	int KeyReleasedEvent::GetKey() const
	{
		return m_Keycode;
	}
} // namespace gp1::events::keyboard
