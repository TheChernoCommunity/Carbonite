#include "PCH.h"

#include "Utils/Core.h"
#include "Utils/FileIO.h"

#include "Log.h"

#if CARBONITE_IS_SYSTEM_WINDOWS
#include <Windows.h>
#elif CARBONITE_IS_SYSTEM_MACOSX
#include <mach-o/dyld.h>
#elif CARBONITE_IS_SYSTEM_LINUX
#include <unistd.h>
#endif

namespace FileIO
{
	static std::filesystem::path platformGetExecutableDir();

	static std::filesystem::path s_ExecutableDir = platformGetExecutableDir();
	static std::filesystem::path s_GameDir       = std::filesystem::current_path();

	std::filesystem::path getExecutableDir()
	{
		return s_ExecutableDir;
	}

	void setGameDir(std::filesystem::path dir)
	{
		s_GameDir = dir;
	}

	std::filesystem::path getGameDir()
	{
		return s_GameDir;
	}

	std::filesystem::path platformGetExecutableDir()
	{
		std::filesystem::path path;
#if CARBONITE_IS_SYSTEM_WINDOWS
		wchar_t* buffer = new wchar_t[32767]; // Windows can only support upto 32ki long filenames, and it's probably way more than unix would handle.
		DWORD    result = GetModuleFileNameW(nullptr, buffer, 32767);
		if (result > 0)
			path = std::filesystem::path(buffer).parent_path();
		delete[] buffer;
#elif CARBONITE_IS_SYSTEM_MACOSX
		std::uint32_t bufSize = 0;
		int           result  = _NSGetExecutablePath(nullptr, &bufSize);
		char*         buffer  = new char[bufSize + 1];
		result                = _NSGetExecutablePath(buffer, &bufSize);
		if (result == 0)
			path = std::filesystem::path(buffer).parent_path();
		delete[] buffer;
#elif CARBONITE_IS_SYSTEM_LINUX
		std::size_t bufSize = 0;
		stat        stat;
		if (lstat("/proc/self/exe", &stat) >= 0)
			bufSize = stat.st_size;
		char*   buffer = new char[bufSize + 1];
		ssize_t result = readlink("/proc/self/exe", buffer, bufSize);
		if (result > 0)
			path = std::filesystem::path(buffer).parent_path();
		delete[] buffer;
#endif
		return path;
	}
} // namespace FileIO
