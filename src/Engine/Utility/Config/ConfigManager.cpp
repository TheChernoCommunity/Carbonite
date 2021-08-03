//
//	Created by MarcasRealAccount on 8. Oct. 2020
//	Edited by MarcasRealAccount on 29. Oct. 2020
//

#include "Engine/Utility/Config/ConfigManager.h"

namespace gp1::config
{
	std::unordered_map<std::string, ConfigFile*> ConfigManager::s_ConfigFiles;

	void ConfigManager::SaveConfigs()
	{
		for (auto configFile : ConfigManager::s_ConfigFiles)
			configFile.second->SaveConfig();
	}

	ConfigFile* ConfigManager::GetConfigFile(const std::string& id)
	{
		auto itr = ConfigManager::s_ConfigFiles.find(id);
		if (itr != ConfigManager::s_ConfigFiles.end())
			return itr->second;
		ConfigFile* file = new ConfigFile("Configs/" + id);
		file->ReadConfig();
		ConfigManager::s_ConfigFiles.insert({ id, file });
		return file;
	}

	ConfigFile* ConfigManager::GetConfigFilePath(const std::string& filePath)
	{
		auto itr = ConfigManager::s_ConfigFiles.find(filePath);
		if (itr != ConfigManager::s_ConfigFiles.end())
			return itr->second;
		ConfigFile* file = new ConfigFile(filePath);
		file->ReadConfig();
		ConfigManager::s_ConfigFiles.insert({ filePath, file });
		return file;
	}

	void ConfigManager::RemoveConfigFile(ConfigFile* configFile)
	{
		auto itr = ConfigManager::s_ConfigFiles.find(configFile->GetKey());
		if (itr != ConfigManager::s_ConfigFiles.end())
			ConfigManager::s_ConfigFiles.erase(itr);
	}

} // namespace gp1::config
