//
// Created by sfulham on 8/10/20.
// Edited by MarcasRalAccount on 5. Nov. 2020.
//

#pragma once

#define BITSHIFT(x) (1 << x)

namespace gp1::events
{
	enum class EventType
	{
		None                           = 0,
		WINDOW_EVENT                   = BITSHIFT(1),
		WINDOW_CLOSE_EVENT             = BITSHIFT(2),
		WINDOW_RESIZE_EVENT            = BITSHIFT(3),
		WINDOW_MOVE_EVENT              = BITSHIFT(4),
		KEY_EVENT                      = BITSHIFT(5),
		KEY_PRESSED_EVENT              = BITSHIFT(6),
		KEY_RELEASED_EVENT             = BITSHIFT(7),
		MOUSE_EVENT                    = BITSHIFT(8),
		MOUSE_MOVED_EVENT              = BITSHIFT(9),
		MOUSE_BUTTON_PRESSED_EVENT     = BITSHIFT(10),
		MOUSE_BUTTON_RELEASED_EVENT    = BITSHIFT(11),
		MOUSE_SCROLLED_EVENT           = BITSHIFT(12),
		JOYSTICK_AXIS_CHANGE_EVENT     = BITSHIFT(13),
		JOYSTICK_BUTTON_PRESSED_EVENT  = BITSHIFT(14),
		JOYSTICK_BUTTON_RELEASED_EVENT = BITSHIFT(15),
		GAMEPAD_AXIS_CHANGE_EVENT      = BITSHIFT(16),
		GAMEPAD_BUTTON_PRESSED_EVENT   = BITSHIFT(17),
		GAMEPAD_BUTTON_RELEASED_EVENT  = BITSHIFT(18)
	};

	class Event
	{
	public:
		// Get the type of event.
		virtual EventType GetType() const = 0;

	public:
		bool Handled = false; // Has this event been handled or not
	};

} // namespace gp1::events

#undef BITSHIFT
