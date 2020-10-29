//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once

#include <string>
#include <unordered_map>

namespace gp1 {

	namespace config {

		class ConfigFile;

		struct ConfigSection {
		public:
			ConfigSection(std::string key, ConfigSection* parent = nullptr);
			~ConfigSection();

			// Cleans up the config file.
			void CleanUp();

			// Gets all the config values.
			const std::unordered_map<std::string, std::string>& GetConfigs() const;
			// Gets all the sections.
			const std::unordered_map<std::string, ConfigSection*>& GetSections() const;
			// Sets a config value.
			void SetConfig(std::string key, std::string value);
			// Gets or creates a config value.
			std::string GetConfig(std::string key, std::string def = "");
			// Gets a section.
			ConfigSection* GetSection(std::string key) const;
			// Gets or creates a section.
			ConfigSection* GetOrCreateSection(std::string key);

			// Sets a config value with an int value.
			void SetConfigInt(std::string key, int64_t value);
			// Sets a config value with an unsigned int value.
			void SetConfigUInt(std::string key, uint64_t value);
			// Sets a config value with a bool value.
			void SetConfigBool(std::string key, bool value);

			// Get int value of a config.
			int64_t GetConfigInt(std::string key, int64_t def = 0);
			// Get unsigned int value of a config.
			uint64_t GetConfigUInt(std::string key, uint64_t def = 0);
			// Get bool value of a config.
			bool GetConfigBool(std::string key, bool def = false);

			// Get the key.
			std::string GetKey() const;
			// Get the full key with the parent's key.
			std::string GetFullKey() const;

			friend ConfigFile;

		private:
			// Get the file string.
			std::string Save(bool first = true);
			// Get the file string.
			std::string Save(bool& firstSection, bool first = true);
			// Remove a section.
			void RemoveSection(ConfigSection* section);

		private:
			std::string m_Key;											// This sections key.
			ConfigSection* m_Parent;									// This sections parent.

			std::unordered_map<std::string, std::string> m_Configs;		// The configs.
			std::unordered_map<std::string, ConfigSection*> m_Sections;	// The sections.
		};

	} // namespace config

} // namespace gp1
