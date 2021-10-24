#include <spdlog/sinks/stdout_color_sinks.h>

#include "Log.h"

namespace
{

	static std::shared_ptr<spdlog::logger> s_clientLogger;

} // namespace

namespace Log
{

	void init()
	{
		s_clientLogger = spdlog::stderr_color_mt("Carbonite");
		spdlog::set_pattern("[%T.%f][%^%8l%$][%7t] %v");

#if defined(NDEBUG)
		s_clientLogger->set_level(spdlog::level::level_enum::err);
#else
		s_clientLogger->set_level(spdlog::level::level_enum::info);
#endif // NDEBUG
	}

	std::shared_ptr<spdlog::logger> getClientLogger()
	{
		return s_clientLogger;
	}

} // namespace Log