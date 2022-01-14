#include "PCH.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>

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
			std::vector<spdlog::sink_ptr> sinks;
			if constexpr (Core::s_IsConfigDebug)
				sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());
			sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_st>("Logs/Log", 23, 59));
			s_Logger = std::make_shared<spdlog::logger>("Carbonite", sinks.begin(), sinks.end());
			spdlog::set_pattern("[%T.%f][%^%8l%$][%7t] %v");

			if constexpr (Core::s_IsConfigDist)
				s_Logger->set_level(spdlog::level::level_enum::err);
			else
				s_Logger->set_level(spdlog::level::level_enum::trace);
		}

		return s_Logger;
	}
} // namespace Log
