//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	Edited by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once

#include "Engine/Utility/Config/ConfigFile.h"

#include <string>
#include <unordered_map>

namespace gp1 {

	namespace config {

		class ConfigFile;

		class ConfigManager {
		public:
			// Saves all ConfigFiles.
			static void SaveConfigs();

			// Get or create a ConfigFile that can be used to store configs.
			static ConfigFile* GetConfigFile(std::string id);

			friend ConfigFile;
		private:
			// Removes a config file.
			static void RemoveConfigFile(ConfigFile* configFile);

		private:
			static std::unordered_map<std::string, ConfigFile*> ConfigFiles;	// Already created config files.
		};

	} // namespace config

} // namespace gp1
