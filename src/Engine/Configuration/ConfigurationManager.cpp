//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#include "Engine/Configuration/ConfigurationManager.h"

namespace gp1 {

	namespace configuration {

		std::unordered_map<std::string, ConfigurationFile*> ConfigurationManager::ConfigurationFiles;

		void ConfigurationManager::SaveConfigurations() {
			for (auto configurationFile : ConfigurationManager::ConfigurationFiles)
				configurationFile.second->SaveConfiguration();
		}

		ConfigurationFile* ConfigurationManager::CreateConfigurationFile(std::string id, std::string filePath) {
			ConfigurationFile* configurationFile = new ConfigurationFile(id, filePath);
			configurationFile->ReadConfiguration();
			ConfigurationManager::ConfigurationFiles.insert(std::pair(id, configurationFile));
			return configurationFile;
		}

		ConfigurationFile* ConfigurationManager::GetConfigurationFile(std::string id) {
			auto itr = ConfigurationManager::ConfigurationFiles.find(id);
			if (itr != ConfigurationManager::ConfigurationFiles.end())
				return itr->second;
			return nullptr;
		}

		void ConfigurationManager::RemoveConfigurationFileImpl(ConfigurationFile* configurationFile) {
			auto itr = ConfigurationManager::ConfigurationFiles.find(configurationFile->GetId());
			if (itr != ConfigurationManager::ConfigurationFiles.end())
				ConfigurationManager::ConfigurationFiles.erase(itr);
		}

		void ConfigurationManager::RemoveConfigurationFile(ConfigurationFile* configurationFile) {
			delete configurationFile;
		}

	} // namespace configuration

} // namespace gp1
