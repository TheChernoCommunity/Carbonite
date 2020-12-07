//
//	Created by FancyKillerPanda on 8. Oct. 2020
//	Edited by MarcasRealAccount on 17. Oct. 2020
//

#include <cstring>
#include <ctime>
#include <filesystem>
#include <stdarg.h>
#include <stdio.h>

#include "Engine/Utility/Logger.h"

namespace gp1
{
	std::unordered_set<Severity> Logger::s_DisabledSeverities;
	std::vector<std::string>     Logger::s_Buffer;

	bool Logger::s_LogToFile = true;
#ifdef _DEBUG
	bool Logger::s_LogToConsole = true;
#else
	bool Logger::s_LogToConsole = false;
#endif
	const char* Logger::s_PreviousFile = "logs/log-previous.txt";
	const char* Logger::s_CurrentFile  = "logs/log-current.txt";

	Logger::Logger(const char* name)
	    : m_Name(name) {}

	void Logger::Log(Severity severity, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		Logger::Log(this->m_Name, severity, format, args);
		va_end(args);
	}

	void Logger::LogTrace(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		Logger::Log(this->m_Name, gp1::Severity::Trace, format, args);
		va_end(args);
	}

	void Logger::LogDebug(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		Logger::Log(this->m_Name, gp1::Severity::Debug, format, args);
		va_end(args);
	}

	void Logger::LogWarning(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		Logger::Log(this->m_Name, gp1::Severity::Warning, format, args);
		va_end(args);
	}

	void Logger::LogError(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		Logger::Log(this->m_Name, gp1::Severity::Error, format, args);
		va_end(args);
	}

	void Logger::Init()
	{
		if (std::filesystem::exists(Logger::s_CurrentFile))
		{
			if (std::filesystem::exists(Logger::s_PreviousFile)) std::filesystem::remove(Logger::s_PreviousFile);

			if (rename(Logger::s_CurrentFile, Logger::s_PreviousFile))
				Logger("Logger").Log(Severity::Debug, "Failed to rename log file %s to %s", Logger::s_CurrentFile, Logger::s_PreviousFile);
		}
	}

	void Logger::DeInit()
	{
		Flush();
	}

	void Logger::EnableSeverity(Severity severity)
	{
		Logger::s_DisabledSeverities.erase(severity);
	}

	void Logger::DisableSeverity(Severity severity)
	{
		Logger::s_DisabledSeverities.insert(severity);
	}

	void Logger::Flush()
	{
		if (!Logger::s_LogToFile) return;

		std::filesystem::path filepath { Logger::s_CurrentFile };
		std::filesystem::create_directories(filepath.parent_path());

		FILE* file = fopen(Logger::s_CurrentFile, "a");
		if (file)
		{
			for (auto message : Logger::s_Buffer)
				fwrite(message.c_str(), sizeof(char), message.length(), file);
			fclose(file);
			Logger::s_Buffer.clear();
		}
		else
		{
			Logger::s_LogToFile = false;
		}
	}

	uint32_t Logger::GetSeverityMaxBufferCount(Severity severity)
	{
		switch (severity)
		{
		case Severity::Debug:
			return 50;
		case Severity::Warning:
			return 10;
		case Severity::Error:
			return 0;
		case Severity::Trace:
		default:
			return 100;
		}
	}

	const char* Logger::GetSeverityId(Severity severity)
	{
		switch (severity)
		{
		case Severity::Debug:
			return "Debug";
		case Severity::Warning:
			return "Warning";
		case Severity::Error:
			return "Error";
		case Severity::Trace:
		default:
			return "Trace";
		}
	}

	const char* Logger::GetSeverityConsoleColor(Severity severity)
	{
		switch (severity)
		{
		case Severity::Debug:
			return "\033[0;36m";
		case Severity::Warning:
			return "\033[0;93m";
		case Severity::Error:
			return "\033[0;91m";
		case Severity::Trace:
		default:
			return "\033[0;97m";
		}
	}

	void Logger::Log(const char* name, Severity severity, const char* format, va_list args)
	{
		auto itr = Logger::s_DisabledSeverities.find(severity);
		if (itr != Logger::s_DisabledSeverities.end()) return;

		uint32_t length = vsnprintf(nullptr, 0, format, args) + 1;
		char*    buf    = new char[length];
		vsnprintf(buf, length, format, args);

		std::string message(buf);
		delete[] buf;

		std::vector<std::string> messages;

		uint32_t lastIndex = 0;
		for (uint32_t i = 0; i < message.length(); i++)
		{
			if (message[i] == '\n')
			{
				messages.push_back(message.substr(lastIndex, i - lastIndex));
				lastIndex = i + 1;
			}
			else if (i == message.length() - 1)
			{
				messages.push_back(message.substr(lastIndex));
			}
		}

		for (std::string msg : messages)
		{
			std::string logMsg     = "";
			std::string consoleMsg = "";

			constexpr uint32_t timeBufferSize = 16;
			std::time_t        currentTime    = std::time(nullptr);
			char               timeBuffer[timeBufferSize];

			if (Logger::s_LogToFile) logMsg += "[" + std::string(name) + "]";
			if (Logger::s_LogToConsole) consoleMsg += "[" + std::string(name) + "]";

			if (std::strftime(timeBuffer, timeBufferSize, "[%H:%M:%S]", std::localtime(&currentTime)))
			{
				if (Logger::s_LogToFile) logMsg += timeBuffer;
				if (Logger::s_LogToConsole) consoleMsg += timeBuffer;
			}

			if (Logger::s_LogToFile) logMsg += " " + std::string(Logger::GetSeverityId(severity)) + ": " + msg + "\n";
			if (Logger::s_LogToConsole) consoleMsg += " " + std::string(Logger::GetSeverityConsoleColor(severity)) + std::string(Logger::GetSeverityId(severity)) + "\033[0m: " + msg + "\n";

			if (Logger::s_LogToFile) Logger::s_Buffer.push_back(logMsg);
			if (Logger::s_LogToConsole) printf("%s", consoleMsg.c_str());
		}

		if (Logger::s_LogToFile)
			if (Logger::s_Buffer.size() > Logger::GetSeverityMaxBufferCount(severity)) Flush();
	}

} // namespace gp1
