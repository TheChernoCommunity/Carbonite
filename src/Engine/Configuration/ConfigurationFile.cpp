//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#include "Engine/Configuration/ConfigurationFile.h"
#include "Engine/Configuration/ConfigurationManager.h"

#include <stdint.h>
#include <filesystem>

namespace gp1 {

	namespace configuration {

		ConfigurationFile::ConfigurationFile(std::string id, std::string filePath)
			: m_id(id), m_filePath(filePath) {}

		ConfigurationFile::~ConfigurationFile() {
			SaveConfiguration();
			ConfigurationManager::RemoveConfigurationFileImpl(this);
		}

		void ConfigurationFile::ReadConfiguration() {
			FILE* file = fopen(this->m_filePath.c_str(), "r");
			if (file) {
				fseek(file, 0, SEEK_END);
				uint32_t length = (uint32_t)ftell(file);
				char* buf = new char[length];
				fseek(file, 0, SEEK_SET);
				fread(buf, sizeof(char), length, file);

				std::string currentLine = "";
				for (uint32_t i = 0; i < length; i++) {
					char c = buf[i];
					if (c == '\n') {
						size_t separatorIndex = currentLine.find_first_of('=');
						std::string configId = currentLine.substr(0, separatorIndex);
						std::string configValue = currentLine.substr(separatorIndex + 1);
						SetConfig(configId, configValue);
						currentLine = "";
					} else {
						currentLine += c;
					}
				}

				delete[] buf;
				fclose(file);
			}
		}

		void ConfigurationFile::SaveConfiguration() {
			std::filesystem::path filepath{ this->m_filePath };
			std::filesystem::create_directories(filepath.parent_path());

			FILE* file = fopen(this->m_filePath.c_str(), "w");
			if (file) {
				for (auto config : this->m_configs) {
					fwrite(config.first.c_str(), sizeof(char), config.first.size(), file);
					fwrite("=", sizeof(char), 1, file);
					fwrite(config.second.c_str(), sizeof(char), config.second.size(), file);
					fwrite("\n", sizeof(char), 1, file);
				}
				fclose(file);
			}
		}

		void ConfigurationFile::SetConfig(std::string configId, std::string configValue) {
			this->m_configs.insert_or_assign(configId, configValue);
		}

		void ConfigurationFile::RemoveConfig(std::string configId) {
			auto itr = this->m_configs.find(configId);
			if (itr != this->m_configs.end())
				this->m_configs.erase(itr);
		}

		const std::string* ConfigurationFile::GetConfig(std::string configId) {
			auto itr = this->m_configs.find(configId);
			if (itr != this->m_configs.end())
				return &itr->second;
			return nullptr;
		}

		const std::string& ConfigurationFile::GetId() const {
			return this->m_id;
		}

	} // namespace configuration

} // namespace gp1
