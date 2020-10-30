//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#include "Engine/Input/AxisInputBinding.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/MouseEvent.h"

namespace gp1 {

	namespace input {

		AxisInputBinding::AxisInputBinding(InputGroup* inputGroup, const std::string& id, uint32_t axis, InputLocation location, AxisCallback callback)
			: IInputBinding(inputGroup, id, gp1::input::InputType::AXIS, axis, location), m_callback(callback) {}

		void AxisInputBinding::HandleEvent(Event& event) {
			if (this->m_callback == nullptr)
				return;

			EventType eventType = event.GetType();
			switch (eventType) {
			case EventType::MOUSE_MOVED_EVENT:
			{
				if (this->GetLocation() != InputLocation::MOUSE)
					return;
				MouseMovedEvent& movedEvent = *(reinterpret_cast<MouseMovedEvent*>(&event));

				if (this->GetIndex() == axises::mouseX) {
					this->m_callback({ this->GetLocation(), this->GetIndex(), (double)movedEvent.GetX(), GetId() });
				} else if (this->GetIndex() == axises::mouseY) {
					this->m_callback({ this->GetLocation(), this->GetIndex(), (double)movedEvent.GetY(), GetId() });
				}

				break;
			}
			case EventType::MOUSE_SCROLLED_EVENT:
			{
				if (this->GetLocation() != InputLocation::MOUSE)
					return;
				MouseScrollEvent& scrollEvent = *static_cast<MouseScrollEvent*>(&event);

				if (this->GetIndex() == axises::mouseWheelX) {
					this->m_callback({ this->GetLocation(), this->GetIndex(), scrollEvent.GetX(), GetId() });
				} else if (this->GetIndex() == axises::mouseWheelY) {
					this->m_callback({ this->GetLocation(), this->GetIndex(), scrollEvent.GetY(), GetId() });
				}

				break;
			}
			}
		}

		void AxisInputBinding::BindCallback(AxisCallback callback) {
			this->m_callback = callback;
		}

	} // namespace input

} // namespace gp1
