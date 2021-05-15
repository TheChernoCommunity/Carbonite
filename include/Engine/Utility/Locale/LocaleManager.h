#pragma once

#include <string>
#include <unordered_map>

namespace gp1
{
	namespace locale
	{
		class LocaleManager
		{
		public:
			// Sets the localization to be used.
			static void SetLocalization(const std::string& languageCode);
			// Gets the current language code used.
			static const std::string& GetLanguageCode();
			// Gets the localized string, from the key.
			static std::string GetLocalizedString(const std::string& key);

		private:
			static std::string                                  s_LanguageCode;  // The current language loaded in.
			static std::unordered_map<std::string, std::string> s_Localizations; // The current localized strings.
		};

	} // namespace locale

} // namespace gp1
