//
//	Created by MarcasRealAccount on 8. Oct. 2020
//

#include "Engine/Input/InputGroup.h"
#include "Engine/Events/Event.h"
#include "Engine/Input/InputHandler.h"

#include <exception>

namespace gp1::input
{
	InputGroup::InputGroup(const std::string& id)
	    : m_id(id) {}

	InputGroup::~InputGroup()
	{
		for (auto binding : this->m_inputBindings)
			delete binding.second;
	}

	void InputGroup::attach()
	{
		InputHandler::SetCurrentActiveInputGroup(this);
	}

	void InputGroup::detach()
	{
		InputHandler::SetCurrentActiveInputGroup(nullptr);
	}

	void InputGroup::SetCaptureMouse(bool captureMouse)
	{
		this->m_CaptureMouse = captureMouse;
	}

	bool InputGroup::DoesCaptureMouse() const
	{
		return this->m_CaptureMouse;
	}

	void InputGroup::HandleEvent(events::Event& event)
	{
		for (auto binding : this->m_inputBindings)
		{
			binding.second->HandleEvent(event);
			if (event.Handled)
				return;
		}
	}

	IInputBinding* InputGroup::GetInputBinding(const std::string& id)
	{
		auto itr = this->m_inputBindings.find(id);
		if (itr != this->m_inputBindings.end())
			return itr->second;
		return nullptr;
	}

	void InputGroup::RemoveInputBindingImpl(IInputBinding* binding)
	{
		auto itr = this->m_inputBindings.find(binding->GetId());
		if (itr != this->m_inputBindings.end())
			this->m_inputBindings.erase(itr);
	}

	void InputGroup::RemoveInputBinding(IInputBinding* binding)
	{
		delete binding;
	}

	ButtonInputBinding* InputGroup::CreateButtonInputBinding(const std::string& id, uint32_t button, ButtonInputType inputType, InputLocation location, ButtonCallback callback)
	{
		if (this->m_inputBindings.find(id) != this->m_inputBindings.end())
			return nullptr;

		InputHandler::GetBindingConfigs(this->m_id + "." + id, InputType::BUTTON, &location, &button);
		ButtonInputBinding* binding = new ButtonInputBinding(this, id, button, inputType, location, callback);
		this->m_inputBindings.insert(std::pair(id, binding));
		return binding;
	}

	AxisInputBinding* InputGroup::CreateAxisInputBinding(const std::string& id, uint32_t axis, InputLocation location, AxisCallback callback)
	{
		if (this->m_inputBindings.find(id) != this->m_inputBindings.end())
			return nullptr;

		InputHandler::GetBindingConfigs(this->m_id + "." + id, InputType::AXIS, &location, &axis);
		AxisInputBinding* binding = new AxisInputBinding(this, id, axis, location, callback);
		this->m_inputBindings.insert(std::pair(id, binding));
		return binding;
	}

	const std::string& InputGroup::GetId() const
	{
		return this->m_id;
	}

} // namespace gp1::input
