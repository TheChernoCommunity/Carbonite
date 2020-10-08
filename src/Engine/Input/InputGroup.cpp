#include "Engine/Input/InputGroup.h"
#include "Engine/Input/InputHandler.h"
#include "Engine/Events/Event.h"

#include <exception>

namespace gp1 {

	namespace input {

		InputGroup::InputGroup(InputHandler* inputHandler, std::string id) {
			if (inputHandler == nullptr) {
				throw std::exception("InputGroup can't take a nullptr to an InputHandler!");
			}

			this->m_inputHandler = inputHandler;
			this->m_id = id;
		}

		InputGroup::~InputGroup() {
			this->m_inputHandler->RemoveInputGroupImpl(this);
		}

		void InputGroup::attach() {
			this->m_inputHandler->SetCurrentActiveInputGroup(this);
		}

		void InputGroup::detach() {
			this->m_inputHandler->SetCurrentActiveInputGroup(nullptr);
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

		ButtonInputBinding* InputGroup::CreateButtonInputBinding(std::string id, InputLocation location, ButtonInputType inputType, uint32_t button, ButtonCallback callback) {
			ButtonInputBinding* binding = new ButtonInputBinding(this, this->m_id + "." + id, location, inputType, button, callback);
			this->m_inputBindings.insert(std::pair(id, binding));
			return binding;
		}

		AxisInputBinding* InputGroup::CreateAxisInputBinding(std::string id, InputLocation location, uint32_t axis, AxisCallback callback) {
			AxisInputBinding* binding = new AxisInputBinding(this, this->m_id + "." + id, location, axis, callback);
			this->m_inputBindings.insert(std::pair(id, binding));
			return binding;
		}

		const std::string& InputGroup::GetId() const {
			return this->m_id;
		}

	} // namespace input

} // namespace gp1
