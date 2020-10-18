//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#include "Engine/Input/IInputBinding.h"
#include "Engine/Input/InputGroup.h"
#include "Engine/Input/InputHandler.h"

#include <exception>

namespace gp1 {

	namespace input {

		IInputBinding::IInputBinding(InputGroup* inputGroup, std::string id, InputType type, uint32_t index, InputLocation location) {
			if (inputGroup == nullptr) {
				throw std::exception("IInputBinding can't take a nullptr to an InputGroup!");
			}

			this->m_inputGroup = inputGroup;
			this->m_id = id;
			this->m_type = type;
			this->m_index = index;
			this->m_location = location;
		}

		IInputBinding::~IInputBinding() {
			this->m_inputGroup->RemoveInputBindingImpl(this);
		}

		void IInputBinding::SetBinding(InputLocation location, uint32_t index) {
			this->m_location = location;
			this->m_index = index;
			InputHandler::SetBindingConfigs(this->m_inputGroup->GetId() + "." + this->m_id, this->m_location, this->m_index);
		}

		void IInputBinding::SetInputLocation(InputLocation location) {
			this->m_location = location;
			InputHandler::SetBindingConfigs(this->m_inputGroup->GetId() + "." + this->m_id, this->m_location, this->m_index);
		}

		void IInputBinding::SetIndex(uint32_t index) {
			this->m_index = index;
			InputHandler::SetBindingConfigs(this->m_inputGroup->GetId() + "." + this->m_id, this->m_location, this->m_index);
		}

		InputGroup* IInputBinding::GetInputGroup() const {
			return this->m_inputGroup;
		}

		const std::string& IInputBinding::GetId() const {
			return this->m_id;
		}

		const InputType& IInputBinding::GetType() const {
			return this->m_type;
		}

		const InputLocation& IInputBinding::GetLocation() const {
			return this->m_location;
		}

		const uint32_t& IInputBinding::GetIndex() const {
			return this->m_index;
		}

	} // namespace input

} // namespace gp1
