//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#include "Engine/Input/AxisInputBinding.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/MouseEvent.h"

namespace gp1 {

	namespace input {

		AxisInputBinding::AxisInputBinding(std::string id, InputLocation location, uint32_t axis, AxisCallback callback)
			: IInputBinding(id, gp1::input::InputType::AXIS, location, axis), m_callback(callback) {}

		void AxisInputBinding::HandleEvent(Event& event) {
			EventType eventType = event.GetType();
			switch (eventType) {
			case EventType::MOUSE_MOVED_EVENT:
			{
				if (this->GetLocation() != InputLocation::MOUSE)
					return;
				MouseMovedEvent& movedEvent = *((MouseMovedEvent*)&event);

				if (MouseMovedEvent::GetXAxisIndex() == this->GetIndex()) {
					this->m_callback(this->GetIndex(), movedEvent.GetX());
					event.Handled = true;
				} else if (MouseMovedEvent::GetYAxisIndex() != this->GetIndex()) {
					this->m_callback(this->GetIndex(), movedEvent.GetY());
					event.Handled = true;
				}

				break;
			}
			}
		}

	} // namespace input

} // namespace gp1
