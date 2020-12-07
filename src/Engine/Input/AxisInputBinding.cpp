//
//	Created by MarcasRealAccount on 8. Oct. 2020
//

#include "Engine/Input/AxisInputBinding.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/GamepadEvent.h"
#include "Engine/Events/JoystickEvent.h"
#include "Engine/Events/MouseEvent.h"

#include <unordered_map>

namespace gp1::input
{
	double AxisCallbackData::GetDeltaValue() const
	{
		return this->m_Value - this->m_PreviousValue;
	}

	std::unordered_map<uint64_t, double> AxisInputBinding::s_PreviousAxisValues;

	AxisInputBinding::AxisInputBinding(InputGroup* inputGroup, const std::string& id, uint32_t axis, InputLocation location, AxisCallback callback)
	    : IInputBinding(inputGroup, id, gp1::input::InputType::AXIS, axis, location), m_callback(callback) {}

	void AxisInputBinding::HandleEvent(events::Event& event)
	{
		if (this->m_callback == nullptr)
			return;

		events::EventType eventType = event.GetType();
		switch (eventType)
		{
		case events::EventType::MOUSE_MOVED_EVENT:
		{
			if (this->GetLocation() != InputLocation::MOUSE)
				return;
			events::mouse::MouseMovedEvent& movedEvent = *reinterpret_cast<events::mouse::MouseMovedEvent*>(&event);

			if (this->GetIndex() == axises::mouseX)
			{
				this->m_callback({ this->GetLocation(), this->GetIndex(), movedEvent.GetX(), GetPreviousAxisValue(this->GetLocation(), this->GetIndex(), movedEvent.GetX()), GetId() });
			}
			else if (this->GetIndex() == axises::mouseY)
			{
				this->m_callback({ this->GetLocation(), this->GetIndex(), movedEvent.GetY(), GetPreviousAxisValue(this->GetLocation(), this->GetIndex(), movedEvent.GetY()), GetId() });
			}

			break;
		}
		case events::EventType::MOUSE_SCROLLED_EVENT:
		{
			if (this->GetLocation() != InputLocation::MOUSE)
				return;
			events::mouse::MouseScrollEvent& scrollEvent = *reinterpret_cast<events::mouse::MouseScrollEvent*>(&event);

			if (this->GetIndex() == axises::mouseWheelX)
			{
				this->m_callback({ this->GetLocation(), this->GetIndex(), scrollEvent.GetX(), GetPreviousAxisValue(this->GetLocation(), this->GetIndex(), scrollEvent.GetX()), GetId() });
			}
			else if (this->GetIndex() == axises::mouseWheelY)
			{
				this->m_callback({ this->GetLocation(), this->GetIndex(), scrollEvent.GetY(), GetPreviousAxisValue(this->GetLocation(), this->GetIndex(), scrollEvent.GetY()), GetId() });
			}

			break;
		}
		case events::EventType::GAMEPAD_AXIS_CHANGE_EVENT:
		{
			if (this->GetLocation() != InputLocation::GAMEPAD)
				return;
			events::gamepad::GamepadAxisEvent& axisEvent = *reinterpret_cast<events::gamepad::GamepadAxisEvent*>(&event);

			if (this->GetIndex() != axisEvent.GetAxis())
				return;

			this->m_callback({ this->GetLocation(), this->GetIndex(), axisEvent.GetValue(), GetPreviousAxisValue(this->GetLocation(), this->GetIndex(), axisEvent.GetValue()), GetId() });
			axisEvent.Handled = true;
			break;
		}
		case events::EventType::JOYSTICK_AXIS_CHANGE_EVENT:
		{
			if (this->GetLocation() != InputLocation::JOYSTICK)
				return;
			events::joystick::JoystickAxisEvent& axisEvent = *reinterpret_cast<events::joystick::JoystickAxisEvent*>(&event);

			if (this->GetIndex() != axisEvent.GetAxis())
				return;

			this->m_callback({ this->GetLocation(), this->GetIndex(), axisEvent.GetValue(), GetPreviousAxisValue(this->GetLocation(), this->GetIndex(), axisEvent.GetValue()), GetId() });
			axisEvent.Handled = true;
			break;
		}
		}
	}

	void AxisInputBinding::BindCallback(AxisCallback callback)
	{
		this->m_callback = callback;
	}

	double AxisInputBinding::GetPreviousAxisValue(InputLocation location, uint32_t axis, double value)
	{
		auto previousValue = AxisInputBinding::s_PreviousAxisValues.find(static_cast<uint64_t>(location) << 32 | axis);
		if (previousValue == AxisInputBinding::s_PreviousAxisValues.end())
		{
			auto res = AxisInputBinding::s_PreviousAxisValues.insert({ static_cast<uint64_t>(location) << 32 | axis, value });
			if (!res.second) return 0.0;
			previousValue = res.first;
		}
		return previousValue->second;
	}

	void AxisInputBinding::SetPreviousAxisValue(InputLocation location, uint32_t axis, double value)
	{
		AxisInputBinding::s_PreviousAxisValues.insert_or_assign(static_cast<uint64_t>(location) << 32 | axis, value);
	}

} // namespace gp1::input
