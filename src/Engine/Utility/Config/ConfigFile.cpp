//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	Edited by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Utility/Config/ConfigFile.h"
#include "Engine/Utility/Config/ConfigManager.h"

#include <stdint.h>
#include <filesystem>

namespace gp1 {

	namespace config {

		std::string ParsableToString(const std::string& str) {
			uint64_t start = str.find_first_not_of(' ');
			uint64_t end = str.find_last_not_of(' ');
			std::string output = str.substr(start, end + 1 - start);

			start = output.find_first_not_of('"');
			end = output.find_last_not_of('"');
			output = output.substr(start, end + 1 - start);

			for (uint64_t i = 0; i < output.length(); i++) {
				if (output[i] == '\\') {
					char c = output[i + 1];
					switch (c) {
					case '\\':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, "\\");
						break;
					case '\'':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, "\'");
						break;
					case '\"':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, "\"");
						break;
					case '0':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, "\0");
						break;
					case 'a':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, "\a");
						break;
					case 'b':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, "b");
						break;
					case 't':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, "\t");
						break;
					case 'r':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, "\r");
						break;
					case 'n':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, "\n");
						break;
					case ';':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, ";");
						break;
					case '#':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, "#");
						break;
					case '=':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, "=");
						break;
					case ':':
						output = output.substr(0, i) + output.substr(i + 2);
						output.insert(i, ":");
						break;
					case 'x':
						uint32_t unicodeCharacter = '\0' << 16 | output[i + 2] << 12 | output[i + 3] << 8 | output[i + 4] << 4 | output[i + 5];
						output = output.substr(0, i) + output.substr(i + 6);
						output.insert(i, reinterpret_cast<char*>(&unicodeCharacter));
						break;
					}
				}
			}

			return output;
		}

		ConfigFile::ConfigFile(const std::string& id)
			: ConfigSection(id) {}

		ConfigFile::~ConfigFile() {
			SaveConfig();
			ConfigManager::RemoveConfigFile(this);
		}

		void ConfigFile::ReadConfig() {
			FILE* file = fopen((this->GetKey() + ".ini").c_str(), "r");
			if (file) {
				fseek(file, 0, SEEK_END);
				uint64_t length = (uint64_t)ftell(file);
				if (length == 0) {
					fclose(file);
					return;
				}
				char* buf = new char[length];
				fseek(file, 0, SEEK_SET);
				length = fread(buf, sizeof(char), length, file);
				buf[length] = '\0';
				fclose(file);

				ConfigSection* currentSection = this;
				uint64_t start;
				for (uint64_t i = 0; i < length; i++) {
					char c = buf[i];
					switch (c) {
					case ';':
						i++;
						while (i < length && buf[i] != '\n') i++;
						break;
					case '[':
						i++;
						start = i;
						while (i < length && buf[i] != ']') i++;
						currentSection = GetOrCreateSection(ParsableToString(std::string(buf + start, i - start)));
						while (i < length && buf[i] != '\n') i++;
						break;
					case '\n':
						break;
					default:
						start = i;
						bool backslash = false;
						while (i < length) {
							if (buf[i] == '\\')
								backslash = true;
							i++;
							if (buf[i] == '=' && !backslash)
								break;
							backslash = false;
						}
						std::string key = ParsableToString(std::string(buf + start, i - start));
						i++;
						start = i;
						backslash = false;
						while (i < length) {
							if (buf[i] == '\\')
								backslash = true;
							i++;
							if (buf[i] == '\n' && !backslash)
								break;
							backslash = false;
						}
						std::string value = ParsableToString(std::string(buf + start, i - start));
						currentSection->m_Configs.insert({ key, value });
					}
				}

				delete[] buf;
			}
		}

		void ConfigFile::SaveConfig() {
			std::filesystem::path filepath{ this->GetKey() + ".ini" };
			std::filesystem::create_directories(filepath.parent_path());

			FILE* file = fopen((this->GetKey() + ".ini").c_str(), "w");
			if (file) {
				std::string fileStr = Save();
				fwrite(fileStr.c_str(), sizeof(char), fileStr.length(), file);
				fclose(file);
			}
		}

	} // namespace config

} // namespace gp1
