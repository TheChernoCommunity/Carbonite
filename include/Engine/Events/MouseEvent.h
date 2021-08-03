//
// Created by sfulham on 8/10/20.
// Edited by MarcasRealAccount on 4. Nov. 2020.
//

#pragma once

#include "Event.h"

namespace gp1::events::mouse
{
	class MouseEvent : public Event
	{
	public:
		virtual EventType GetType() const = 0;
	};

	class MouseButtonPressedEvent : public MouseEvent
	{
	public:
		MouseButtonPressedEvent(int MouseButton);

		virtual EventType GetType() const override;
		// Get the type of event.
		static EventType GetTypeS();
		// Get the button that was pressed.
		int GetButton() const;

	private:
		int m_MouseButton; // The button that was pressed.
	};

	class MouseButtonReleasedEvent : public MouseEvent
	{
	public:
		MouseButtonReleasedEvent(int MouseButton);

		virtual EventType GetType() const override;
		// Get the type of event.
		static EventType GetTypeS();
		// Get the button that was released.
		int GetButton() const;

	private:
		int m_MouseButton; // The button that was released.
	};

	class MouseMovedEvent : public MouseEvent
	{
	public:
		MouseMovedEvent(double x, double y);

		virtual EventType GetType() const override;
		// Get the type of event.
		static EventType GetTypeS();
		// Get the x axis value.
		double GetX() const;
		// Get the y axis value.
		double GetY() const;

	private:
		double m_X; // The x axis value.
		double m_Y; // The y axis value.
	};

	class MouseScrollEvent : public MouseEvent
	{
	public:
		MouseScrollEvent(double x, double y);

		virtual EventType GetType() const override;
		static EventType  GetTypeS();   // Get the type of event.
		double            GetX() const; // Get the x axis value.
		double            GetY() const; // Get the y axis value.

	private:
		double m_X; // The x axis value.
		double m_Y; // The y axis value.
	};

} // namespace gp1::events::mouse
