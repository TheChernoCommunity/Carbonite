//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#include "Engine/Input/IInputBinding.h"
#include "Engine/Configuration/ConfigurationManager.h"
#include "Engine/Input/InputGroup.h"

#include <exception>
#include <filesystem>

namespace gp1 {

	namespace input {

		IInputBinding::IInputBinding(InputGroup* inputGroup, std::string id, InputType type, InputLocation location, uint32_t index) {
			if (inputGroup == nullptr) {
				throw std::exception("IInputBinding can't take a nullptr to an InputGroup!");
			}

			this->m_inputGroup = inputGroup;
			this->m_id = id;
			this->m_type = type;

			configuration::ConfigurationFile* inputBindings = configuration::ConfigurationManager::GetConfigurationFile("InputBindings");
			if (inputBindings == nullptr)
				inputBindings = configuration::ConfigurationManager::CreateConfigurationFile("InputBindings", "configs/inputBindings.conf");
			const std::string* config = inputBindings->GetConfig(id);
			if (config == nullptr) {
				char buf[52]; // 12 For "Loc: , Ind: " and 20 for each number so 52 character should be the maximum obtainable.
				sprintf_s(buf, "Loc: %u, Ind: %u", (uint32_t)location, index);

				inputBindings->SetConfig(id, buf);

				this->m_location = location;
				this->m_index = index;
			} else {
				uint32_t configLoc = (uint32_t)location;
				uint32_t configInd = index;
				sscanf_s(config->c_str(), "Loc: %u, Ind: %u", &configLoc, &configInd);

				if (configLoc > (uint32_t)InputLocation::LAST)
					this->m_location = InputLocation::UNKNOWN;
				else
					this->m_location = (InputLocation)configLoc;

				this->m_index = configInd;
			}
		}

		IInputBinding::~IInputBinding() {
			this->m_inputGroup->RemoveInputBindingImpl(this);
		}

		void IInputBinding::SetBinding(InputLocation location, uint32_t index) {
			configuration::ConfigurationFile* inputBindings = configuration::ConfigurationManager::GetConfigurationFile("InputBindings");
			if (inputBindings == nullptr)
				inputBindings = configuration::ConfigurationManager::CreateConfigurationFile("InputBindings", "configs/inputBindings.conf");
			char buf[52]; // 12 For "Loc: , Ind: " and 20 for each number so 52 character should be the maximum obtainable.
			sprintf_s(buf, "Loc: %u, Ind: %u", location, index);

			inputBindings->SetConfig(this->m_id, buf);
			this->m_location = location;
			this->m_index = index;
		}

		void IInputBinding::SetInputLocation(InputLocation location) {
			configuration::ConfigurationFile* inputBindings = configuration::ConfigurationManager::GetConfigurationFile("InputBindings");
			if (inputBindings == nullptr)
				inputBindings = configuration::ConfigurationManager::CreateConfigurationFile("InputBindings", "configs/inputBindings.conf");
			char buf[52]; // 12 For "Loc: , Ind: " and 20 for each number so 52 character should be the maximum obtainable.
			sprintf_s(buf, "Loc: %u, Ind: %u", (uint32_t)location, this->m_index);

			inputBindings->SetConfig(this->m_id, buf);
			this->m_location = location;
		}

		void IInputBinding::SetIndex(uint32_t index) {
			configuration::ConfigurationFile* inputBindings = configuration::ConfigurationManager::GetConfigurationFile("InputBindings");
			if (inputBindings == nullptr)
				inputBindings = configuration::ConfigurationManager::CreateConfigurationFile("InputBindings", "configs/inputBindings.conf");
			char buf[52]; // 12 For "Loc: , Ind: " and 20 for each number so 52 character should be the maximum obtainable.
			sprintf_s(buf, "Loc: %u, Ind: %u", (uint32_t)this->m_location, index);

			inputBindings->SetConfig(this->m_id, buf);
			this->m_index = index;
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
