#include "PCH.h"

#include <spdlog/sinks/stdout_color_sinks.h>

#include "Core.h"
#include "Log.h"

namespace
{
	static std::shared_ptr<spdlog::logger> s_Logger = nullptr;
} // namespace

namespace Log
{
	std::shared_ptr<spdlog::logger> getLogger()
	{
		if (s_Logger == nullptr)
		{
			s_Logger = spdlog::stderr_color_mt("Carbonite");
			spdlog::set_pattern("[%T.%f][%^%8l%$][%7t] %v");

#if CARBONITE_IS_CONFIG_DIST
			s_Logger->set_level(spdlog::level::level_enum::err);
#else
			s_Logger->set_level(spdlog::level::level_enum::trace);
#endif // NDEBUG
		}

		return s_Logger;
	}
} // namespace Log
