//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#pragma once

#include "Engine/Input/InputHandler.h"
#include "Engine/Configuration/ConfigurationManager.h"

namespace gp1 {

	namespace input {

		std::unordered_map<std::string, InputGroup*> InputHandler::m_inputGroups;
		InputGroup* InputHandler::m_currentInputGroup = nullptr;

		void InputHandler::HandleEvent(Event& event) {
			if (InputHandler::m_currentInputGroup != nullptr) {
				InputHandler::m_currentInputGroup->HandleEvent(event);
			}
		}

		void InputHandler::SetCurrentActiveInputGroup(std::string id) {
			SetCurrentActiveInputGroup(GetInputGroup(id));
		}

		void InputHandler::SetCurrentActiveInputGroup(InputGroup* inputGroup) {
			InputHandler::m_currentInputGroup = inputGroup;
		}

		InputGroup* InputHandler::CreateInputGroup(std::string id) {
			InputGroup* inputGroup = new InputGroup(id);
			InputHandler::m_inputGroups.insert(std::pair(id, inputGroup));
			if (InputHandler::m_currentInputGroup == nullptr)
				InputHandler::m_currentInputGroup = inputGroup;
			return inputGroup;
		}

		InputGroup* InputHandler::GetInputGroup(std::string id) {
			auto itr = InputHandler::m_inputGroups.find(id);
			if (itr != InputHandler::m_inputGroups.end())
				return itr->second;
			return nullptr;
		}

		InputGroup* InputHandler::GetOrCreateInputGroup(std::string id) {
			InputGroup* inputGroup = GetInputGroup(id);
			if (inputGroup != nullptr)
				return inputGroup;
			return CreateInputGroup(id);
		}

		void InputHandler::RemoveInputGroupImpl(InputGroup* inputGroup) {
			auto itr = InputHandler::m_inputGroups.find(inputGroup->GetId());
			if (itr != InputHandler::m_inputGroups.end())
				InputHandler::m_inputGroups.erase(itr);
		}

		void InputHandler::RemoveInputGroup(InputGroup* inputGroup) {
			delete inputGroup;
		}

		void InputHandler::SetBindingConfigs(std::string id, InputLocation location, uint32_t index) {
			configuration::ConfigurationFile* inputBindings = configuration::ConfigurationManager::GetOrCreateConfigurationFile("InputBindings", "configs/inputBindings.conf");
			char buf[32];	// 12 For "Loc: , Ind: " and 10 for each number so 32 characters should be the maximum obtainable.
			sprintf_s(buf, "Loc: %u, Ind: %u", (uint32_t)location, index);
			inputBindings->SetConfig(id, buf);
		}

		void InputHandler::GetBindingConfigs(std::string id, InputLocation* location, uint32_t* index) {
			configuration::ConfigurationFile* inputBindings = configuration::ConfigurationManager::GetOrCreateConfigurationFile("InputBindings", "configs/inputBindings.conf");
			const std::string* config = inputBindings->GetConfig(id);
			if (config == nullptr) {
				SetBindingConfigs(id, *location, *index);
			} else {
				uint32_t confLoc;
				sscanf_s(config->c_str(), "Loc: %u, Ind: %u", &confLoc, index);
				if (confLoc > (uint32_t)InputLocation::LAST)
					*location = InputLocation::UNKNOWN;
				else
					*location = (InputLocation)confLoc;
			}
		}

	} // namespace input

} // namespace gp1
