//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Utility/Config/ConfigSection.h"

#include <sstream>

namespace gp1 {

	namespace config {

		std::string ToParsableString(std::string str) {
			std::string output = str;

			bool space = false;
			for (uint64_t i = 0; i < output.length(); i++) {
				if (output[i] == '\\' && output[i + 1] == '\n') {
					i++;
					continue;
				}
				char c = output[i];

				switch (c) {
				case ' ':
					space = true;
					break;
				case '\\':
				case '\'':
				case '\"':
				case ';':
				case '#':
				case '=':
				case ':':
					output.insert(output.begin() + i, '\\');
					i++;
					break;
				case '\0':
					output[i] = '0';
					output.insert(output.begin() + i, '\\');
					i++;
					break;
				case '\a':
					output[i] = 'a';
					output.insert(output.begin() + i, '\\');
					i++;
					break;
				case '\b':
					output[i] = 'b';
					output.insert(output.begin() + i, '\\');
					i++;
					break;
				case '\t':
					output[i] = 't';
					output.insert(output.begin() + i, '\\');
					i++;
					break;
				case '\r':
					output[i] = 'r';
					output.insert(output.begin() + i, '\\');
					i++;
					break;
				case '\n':
					output[i] = 'n';
					output.insert(output.begin() + i, '\\');
					i++;
					break;
				}
			}

			if (space) {
				output = '"' + output + '"';
			}

			return output;
		}

		ConfigSection::ConfigSection(std::string key, ConfigSection* parent)
			: m_Key(key), m_Parent(parent) {}

		ConfigSection::~ConfigSection() {
			if (m_Parent)
				m_Parent->RemoveSection(this);
		}

		void ConfigSection::CleanUp() {
			for (auto section : this->m_Sections)
				delete section.second;
			this->m_Sections.clear();
			this->m_Configs.clear();
		}

		const std::unordered_map<std::string, std::string>& ConfigSection::GetConfigs() const {
			return this->m_Configs;
		}

		const std::unordered_map<std::string, ConfigSection*>& ConfigSection::GetSections() const {
			return this->m_Sections;
		}

		void ConfigSection::SetConfig(std::string key, std::string value) {
			this->m_Configs.insert_or_assign(key, value);
		}

		std::string ConfigSection::GetConfig(std::string key, std::string def) {
			auto itr = this->m_Configs.find(key);
			if (itr != this->m_Configs.end())
				return itr->second;
			this->m_Configs.insert_or_assign(key, def);
			return def;
		}

		ConfigSection* ConfigSection::GetSection(std::string key) const {
			uint64_t keyPeriod = key.find_first_of('.');
			if (keyPeriod < key.length()) {
				std::string thisKey = key.substr(0, keyPeriod);
				ConfigSection* sec = GetSection(thisKey);
				if (sec)
					return sec->GetSection(key.substr(keyPeriod + 1));
				return nullptr;
			} else {
				auto itr = this->m_Sections.find(key);
				if (itr != this->m_Sections.end())
					return itr->second;
				return nullptr;
			}
		}

		ConfigSection* ConfigSection::GetOrCreateSection(std::string key) {
			ConfigSection* section = GetSection(key);
			if (section != nullptr)
				return section;
			uint64_t keyPeriod = key.find_first_of('.');
			if (keyPeriod < key.length()) {
				std::string thisKey = key.substr(0, keyPeriod);
				ConfigSection* sec = GetOrCreateSection(thisKey);
				if (sec)
					return sec->GetOrCreateSection(key.substr(keyPeriod + 1));
				return nullptr;
			} else {
				section = new ConfigSection(key, this);
				this->m_Sections.insert_or_assign(key, section);
				return section;
			}
		}

		void ConfigSection::SetConfigInt(std::string key, int64_t value) {
			SetConfig(key, std::to_string(value));
		}

		void ConfigSection::SetConfigUInt(std::string key, uint64_t value) {
			SetConfig(key, std::to_string(value));
		}

		void ConfigSection::SetConfigBool(std::string key, bool value) {
			SetConfig(key, value ? "true" : "false");
		}

		int64_t ConfigSection::GetConfigInt(std::string key, int64_t def) {
			int64_t val;
			std::istringstream(GetConfig(key, std::to_string(def))) >> val;
			return val;
		}

		uint64_t ConfigSection::GetConfigUInt(std::string key, uint64_t def) {
			uint64_t val;
			std::istringstream(GetConfig(key, std::to_string(def))) >> val;
			return val;
		}

		bool ConfigSection::GetConfigBool(std::string key, bool def) {
			std::string value = GetConfig(key, def ? "true" : "false");
			return value == "true";
		}

		std::string ConfigSection::GetKey() const {
			return this->m_Key;
		}

		std::string ConfigSection::GetFullKey() const {
			std::string key = this->m_Key;
			if (this->m_Parent) key = this->m_Parent->GetFullKey() + "." + key;
			return key;
		}

		std::string ConfigSection::Save(bool first) {
			bool firstSection = true;
			return Save(firstSection, first);
		}

		std::string ConfigSection::Save(bool& firstSection, bool first) {
			std::string output;
			if (this->m_Configs.size() > 0) {
				if (!first) {
					std::string fullKey = GetFullKey();
					fullKey = fullKey.substr(fullKey.find_first_of('.') + 1);
					if (!firstSection)
						output += "\n";
					output += "[" + ToParsableString(fullKey) + "]\n";
					firstSection = false;
				}

				auto configItr = this->m_Configs.begin();
				while (configItr != this->m_Configs.end()) {
					output += ToParsableString(configItr->first) + " = " + ToParsableString(configItr->second) + "\n";
					configItr++;
				}
			}

			if (this->m_Sections.size() > 0) {
				auto sectionItr = this->m_Sections.begin();
				while (sectionItr != this->m_Sections.end()) {
					output += sectionItr->second->Save(firstSection, false);
					sectionItr++;
				}
			}
			return output;
		}

		void ConfigSection::RemoveSection(ConfigSection* section) {
			auto itr = this->m_Sections.find(section->GetKey());
			if (itr != this->m_Sections.end())
				this->m_Sections.erase(itr);
		}

	} // namespace configuration

} // namespace gp1
