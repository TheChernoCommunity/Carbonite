//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#pragma once

#include "Engine/Configuration/ConfigurationFile.h"

#include <string>
#include <unordered_map>

//	TODO's for anyone looking at this file:
//		Memory Management ;)

namespace gp1 {

	namespace configuration {

		class ConfigurationManager {
		public:
			// Saves all ConfigurationFiles.
			static void SaveConfigurations();

			// Creates a new ConfigurationFile that can be used to store configs.
			static ConfigurationFile* CreateConfigurationFile(std::string id, std::string filePath);
			// Gets a ConfigurationFile.
			static ConfigurationFile* GetConfigurationFile(std::string id);
			// This function only removes the ConfigurationFile from the 'ConfigurationFiles' variable.
			static void RemoveConfigurationFileImpl(ConfigurationFile* configurationFile);
			// This function deletes the configurationFile data. which causes it to save and remove itself from the 'ConfigurationFiles' variable.
			static void RemoveConfigurationFile(ConfigurationFile* configurationFile);

		private:
			static std::unordered_map<std::string, ConfigurationFile*> ConfigurationFiles;	// Created ConfigurationFiles.
		};

	} // namespace configuration

} // namespace gp1
