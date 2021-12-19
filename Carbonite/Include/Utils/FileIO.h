#pragma once

#include <filesystem>

namespace FileIO {
	std::filesystem::path getExecutableDir();
	void setGameDir(std::filesystem::path dir);
	std::filesystem::path getGameDir();
}
