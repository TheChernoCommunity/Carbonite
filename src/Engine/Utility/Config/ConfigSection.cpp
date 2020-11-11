//
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#include "Engine/Utility/Config/ConfigSection.h"

#include <sstream>

namespace gp1 {

namespace config {

std::string ToParsableString(const std::string& str) {
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

ConfigSection::ConfigSection(const std::string& key, ConfigSection* parent)
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

void ConfigSection::SetConfig(const std::string& key, const std::string& value) {
    this->m_Configs.insert_or_assign(key, value);
    this->m_Changed = true;
}

const std::string& ConfigSection::GetConfig(const std::string& key, const std::string& def) {
    uint64_t keyPeriod = key.find_first_of('.');
    if (keyPeriod < key.length()) {
        std::string thisKey = key.substr(0, keyPeriod);
        ConfigSection* sec = GetOrCreateSection(thisKey);
        if (sec)
            return sec->GetConfig(key.substr(keyPeriod + 1), def);
    }
    auto itr = this->m_Configs.find(key);
    if (itr != this->m_Configs.end())
        return itr->second;
    this->m_Configs.insert_or_assign(key, def);
    this->m_Changed = true;
    return def;
}

ConfigSection* ConfigSection::GetSection(const std::string& key) const {
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

ConfigSection* ConfigSection::GetOrCreateSection(const std::string& key) {
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

template <>
void ConfigSection::SetConfigTyped(const std::string& key, int8_t value) {
    SetConfig(key, std::to_string(value));
}

template <>
void ConfigSection::SetConfigTyped(const std::string& key, int16_t value) {
    SetConfig(key, std::to_string(value));
}

template <>
void ConfigSection::SetConfigTyped(const std::string& key, int32_t value) {
    SetConfig(key, std::to_string(value));
}

template <>
void ConfigSection::SetConfigTyped(const std::string& key, int64_t value) {
    SetConfig(key, std::to_string(value));
}

template <>
void ConfigSection::SetConfigTyped(const std::string& key, uint8_t value) {
    SetConfig(key, std::to_string(value));
}

template <>
void ConfigSection::SetConfigTyped(const std::string& key, uint16_t value) {
    SetConfig(key, std::to_string(value));
}

template <>
void ConfigSection::SetConfigTyped(const std::string& key, uint32_t value) {
    SetConfig(key, std::to_string(value));
}

template <>
void ConfigSection::SetConfigTyped(const std::string& key, uint64_t value) {
    SetConfig(key, std::to_string(value));
}

template <>
void ConfigSection::SetConfigTyped(const std::string& key, bool value) {
    SetConfig(key, value ? "true" : "false");
}

template <>
int8_t ConfigSection::GetConfigTyped(const std::string& key, int8_t def) {
    int8_t val;
    std::istringstream(GetConfig(key, std::to_string(def))) >> val;
    return val;
}

template <>
int16_t ConfigSection::GetConfigTyped(const std::string& key, int16_t def) {
    int16_t val;
    std::istringstream(GetConfig(key, std::to_string(def))) >> val;
    return val;
}

template <>
int32_t ConfigSection::GetConfigTyped(const std::string& key, int32_t def) {
    int32_t val;
    std::istringstream(GetConfig(key, std::to_string(def))) >> val;
    return val;
}

template <>
int64_t ConfigSection::GetConfigTyped(const std::string& key, int64_t def) {
    int64_t val;
    std::istringstream(GetConfig(key, std::to_string(def))) >> val;
    return val;
}

template <>
uint8_t ConfigSection::GetConfigTyped(const std::string& key, uint8_t def) {
    uint8_t val;
    std::istringstream(GetConfig(key, std::to_string(def))) >> val;
    return val;
}

template <>
uint16_t ConfigSection::GetConfigTyped(const std::string& key, uint16_t def) {
    uint16_t val;
    std::istringstream(GetConfig(key, std::to_string(def))) >> val;
    return val;
}

template <>
uint32_t ConfigSection::GetConfigTyped(const std::string& key, uint32_t def) {
    uint32_t val;
    std::istringstream(GetConfig(key, std::to_string(def))) >> val;
    return val;
}

template <>
uint64_t ConfigSection::GetConfigTyped(const std::string& key, uint64_t def) {
    uint64_t val;
    std::istringstream(GetConfig(key, std::to_string(def))) >> val;
    return val;
}

template <>
bool ConfigSection::GetConfigTyped(const std::string& key, bool def) {
    std::string value = GetConfig(key, def ? "true" : "false");
    return value == "true";
}

const std::string& ConfigSection::GetKey() const {
    return this->m_Key;
}

std::string ConfigSection::GetFullKey() const {
    std::string key = this->m_Key;
    if (this->m_Parent) key = this->m_Parent->GetFullKey() + "." + key;
    return key;
}

bool ConfigSection::HasChanged() const {
    if (m_Changed)
        return true;
    for (auto section : this->m_Sections)
        if (section.second->HasChanged())
            return true;
    return false;
}

void ConfigSection::SetChanges(bool changed) {
    this->m_Changed = changed;
    for (auto section : this->m_Sections)
        section.second->SetChanges(changed);
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
