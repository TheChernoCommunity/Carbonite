//	
//	Created by MarcasRealAccount on 5. Nov. 2020
//	

#pragma once

#include "Event.h"

#include <stdint.h>

namespace gp1 {

	class GamepadEvent : public Event {
	public:
		GamepadEvent(uint32_t joystickIndex) : m_JoystickIndex(joystickIndex) {};
		virtual EventType GetType() = 0;
		uint32_t GetJoystickIndex() { return m_JoystickIndex; };

	private:
		uint32_t m_JoystickIndex;
	};

	class GamepadAxisEvent : public GamepadEvent {
	public:
		GamepadAxisEvent(uint32_t joystickIndex, uint32_t axis, double value) : GamepadEvent(joystickIndex), m_Axis(axis), m_Value(value) {};
		virtual EventType GetType() override { return EventType::GAMEPAD_AXIS_CHANGE_EVENT; };
		static EventType GetTypeS() { return EventType::GAMEPAD_AXIS_CHANGE_EVENT; };
		uint32_t GetAxis() { return m_Axis; };
		double GetValue() { return m_Value; };

	private:
		uint32_t m_Axis;
		double m_Value;
	};

	class GamepadButtonPressedEvent : public GamepadEvent {
	public:
		GamepadButtonPressedEvent(uint32_t joystickIndex, uint32_t button) : GamepadEvent(joystickIndex), m_Button(button) {};
		virtual EventType GetType() override { return EventType::GAMEPAD_BUTTON_PRESSED_EVENT; };
		static EventType GetTypeS() { return EventType::GAMEPAD_BUTTON_PRESSED_EVENT; };
		uint32_t GetButton() { return m_Button; };

	private:
		uint32_t m_Button;
	};

	class GamepadButtonReleasedEvent : public GamepadEvent {
	public:
		GamepadButtonReleasedEvent(uint32_t joystickIndex, uint32_t button) : GamepadEvent(joystickIndex), m_Button(button) {};
		virtual EventType GetType() override { return EventType::GAMEPAD_BUTTON_RELEASED_EVENT; };
		static EventType GetTypeS() { return EventType::GAMEPAD_BUTTON_RELEASED_EVENT; };
		uint32_t GetButton() { return m_Button; };

	private:
		uint32_t m_Button;
	};

} // namespace gp1
