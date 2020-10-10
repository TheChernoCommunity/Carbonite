//
// Created by sfulham on 8/10/20.
//

#pragma once

#define BITSHIFT(x) (1 << x)

namespace gp1
{
    enum class EventType
    {
        None = 0,
        WINDOW_EVENT = BITSHIFT(1), WINDOW_CLOSE_EVENT = BITSHIFT(2), WINDOW_RESIZE_EVENT = BITSHIFT(3), WINDOW_MOVE_EVENT = BITSHIFT(4),
        KEY_EVENT = BITSHIFT(5), KEY_PRESSED_EVENT = BITSHIFT(6), KEY_RELEASED_EVENT = BITSHIFT(7),
        MOUSE_EVENT = BITSHIFT(8), MOUSE_MOVED_EVENT = BITSHIFT(9), MOUSE_BUTTON_PRESSED_EVENT = BITSHIFT(10), MOUSE_BUTTON_RELEASED_EVENT, MOUSE_SCROLLED_EVENT = BITSHIFT(11)
    };

    class Event
    {
    public:
        virtual EventType GetType() = 0;
    public:
        bool Handled = false;
    };
}
