#pragma once

#include <sstream>

#include "Event.h"
#include "KeyCodes.h"

class KeyEvent : public Event
{
public:
	KeyCode GetKeyCode() const
	{
		return m_KeyCode;
	}

	EVENT_CLASS_CATEGORY(static_cast<int>(Event::Category::Keyboard) | static_cast<int>(Event::Category::Input))
protected:
	KeyEvent(const KeyCode keycode)
	    : m_KeyCode(keycode) {}

	KeyCode m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount)
	    : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

	uint16_t GetRepeatCount() const
	{
		return m_RepeatCount;
	}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << static_cast<int>(m_KeyCode) << " (" << static_cast<int>(m_RepeatCount) << " repeats)";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPressed)
private:
	uint16_t m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(const KeyCode keycode)
	    : KeyEvent(keycode) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << static_cast<int>(m_KeyCode);
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(const KeyCode keycode)
	    : KeyEvent(keycode) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << static_cast<int>(m_KeyCode);
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyTyped)
};