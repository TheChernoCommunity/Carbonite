//
//	Created by MarcasRealAccount on 8. Oct. 2020
//	Edited by MarcasRealAccount on 29. Oct. 2020
//

#pragma once

#include "Engine/Utility/Config/ConfigFile.h"

#include <string>
#include <unordered_map>

namespace gp1::config
{
	class ConfigFile;

	class ConfigManager
	{
	public:
		// Saves all ConfigFiles.
		static void SaveConfigs();

		// Get or create a ConfigFile that can be used to store configs.
		static ConfigFile* GetConfigFile(const std::string& id);
		// Get or create a ConfigFile at a custom file path instead of "Configs/".
		static ConfigFile* GetConfigFilePath(const std::string& filePath);

		friend ConfigFile;

	private:
		// Removes a config file.
		static void RemoveConfigFile(ConfigFile* configFile);

	private:
		static std::unordered_map<std::string, ConfigFile*> s_ConfigFiles; // Already created config files.
	};

} // namespace gp1::config
