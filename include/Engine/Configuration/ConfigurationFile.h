//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#pragma once

#include <string>
#include <unordered_map>

//	TODO's for anyone looking at this file:
//		Memory Management ;)

namespace gp1 {

	namespace configuration {

		class ConfigurationFile {
		public:
			ConfigurationFile(std::string id, std::string filePath);
			~ConfigurationFile();

			// Reads and parses the configuration file.
			void ReadConfiguration();
			// Writes to the configuration file.
			void SaveConfiguration();

			// Sets a config's value.
			void SetConfig(std::string configId, std::string configValue);
			// Removes a config.
			void RemoveConfig(std::string configId);
			// Gets a config.
			const std::string* GetConfig(std::string configId);

			// Gets the id of this ConfigurationFile.
			const std::string& GetId() const;

		private:
			std::string m_id;										// The id of this ConfigurationFile
			std::string m_filePath;									// The path to the configuration file

			std::unordered_map<std::string, std::string> m_configs;	// The configs for this ConfigurationFile
		};

	} // namespace configuration

} // namespace gp1
