#pragma once

#include <cstdint>

#include <filesystem>
#include <vector>

namespace FileIO
{
	std::filesystem::path getExecutableDir();
	void                  setGameDir(const std::filesystem::path& dir);
	std::filesystem::path getGameDir();

	bool          readGameFile(const std::filesystem::path& gameFile, std::vector<std::uint8_t>& fileContent);
	std::uint64_t gameFileLastWriteTime(const std::filesystem::path& gameFile);
} // namespace FileIO
