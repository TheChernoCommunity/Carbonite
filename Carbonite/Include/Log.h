#pragma once

#include <memory>

#include <spdlog/spdlog.h>

namespace Log
{
	std::shared_ptr<spdlog::logger> getClientLogger();

	void init();

	template <typename... Ts>
	void trace(Ts&&... args)
	{
		getClientLogger()->trace(std::forward<Ts>(args)...);
	}

	template <typename... Ts>
	void info(Ts&&... args)
	{
		getClientLogger()->info(std::forward<Ts>(args)...);
	}

	template <typename... Ts>
	void debug(Ts&&... args)
	{
		getClientLogger()->debug(std::forward<Ts>(args)...);
	}

	template <typename... Ts>
	void warn(Ts&&... args)
	{
		getClientLogger()->warn(std::forward<Ts>(args)...);
	}

	template <typename... Ts>
	void error(Ts&&... args)
	{
		getClientLogger()->error(std::forward<Ts>(args)...);
	}

	template <typename... Ts>
	void critical(Ts&&... args)
	{
		getClientLogger()->critical(std::forward<Ts>(args)...);
	}
} // namespace Log