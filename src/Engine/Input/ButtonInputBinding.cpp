//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#include "Engine/Input/ButtonInputBinding.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace gp1 {

	namespace input {

		ButtonInputBinding::ButtonInputBinding(InputGroup* inputGroup, const std::string& id, uint32_t button, ButtonInputType inputType, InputLocation location, ButtonCallback callback)
			: IInputBinding(inputGroup, id, InputType::BUTTON, button, location), m_inputType(inputType), m_callback(callback) {}

		void ButtonInputBinding::HandleEvent(Event& event) {
			if (this->m_callback == nullptr)
				return;

			EventType eventType = event.GetType();
			switch (eventType) {
			case EventType::KEY_PRESSED_EVENT:
			{
				if (this->GetLocation() != InputLocation::KEYBOARD)
					return;

				KeyPressedEvent& pressedEvent = *(reinterpret_cast<KeyPressedEvent*>(&event));
				if ((uint32_t)pressedEvent.GetKey() != this->GetIndex())
					return;

				if (pressedEvent.IsRepeat()) {
					if (this->m_inputType != ButtonInputType::REPEAT)
						return;
				} else {
					if (this->m_inputType != ButtonInputType::PRESS)
						return;
				}

				this->m_callback({ this->GetLocation(), this->m_inputType, this->GetIndex(), GetId() });
				event.Handled = true;
				break;
			}
			case EventType::KEY_RELEASED_EVENT:
			{
				if (this->GetLocation() != InputLocation::KEYBOARD)
					return;

				KeyReleasedEvent& releasedEvent = *(reinterpret_cast<KeyReleasedEvent*>(&event));
				if ((uint32_t)releasedEvent.GetKey() != this->GetIndex())
					return;

				if (this->m_inputType != ButtonInputType::RELEASE)
					return;

				this->m_callback({ this->GetLocation(), this->m_inputType, this->GetIndex(), GetId() });
				event.Handled = true;
				break;
			}
			case EventType::MOUSE_BUTTON_PRESSED_EVENT:
			{
				if (this->GetLocation() != InputLocation::MOUSE)
					return;

				MouseButtonPressedEvent& pressedEvent = *(reinterpret_cast<MouseButtonPressedEvent*>(&event));
				if ((uint32_t)pressedEvent.GetButton() != this->GetIndex())
					return;

				this->m_callback({ this->GetLocation(), this->m_inputType, this->GetIndex(), GetId() });
				event.Handled = true;
				break;
			}
			case EventType::MOUSE_BUTTON_RELEASED_EVENT:
			{
				if (this->GetLocation() != InputLocation::MOUSE)
					return;

				MouseButtonReleasedEvent& releasedEvent = *(reinterpret_cast<MouseButtonReleasedEvent*>(&event));
				if ((uint32_t)releasedEvent.GetButton() != this->GetIndex())
					return;

				this->m_callback({ this->GetLocation(), this->m_inputType, this->GetIndex(), GetId() });
				event.Handled = true;
				break;
			}
			}
		}

		void ButtonInputBinding::BindCallback(ButtonCallback callback) {
			this->m_callback = callback;
		}

	} // namespace input

} // namespace gp1
