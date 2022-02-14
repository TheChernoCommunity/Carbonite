#pragma once

#include <memory>

#include <spdlog/spdlog.h>

namespace Log
{
	std::shared_ptr<spdlog::logger> getLogger();

	template <typename... Ts>
	void trace(Ts&&... args)
	{
		getLogger()->trace(std::forward<Ts>(args)...);
	}

	template <typename... Ts>
	void info(Ts&&... args)
	{
		getLogger()->info(std::forward<Ts>(args)...);
	}

	template <typename... Ts>
	void debug(Ts&&... args)
	{
		getLogger()->debug(std::forward<Ts>(args)...);
	}

	template <typename... Ts>
	void warn(Ts&&... args)
	{
		getLogger()->warn(std::forward<Ts>(args)...);
	}

	template <typename... Ts>
	void error(Ts&&... args)
	{
		getLogger()->error(std::forward<Ts>(args)...);
	}

	template <typename... Ts>
	void critical(Ts&&... args)
	{
		getLogger()->critical(std::forward<Ts>(args)...);
	}
} // namespace Log