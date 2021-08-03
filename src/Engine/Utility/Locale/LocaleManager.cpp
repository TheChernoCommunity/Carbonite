#include "Engine/Utility/Locale/LocaleManager.h"
#include "Engine/Utility/Config/ConfigFile.h"
#include "Engine/Utility/Config/ConfigManager.h"

namespace gp1::locale
{
	std::string                                  LocaleManager::s_LanguageCode;
	std::unordered_map<std::string, std::string> LocaleManager::s_Localizations;

	void AddConfigsToMap(config::ConfigSection* section, std::unordered_map<std::string, std::string>& map, const std::string& currentSectionName = "")
	{
		if (section == nullptr)
			return;

		// Loop through all configs in the section and insert them into the map.
		auto configs = section->GetConfigs();
		for (auto& config : configs)
		{
			map.insert({ currentSectionName + config.first, config.second });
		}

		// Loop through all sections in the section and add all their configs into the map.
		auto sections = section->GetSections();
		for (auto& subSection : sections)
		{
			AddConfigsToMap(subSection.second, map, currentSectionName + subSection.second->GetKey() + ".");
		}
	}

	const std::string& LocaleManager::GetLanguageCode()
	{
		return LocaleManager::s_LanguageCode;
	}

	void LocaleManager::SetLocalization(const std::string& languageCode)
	{
		if (languageCode == LocaleManager::s_LanguageCode)
			return;

		// Clear the old localizations.
		LocaleManager::s_Localizations.clear();

		// Load the lang file as an .ini file and add all its configs to the localizations map.
		config::ConfigFile* config = config::ConfigManager::GetConfigFilePath("locale/" + languageCode);
		if (config)
		{
			AddConfigsToMap(config, LocaleManager::s_Localizations);
			delete config; // Delete the config to save ram.
			LocaleManager::s_LanguageCode = languageCode;
		}
	}

	std::string LocaleManager::GetLocalizedString(const std::string& key)
	{
		auto itr = LocaleManager::s_Localizations.find(key);
		if (itr != LocaleManager::s_Localizations.end())
		{
			return itr->second;
		}
		return "";
	}

} // namespace gp1::locale
