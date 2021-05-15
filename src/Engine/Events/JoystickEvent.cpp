//
// Created by MarcasRealAccount on 21. Dec. 2020.
//

#include "Engine/Events/JoystickEvent.h"

namespace gp1::events::joystick
{
	JoystickEvent::JoystickEvent(uint32_t joystickIndex)
	    : m_JoystickIndex(joystickIndex) {}

	uint32_t JoystickEvent::GetJoystickIndex() const
	{
		return m_JoystickIndex;
	}

	JoystickAxisEvent::JoystickAxisEvent(uint32_t joystickIndex, uint32_t axis, double value)
	    : JoystickEvent(joystickIndex), m_Axis(axis), m_Value(value) {}

	EventType JoystickAxisEvent::GetType() const
	{
		return EventType::JOYSTICK_AXIS_CHANGE_EVENT;
	}

	EventType JoystickAxisEvent::GetTypeS()
	{
		return EventType::JOYSTICK_AXIS_CHANGE_EVENT;
	}

	uint32_t JoystickAxisEvent::GetAxis() const
	{
		return m_Axis;
	}

	double JoystickAxisEvent::GetValue() const
	{
		return m_Value;
	}

	JoystickButtonPressedEvent::JoystickButtonPressedEvent(uint32_t joystickIndex, uint32_t button)
	    : JoystickEvent(joystickIndex), m_Button(button) {}

	EventType JoystickButtonPressedEvent::GetType() const
	{
		return EventType::JOYSTICK_BUTTON_PRESSED_EVENT;
	}

	EventType JoystickButtonPressedEvent::GetTypeS()
	{
		return EventType::JOYSTICK_BUTTON_PRESSED_EVENT;
	}

	uint32_t JoystickButtonPressedEvent::GetButton() const
	{
		return m_Button;
	}

	JoystickButtonReleasedEvent::JoystickButtonReleasedEvent(uint32_t joystickIndex, uint32_t button)
	    : JoystickEvent(joystickIndex), m_Button(button) {}

	EventType JoystickButtonReleasedEvent::GetType() const
	{
		return EventType::JOYSTICK_BUTTON_RELEASED_EVENT;
	}

	EventType JoystickButtonReleasedEvent::GetTypeS()
	{
		return EventType::JOYSTICK_BUTTON_RELEASED_EVENT;
	}

	uint32_t JoystickButtonReleasedEvent::GetButton() const
	{
		return m_Button;
	}
} // namespace gp1::events::joystick
