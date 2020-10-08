//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#pragma once

#include "Engine/Input/InputHandler.h"

namespace gp1 {

	namespace input {

		void InputHandler::HandleEvent(Event& event) {
			if (this->m_currentInputGroup != nullptr) {
				this->m_currentInputGroup->HandleEvent(event);
			}
		}

		void InputHandler::SetCurrentActiveInputGroup(std::string id) {
			SetCurrentActiveInputGroup(GetInputGroup(id));
		}

		void InputHandler::SetCurrentActiveInputGroup(InputGroup* inputGroup) {
			this->m_currentInputGroup = inputGroup;
		}

		InputGroup* InputHandler::CreateInputGroup(std::string id) {
			InputGroup* inputGroup = new InputGroup(this, id);
			this->m_inputGroups.insert(std::pair(id, inputGroup));
			if (this->m_currentInputGroup == nullptr)
				this->m_currentInputGroup = inputGroup;
			return inputGroup;
		}

		InputGroup* InputHandler::GetInputGroup(std::string id) {
			auto itr = this->m_inputGroups.find(id);
			if (itr != this->m_inputGroups.end())
				return itr->second;
			return nullptr;
		}

		void InputHandler::RemoveInputGroupImpl(InputGroup* inputGroup) {
			auto itr = this->m_inputGroups.find(inputGroup->GetId());
			if (itr != this->m_inputGroups.end())
				this->m_inputGroups.erase(itr);
		}

		void InputHandler::RemoveInputGroup(InputGroup* inputGroup) {
			delete inputGroup;
		}

	} // namespace input

} // namespace gp1
