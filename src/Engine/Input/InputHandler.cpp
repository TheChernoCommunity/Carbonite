//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#pragma once

#include "Engine/Input/InputHandler.h"
#include "Engine/Utility/Config/ConfigManager.h"
#include "Engine/Events/Event.h"

namespace gp1 {

	namespace input {

		std::unordered_map<std::string, InputGroup*> InputHandler::m_inputGroups;
		InputGroup* InputHandler::m_currentInputGroup = nullptr;

		void InputHandler::CleanUp() {
			for (auto group : InputHandler::m_inputGroups) {
				delete group.second;
			}
		}

		bool InputHandler::HandleEvent(Event& event) {
			if (InputHandler::m_currentInputGroup != nullptr) {
				InputHandler::m_currentInputGroup->HandleEvent(event);
			}
			return event.Handled;
		}

		void InputHandler::SetCurrentActiveInputGroup(const std::string& id) {
			SetCurrentActiveInputGroup(GetInputGroup(id));
		}

		void InputHandler::SetCurrentActiveInputGroup(InputGroup* inputGroup) {
			InputHandler::m_currentInputGroup = inputGroup;
		}

		InputGroup* InputHandler::CreateInputGroup(const std::string& id) {
			if (InputHandler::m_inputGroups.find(id) != InputHandler::m_inputGroups.end())
				return nullptr;

			InputGroup* inputGroup = new InputGroup(id);
			InputHandler::m_inputGroups.insert(std::pair(id, inputGroup));
			if (InputHandler::m_currentInputGroup == nullptr)
				InputHandler::m_currentInputGroup = inputGroup;
			return inputGroup;
		}

		InputGroup* InputHandler::GetInputGroup(const std::string& id) {
			auto itr = InputHandler::m_inputGroups.find(id);
			if (itr != InputHandler::m_inputGroups.end())
				return itr->second;
			return nullptr;
		}

		InputGroup* InputHandler::GetOrCreateInputGroup(const std::string& id) {
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

		void InputHandler::SetBindingConfigs(const std::string& id, InputLocation location, uint32_t index) {
			config::ConfigFile* inputBindings = config::ConfigManager::GetConfigFile("InputBindings");
			config::ConfigSection* sec = inputBindings->GetOrCreateSection(id);
			sec->SetConfigTyped<uint32_t>("Location", static_cast<uint32_t>(location));
			sec->SetConfigTyped<uint32_t>("Index", index);
		}

		void InputHandler::GetBindingConfigs(const std::string& id, InputLocation* location, uint32_t* index) {
			config::ConfigFile* inputBindings = config::ConfigManager::GetConfigFile("InputBindings");
			config::ConfigSection* sec = inputBindings->GetOrCreateSection(id);
			uint32_t confLoc = sec->GetConfigTyped<uint32_t>("Location", static_cast<uint32_t>(*location));
			if (confLoc > static_cast<uint32_t>(InputLocation::LAST))
				*location = InputLocation::UNKNOWN;
			else
				*location = static_cast<InputLocation>(confLoc);
			*index = sec->GetConfigTyped<uint32_t>("Index", *index);
		}

	} // namespace input

} // namespace gp1
