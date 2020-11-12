//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	Edited by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Utility/Config/ConfigManager.h"

namespace gp1 {

	namespace config {

		std::unordered_map<std::string, ConfigFile*> ConfigManager::ConfigFiles;

		void ConfigManager::SaveConfigs() {
			for (auto configFile : ConfigManager::ConfigFiles)
				configFile.second->SaveConfig();
		}

		ConfigFile* ConfigManager::GetConfigFile(const std::string& id) {
			auto itr = ConfigManager::ConfigFiles.find(id);
			if (itr != ConfigManager::ConfigFiles.end())
				return itr->second;
			ConfigFile* file = new ConfigFile("Configs/" + id);
			file->ReadConfig();
			ConfigManager::ConfigFiles.insert({ id, file });
			return file;
		}

		ConfigFile* ConfigManager::GetConfigFilePath(const std::string& filePath) {
			auto itr = ConfigManager::ConfigFiles.find(filePath);
			if (itr != ConfigManager::ConfigFiles.end())
				return itr->second;
			ConfigFile* file = new ConfigFile(filePath);
			file->ReadConfig();
			ConfigManager::ConfigFiles.insert({ filePath, file });
			return file;
		}

		void ConfigManager::RemoveConfigFile(ConfigFile* configFile) {
			auto itr = ConfigManager::ConfigFiles.find(configFile->GetKey());
			if (itr != ConfigManager::ConfigFiles.end())
				ConfigManager::ConfigFiles.erase(itr);
		}

	} // namespace config

} // namespace gp1
