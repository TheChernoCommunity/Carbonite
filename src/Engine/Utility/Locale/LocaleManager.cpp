#include "Engine/Utility/Locale/LocaleManager.h"
#include "Engine/Utility/Config/ConfigManager.h"
#include "Engine/Utility/Config/ConfigFile.h"

namespace gp1 {

	namespace locale {

		std::string LocaleManager::m_LanguageCode;
		std::unordered_map<std::string, std::string> LocaleManager::m_Localizations;

		void AddConfigsToMap(config::ConfigSection* section, std::unordered_map<std::string, std::string>& map, const std::string& currentSectionName = "") {
			if (section == nullptr)
				return;

			// Loop through all configs in the section and insert them into the map.
			auto configs = section->GetConfigs();
			for (auto& config : configs) {
				map.insert({ currentSectionName + config.first, config.second });
			}

			// Loop through all sections in the section and add all their configs into the map.
			auto sections = section->GetSections();
			for (auto& section : sections) {
				AddConfigsToMap(section.second, map, currentSectionName + section.second->GetKey() + ".");
			}
		}

		const std::string& LocaleManager::GetLanguageCode() {
			return LocaleManager::m_LanguageCode;
		}

		void LocaleManager::SetLocalization(const std::string& languageCode) {
			if (languageCode == LocaleManager::m_LanguageCode)
				return;

			// Clear the old localizations.
			LocaleManager::m_Localizations.clear();

			// Load the lang file as an .ini file and add all its configs to the localizations map.
			config::ConfigFile* config = config::ConfigManager::GetConfigFilePath("locale/" + languageCode);
			if (config) {
				AddConfigsToMap(config, LocaleManager::m_Localizations);
				delete config;	// Delete the config to save ram.
				LocaleManager::m_LanguageCode = languageCode;
			}
		}

		std::string LocaleManager::GetLocalizedString(const std::string& key) {
			auto itr = LocaleManager::m_Localizations.find(key);
			if (itr != LocaleManager::m_Localizations.end()) {
				return itr->second;
			}
			return "";
		}

	} // namespace locale

} // namespace gp1
