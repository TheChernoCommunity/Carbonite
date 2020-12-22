//
// Created by MarcasRealAccount on 21. Dec. 2020.
//

#include "Engine/Events/GamepadEvent.h"

namespace gp1::events::gamepad
{
	GamepadEvent::GamepadEvent(uint32_t joystickIndex)
	    : m_JoystickIndex(joystickIndex) {}

	uint32_t GamepadEvent::GetJoystickIndex() const
	{
		return m_JoystickIndex;
	}

	GamepadAxisEvent::GamepadAxisEvent(uint32_t joystickIndex, uint32_t axis, double value)
	    : GamepadEvent(joystickIndex), m_Axis(axis), m_Value(value) {}

	EventType GamepadAxisEvent::GetType() const
	{
		return EventType::GAMEPAD_AXIS_CHANGE_EVENT;
	}

	EventType GamepadAxisEvent::GetTypeS()
	{
		return EventType::GAMEPAD_AXIS_CHANGE_EVENT;
	}

	uint32_t GamepadAxisEvent::GetAxis() const
	{
		return m_Axis;
	}

	double GamepadAxisEvent::GetValue() const
	{
		return m_Value;
	}

	GamepadButtonPressedEvent::GamepadButtonPressedEvent(uint32_t joystickIndex, uint32_t button)
	    : GamepadEvent(joystickIndex), m_Button(button) {}

	EventType GamepadButtonPressedEvent::GetType() const
	{
		return EventType::GAMEPAD_BUTTON_PRESSED_EVENT;
	}

	EventType GamepadButtonPressedEvent::GetTypeS()
	{
		return EventType::GAMEPAD_BUTTON_PRESSED_EVENT;
	}

	uint32_t GamepadButtonPressedEvent::GetButton() const
	{
		return m_Button;
	}

	GamepadButtonReleasedEvent::GamepadButtonReleasedEvent(uint32_t joystickIndex, uint32_t button)
	    : GamepadEvent(joystickIndex), m_Button(button) {}

	EventType GamepadButtonReleasedEvent::GetType() const
	{
		return EventType::GAMEPAD_BUTTON_RELEASED_EVENT;
	}

	EventType GamepadButtonReleasedEvent::GetTypeS()
	{
		return EventType::GAMEPAD_BUTTON_RELEASED_EVENT;
	}

	uint32_t GamepadButtonReleasedEvent::GetButton() const
	{
		return m_Button;
	}
} // namespace gp1::events::gamepad