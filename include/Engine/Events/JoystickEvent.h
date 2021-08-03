//
//	Created by MarcasRealAccount on 5. Nov. 2020
//

#pragma once

#include "Event.h"

#include <stdint.h>

namespace gp1::events::joystick
{
	class JoystickEvent : public Event
	{
	public:
		JoystickEvent(uint32_t joystickIndex);

		virtual EventType GetType() const = 0;
		// Get the joystick index this event came from.
		uint32_t GetJoystickIndex() const;

	private:
		uint32_t m_JoystickIndex; // The joystick index this event came from.
	};

	class JoystickAxisEvent : public JoystickEvent
	{
	public:
		JoystickAxisEvent(uint32_t joystickIndex, uint32_t axis, double value);

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

	class JoystickButtonPressedEvent : public JoystickEvent
	{
	public:
		JoystickButtonPressedEvent(uint32_t joystickIndex, uint32_t button);

		virtual EventType GetType() const override;
		// Get the type of event.
		static EventType GetTypeS();
		// Get the button that was pressed.
		uint32_t GetButton() const;

	private:
		uint32_t m_Button; // The button that was pressed.
	};

	class JoystickButtonReleasedEvent : public JoystickEvent
	{
	public:
		JoystickButtonReleasedEvent(uint32_t joystickIndex, uint32_t button);

		virtual EventType GetType() const override;
		// Get the type of event.
		static EventType GetTypeS();
		// Get the button that was released.
		uint32_t GetButton() const;

	private:
		uint32_t m_Button; // The button that was released.
	};

} // namespace gp1::events::joystick
