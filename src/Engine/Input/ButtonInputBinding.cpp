//
//	Created by MarcasRealAccount on 8. Oct. 2020
//

#include "Engine/Input/ButtonInputBinding.h"
#include "Engine/Events/GamepadEvent.h"
#include "Engine/Events/JoystickEvent.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace gp1::input
{
	ButtonInputBinding::ButtonInputBinding(InputGroup* inputGroup, const std::string& id, uint32_t button, ButtonInputType inputType, InputLocation location, ButtonCallback callback)
	    : IInputBinding(inputGroup, id, InputType::BUTTON, button, location), m_inputType(inputType), m_callback(callback) {}

	void ButtonInputBinding::HandleEvent(events::Event& event)
	{
		if (this->m_callback == nullptr)
			return;

		events::EventType eventType = event.GetType();
		switch (eventType)
		{
		case events::EventType::KEY_PRESSED_EVENT:
		{
			if (this->GetLocation() != InputLocation::KEYBOARD)
				return;

			events::keyboard::KeyPressedEvent& pressedEvent = *(reinterpret_cast<events::keyboard::KeyPressedEvent*>(&event));
			if ((uint32_t) pressedEvent.GetKey() != this->GetIndex())
				return;

			if (pressedEvent.IsRepeat())
			{
				if (this->m_inputType != ButtonInputType::REPEAT)
					return;
			}
			else
			{
				if (this->m_inputType != ButtonInputType::PRESS && this->m_inputType != ButtonInputType::PRESS_AND_RELEASE)
					return;
			}

			this->m_callback({ this->GetLocation(), pressedEvent.IsRepeat() ? ButtonInputType::REPEAT : ButtonInputType::PRESS, this->GetIndex(), GetId() });
			event.Handled = true;
			break;
		}
		case events::EventType::KEY_RELEASED_EVENT:
		{
			if (this->GetLocation() != InputLocation::KEYBOARD)
				return;

			if (this->m_inputType != ButtonInputType::RELEASE && this->m_inputType != ButtonInputType::PRESS_AND_RELEASE)
				return;

			events::keyboard::KeyReleasedEvent& releasedEvent = *(reinterpret_cast<events::keyboard::KeyReleasedEvent*>(&event));
			if ((uint32_t) releasedEvent.GetKey() != this->GetIndex())
				return;

			this->m_callback({ this->GetLocation(), ButtonInputType::RELEASE, this->GetIndex(), GetId() });
			event.Handled = true;
			break;
		}
		case events::EventType::MOUSE_BUTTON_PRESSED_EVENT:
		{
			if (this->GetLocation() != InputLocation::MOUSE)
				return;

			if (this->m_inputType != ButtonInputType::PRESS && this->m_inputType != ButtonInputType::PRESS_AND_RELEASE)
				return;

			events::mouse::MouseButtonPressedEvent& pressedEvent = *(reinterpret_cast<events::mouse::MouseButtonPressedEvent*>(&event));
			if ((uint32_t) pressedEvent.GetButton() != this->GetIndex())
				return;

			this->m_callback({ this->GetLocation(), ButtonInputType::PRESS, this->GetIndex(), GetId() });
			event.Handled = true;
			break;
		}
		case events::EventType::MOUSE_BUTTON_RELEASED_EVENT:
		{
			if (this->GetLocation() != InputLocation::MOUSE)
				return;

			if (this->m_inputType != ButtonInputType::RELEASE && this->m_inputType != ButtonInputType::PRESS_AND_RELEASE)
				return;

			events::mouse::MouseButtonReleasedEvent& releasedEvent = *(reinterpret_cast<events::mouse::MouseButtonReleasedEvent*>(&event));
			if ((uint32_t) releasedEvent.GetButton() != this->GetIndex())
				return;

			this->m_callback({ this->GetLocation(), ButtonInputType::RELEASE, this->GetIndex(), GetId() });
			event.Handled = true;
			break;
		}
		case events::EventType::GAMEPAD_BUTTON_PRESSED_EVENT:
		{
			if (this->GetLocation() != InputLocation::GAMEPAD)
				return;

			if (this->m_inputType != ButtonInputType::PRESS && this->m_inputType != ButtonInputType::PRESS_AND_RELEASE)
				return;

			events::gamepad::GamepadButtonPressedEvent& pressedEvent = *static_cast<events::gamepad::GamepadButtonPressedEvent*>(&event);
			if (pressedEvent.GetButton() != this->GetIndex())
				return;

			this->m_callback({ this->GetLocation(), ButtonInputType::PRESS, this->GetIndex(), GetId() });
			pressedEvent.Handled = true;
			break;
		}
		case events::EventType::GAMEPAD_BUTTON_RELEASED_EVENT:
		{
			if (this->GetLocation() != InputLocation::GAMEPAD)
				return;

			if (this->m_inputType != ButtonInputType::RELEASE && this->m_inputType != ButtonInputType::PRESS_AND_RELEASE)
				return;

			events::gamepad::GamepadButtonReleasedEvent& releasedEvent = *static_cast<events::gamepad::GamepadButtonReleasedEvent*>(&event);
			if (releasedEvent.GetButton() != this->GetIndex())
				return;

			this->m_callback({ this->GetLocation(), ButtonInputType::RELEASE, this->GetIndex(), GetId() });
			releasedEvent.Handled = true;
			break;
		}
		case events::EventType::JOYSTICK_BUTTON_PRESSED_EVENT:
		{
			if (this->GetLocation() != InputLocation::JOYSTICK)
				return;

			if (this->m_inputType != ButtonInputType::PRESS)
				return;

			events::joystick::JoystickButtonPressedEvent& pressedEvent = *static_cast<events::joystick::JoystickButtonPressedEvent*>(&event);
			if (pressedEvent.GetButton() != this->GetIndex())
				return;

			this->m_callback({ this->GetLocation(), ButtonInputType::PRESS, this->GetIndex(), GetId() });
			pressedEvent.Handled = true;
			break;
		}
		case events::EventType::JOYSTICK_BUTTON_RELEASED_EVENT:
		{
			if (this->GetLocation() != InputLocation::JOYSTICK)
				return;

			if (this->m_inputType != ButtonInputType::RELEASE && this->m_inputType != ButtonInputType::PRESS_AND_RELEASE)
				return;

			events::joystick::JoystickButtonReleasedEvent& releasedEvent = *static_cast<events::joystick::JoystickButtonReleasedEvent*>(&event);
			if (releasedEvent.GetButton() != this->GetIndex())
				return;

			this->m_callback({ this->GetLocation(), ButtonInputType::RELEASE, this->GetIndex(), GetId() });
			releasedEvent.Handled = true;
			break;
		}
		default:
			break;
		}
	}

	void ButtonInputBinding::BindCallback(ButtonCallback callback)
	{
		this->m_callback = callback;
	}
} // namespace gp1::input
