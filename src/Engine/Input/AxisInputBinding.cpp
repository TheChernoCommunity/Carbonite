//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#include "Engine/Input/AxisInputBinding.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/MouseEvent.h"

namespace gp1 {

	namespace input {

		AxisInputBinding::AxisInputBinding(InputGroup* inputGroup, std::string id, InputLocation location, uint32_t axis, AxisCallback callback)
			: IInputBinding(inputGroup, id, gp1::input::InputType::AXIS, location, axis), m_callback(callback) {}

		void AxisInputBinding::HandleEvent(Event& event) {
			EventType eventType = event.GetType();
			switch (eventType) {
			case EventType::MOUSE_MOVED_EVENT:
			{
				if (this->GetLocation() != InputLocation::MOUSE)
					return;
				MouseMovedEvent& movedEvent = *((MouseMovedEvent*)&event);

				if (MouseMovedEvent::GetXAxisIndex() == this->GetIndex()) {
					this->m_callback(this->GetLocation(), this->GetIndex(), movedEvent.GetX());
				} else if (MouseMovedEvent::GetYAxisIndex() == this->GetIndex()) {
					this->m_callback(this->GetLocation(), this->GetIndex(), movedEvent.GetY());
				}

				break;
			}
			}
		}

	} // namespace input

} // namespace gp1
