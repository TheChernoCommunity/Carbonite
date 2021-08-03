//
//	Created by MarcasRealAccount on 5. Nov. 2020
//

#pragma once

#include "Event.h"

#include <stdint.h>

namespace gp1::events::gamepad
{
	class GamepadEvent : public Event
	{
	public:
		GamepadEvent(uint32_t joystickIndex);

		virtual EventType GetType() const = 0;
		// Get the joystick index this event came from.
		uint32_t GetJoystickIndex() const;

	private:
		uint32_t m_JoystickIndex; // The joystick index this event came from.
	};

	class GamepadAxisEvent : public GamepadEvent
	{
	public:
		GamepadAxisEvent(uint32_t joystickIndex, uint32_t axis, double value);

		virtual EventType GetType() const override;
		// Get the type of event.
		static EventType GetTypeS();
		// Get the axis that was changed.
		uint32_t GetAxis() const;
		// Get the new value of the axis.
		double GetValue() const;

	private:
		uint32_t m_Axis;  // The axis that was changed.
		double   m_Value; // The new value of the axis.
	};

	class GamepadButtonPressedEvent : public GamepadEvent
	{
	public:
		GamepadButtonPressedEvent(uint32_t joystickIndex, uint32_t button);

		virtual EventType GetType() const override;
		// Get the type of event.
		static EventType GetTypeS();
		// Get the button that was pressed.
		uint32_t GetButton() const;

	private:
		uint32_t m_Button; // The button that was pressed.
	};

	class GamepadButtonReleasedEvent : public GamepadEvent
	{
	public:
		GamepadButtonReleasedEvent(uint32_t joystickIndex, uint32_t button);

		virtual EventType GetType() const override;
		// Get the type of event.
		static EventType GetTypeS();
		// Get the button that was released.
		uint32_t GetButton() const;

	private:
		uint32_t m_Button; // The button that was released.
	};

} // namespace gp1::events::gamepad
