//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#include "Engine/Input/InputGroup.h"
#include "Engine/Input/InputHandler.h"
#include "Engine/Events/Event.h"

#include <exception>

namespace gp1 {

	namespace input {

		InputGroup::InputGroup(std::string id)
			: m_id(id) {}

		InputGroup::~InputGroup() {
			InputHandler::RemoveInputGroupImpl(this);
		}

		void InputGroup::attach() {
			InputHandler::SetCurrentActiveInputGroup(this);
		}

		void InputGroup::detach() {
			InputHandler::SetCurrentActiveInputGroup(nullptr);
		}

		void InputGroup::HandleEvent(Event& event) {
			for (auto binding : this->m_inputBindings) {
				binding.second->HandleEvent(event);
				if (event.Handled)
					return;
			}
		}

		IInputBinding* InputGroup::GetInputBinding(std::string id) {
			auto itr = this->m_inputBindings.find(id);
			if (itr != this->m_inputBindings.end())
				return itr->second;
			return nullptr;
		}

		void InputGroup::RemoveInputBindingImpl(IInputBinding* binding) {
			auto itr = this->m_inputBindings.find(binding->GetId());
			if (itr != this->m_inputBindings.end())
				this->m_inputBindings.erase(itr);
		}

		void InputGroup::RemoveInputBinding(IInputBinding* binding) {
			delete binding;
		}

		ButtonInputBinding* InputGroup::CreateButtonInputBinding(std::string id, uint32_t button, ButtonInputType inputType, InputLocation location, ButtonCallback callback) {
			InputHandler::GetBindingConfigs(this->m_id + "." + id, &location, &button);
			ButtonInputBinding* binding = new ButtonInputBinding(this, this->m_id + "." + id, button, inputType, location, callback);
			this->m_inputBindings.insert(std::pair(id, binding));
			return binding;
		}

		AxisInputBinding* InputGroup::CreateAxisInputBinding(std::string id, uint32_t axis, InputLocation location, AxisCallback callback) {
			InputHandler::GetBindingConfigs(this->m_id + "." + id, &location, &axis);
			AxisInputBinding* binding = new AxisInputBinding(this, this->m_id + "." + id, axis, location, callback);
			this->m_inputBindings.insert(std::pair(id, binding));
			return binding;
		}

		const std::string& InputGroup::GetId() const {
			return this->m_id;
		}

	} // namespace input

} // namespace gp1
