//
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

template <typename T>
using EnumVector = std::vector<std::pair<T, std::string>>;

namespace gp1::config
{
	class ConfigFile;

	struct ConfigSection
	{
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
		// Sets a config value with an enum value name.
		template <typename T>
		void SetConfigEnum(const std::string& key, T value, const EnumVector<T>& enumNames)
		{
			auto itr = enumNames.begin();
			while (itr != enumNames.end())
			{
				if (itr->first == value)
				{
					SetConfig(key, itr->second);
					break;
				}
				itr++;
			}
		}

		// Gets the element T that the config's value was the same as.
		template <typename T>
		T GetConfigEnum(const std::string& key, T def, const EnumVector<T>& enumNames)
		{
			auto itr = enumNames.begin();
			while (itr != enumNames.end())
			{
				if (itr->first == def)
				{
					break;
				}
				itr++;
			}
			if (itr == enumNames.end()) return def;

			const std::string& configValue = GetConfig(key, itr->second);

			itr = enumNames.begin();
			while (itr != enumNames.end())
			{
				if (itr->second == configValue)
					return itr->first;
				itr++;
			}
			return def;
		}

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
		std::string    m_Key;    // This sections key.
		ConfigSection* m_Parent; // This sections parent.

		std::unordered_map<std::string, std::string>    m_Configs;         // The configs.
		std::unordered_map<std::string, ConfigSection*> m_Sections;        // The sections.
		bool                                            m_Changed = false; // Has this section changed.
	};

} // namespace gp1::config
