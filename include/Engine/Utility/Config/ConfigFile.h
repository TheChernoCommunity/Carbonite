//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	Edited by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once

#include "Engine/Utility/Config/ConfigSection.h"

#include <string>
#include <unordered_map>

namespace gp1 {

	namespace config {

		class ConfigFile : public ConfigSection {
		public:
			ConfigFile(const std::string& id);
			~ConfigFile();

			// Reads and parses the config file.
			void ReadConfig();
			// Writes to the config file.
			void SaveConfig();
		};

	} // namespace config

} // namespace gp1
