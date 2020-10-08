//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#include "Engine/Input/ButtonInputBinding.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace gp1 {

	namespace input {

		ButtonInputBinding::ButtonInputBinding(std::string id, InputLocation location, ButtonInputType inputType, uint32_t button, ButtonCallback callback)
			: IInputBinding(id, InputType::BUTTON, location, button), m_inputType(inputType), m_callback(callback) {}

		void ButtonInputBinding::HandleEvent(Event& event) {
			EventType eventType = event.GetType();
			switch (eventType) {
			case EventType::KEY_PRESSED_EVENT:
			{
				if (this->GetLocation() != InputLocation::KEYBOARD)
					return;

				KeyPressedEvent& pressedEvent = *((KeyPressedEvent*)&event);
				if ((uint32_t)pressedEvent.GetKey() != this->GetIndex())
					return;

				if (pressedEvent.IsRepeat()) {
					if (this->m_inputType != ButtonInputType::REPEAT)
						return;
				} else {
					if (this->m_inputType != ButtonInputType::PRESS)
						return;
				}

				this->m_callback(this->GetIndex());
				event.Handled = true;
				break;
			}
			case EventType::KEY_RELEASED_EVENT:
			{
				if (this->GetLocation() != InputLocation::KEYBOARD)
					return;

				KeyReleasedEvent& releasedEvent = *((KeyReleasedEvent*)&event);
				if ((uint32_t)releasedEvent.GetKey() != this->GetIndex())
					return;

				this->m_callback(this->GetIndex());
				event.Handled = true;
				break;
			}
			case EventType::MOUSE_BUTTON_PRESSED_EVENT:
			{
				if (this->GetLocation() != InputLocation::MOUSE)
					return;

				MouseButtonPressedEvent& pressedEvent = *((MouseButtonPressedEvent*)&event);
				if ((uint32_t)pressedEvent.GetButton() != this->GetIndex())
					return;

				this->m_callback(this->GetIndex());
				event.Handled = true;
				break;
			}
			case EventType::MOUSE_BUTTON_RELEASED_EVENT:
			{
				if (this->GetLocation() != InputLocation::MOUSE)
					return;

				MouseButtonReleasedEvent& releasedEvent = *((MouseButtonReleasedEvent*)&event);
				if ((uint32_t)releasedEvent.GetButton() != this->GetIndex())
					return;

				this->m_callback(this->GetIndex());
				event.Handled = true;
				break;
			}
			}
		}

	} // namespace input

} // namespace gp1
