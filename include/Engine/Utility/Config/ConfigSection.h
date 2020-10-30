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
			ConfigSection(const std::string& key, ConfigSection* parent = nullptr);
			~ConfigSection();

			// Cleans up the config file.
			void CleanUp();

			// Gets all the config values.
			const std::unordered_map<std::string, std::string>& GetConfigs() const;
			// Gets all the sections.
			const std::unordered_map<std::string, ConfigSection*>& GetSections() const;
			// Sets a config value.
			void SetConfig(const std::string& key, const std::string& value);
			// Gets or creates a config value.
			const std::string& GetConfig(const std::string& key, const std::string& def = "");
			// Gets a section.
			ConfigSection* GetSection(const std::string& key) const;
			// Gets or creates a section.
			ConfigSection* GetOrCreateSection(const std::string& key);

			// Sets a config value with a T value.
			template <typename T>
			void SetConfigTyped(const std::string& key, T value);
			// Get T value of a config.
			template <typename T>
			T GetConfigTyped(const std::string& key, T def);

			// Get the key.
			const std::string& GetKey() const;
			// Get the full key with the parent's key.
			std::string GetFullKey() const;

			friend ConfigFile;

		protected:
			// Has this section changed.
			bool HasChanged() const;
			// Set if this section has changed.
			void SetChanges(bool changed);

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
			bool m_Changed = false;										// Has this section changed.
		};

	} // namespace config

} // namespace gp1
