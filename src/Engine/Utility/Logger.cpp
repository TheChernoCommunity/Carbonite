//
//	Created by FancyKillerPanda on 8. Oct. 2020
//	Edited by MarcasRealAccount on 17. Oct. 2020
//

#include <ctime>
#include <cstring>
#include <stdio.h>
#include <stdarg.h>
#include <filesystem>

#include "Engine/Utility/Logger.h"

namespace gp1 {

	std::unordered_set<Severity> Logger::m_DisabledSeverities;
	std::vector<std::string> Logger::m_Buffer;

	bool Logger::m_LogToFile = true;
	const char* Logger::m_PreviousFile = "logs/log-previous.txt";
	const char* Logger::m_CurrentFile = "logs/log-current.txt";

	Logger::Logger(const char* name)
		: m_Name(name) {}

	void Logger::Log(Severity severity, const char* format, ...) {
		va_list args;
		va_start(args, format);
		Logger::Log(this->m_Name, severity, format, args);
		va_end(args);
	}

	void Logger::LogTrace(const char* format, ...) {
		va_list args;
		va_start(args, format);
		Logger::Log(this->m_Name, gp1::Severity::Trace, format, args);
		va_end(args);
	}

	void Logger::LogDebug(const char* format, ...) {
		va_list args;
		va_start(args, format);
		Logger::Log(this->m_Name, gp1::Severity::Debug, format, args);
		va_end(args);
	}

	void Logger::LogWarning(const char* format, ...) {
		va_list args;
		va_start(args, format);
		Logger::Log(this->m_Name, gp1::Severity::Warning, format, args);
		va_end(args);
	}

	void Logger::LogError(const char* format, ...) {
		va_list args;
		va_start(args, format);
		Logger::Log(this->m_Name, gp1::Severity::Error, format, args);
		va_end(args);
	}

	void Logger::Init() {
		if (std::filesystem::exists(Logger::m_CurrentFile)) {
			if (std::filesystem::exists(Logger::m_PreviousFile)) {
				std::filesystem::remove(Logger::m_PreviousFile);
			}

			if (rename(Logger::m_CurrentFile, Logger::m_PreviousFile))
				Logger("Logger").Log(Severity::Debug, "Failed to rename log file %s to %s", Logger::m_CurrentFile, Logger::m_PreviousFile);
		}
	}

	void Logger::DeInit() {
		Flush();
	}

	void Logger::EnableSeverity(Severity severity) {
		Logger::m_DisabledSeverities.erase(severity);
	}

	void Logger::DisableSeverity(Severity severity) {
		Logger::m_DisabledSeverities.insert(severity);
	}

	void Logger::Flush() {
		if (!Logger::m_LogToFile)
			return;

		std::filesystem::path filepath{ Logger::m_CurrentFile };
		std::filesystem::create_directories(filepath.parent_path());

		FILE* file = fopen(Logger::m_CurrentFile, "a");
		if (file) {
			for (auto message : Logger::m_Buffer) {
				fwrite(message.c_str(), sizeof(char), message.length(), file);
			}
			fclose(file);
			Logger::m_Buffer.clear();
		} else {
			Logger::m_LogToFile = false;
		}
	}

	uint32_t Logger::GetSeverityMaxBufferCount(Severity severity) {
		switch (severity) {
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

	const char* Logger::GetSeverityId(Severity severity) {
		switch (severity) {
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

	const char* Logger::GetSeverityConsoleColor(Severity severity) {
		switch (severity) {
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

	void Logger::Log(const char* name, Severity severity, const char* format, va_list args) {
		auto itr = Logger::m_DisabledSeverities.find(severity);
		if (itr != Logger::m_DisabledSeverities.end())
			return;

		uint32_t length = vsnprintf(nullptr, 0, format, args) + 1;
		char* buf = new char[length];
		vsnprintf(buf, length, format, args);

		std::string message(buf);
		delete[] buf;

		std::vector<std::string> messages;

		uint32_t lastIndex = 0;
		for (uint32_t i = 0; i < message.length(); i++) {
			if (message[i] == '\n') {
				messages.push_back(message.substr(lastIndex, i - lastIndex));
				lastIndex = i + 1;
			} else if (i == message.length() - 1) {
				messages.push_back(message.substr(lastIndex));
			}
		}

		for (std::string msg : messages) {
			std::string logMsg = "";
			std::string consoleMsg = "";

			constexpr uint32_t timeBufferSize = 16;
			std::time_t currentTime = std::time(nullptr);
			char timeBuffer[timeBufferSize];

			if (Logger::m_LogToFile)
				logMsg += "[" + std::string(name) + "]";
			consoleMsg += "[" + std::string(name) + "]";

			if (std::strftime(timeBuffer, timeBufferSize, "[%H:%M:%S]", std::localtime(&currentTime))) {
				if (Logger::m_LogToFile)
					logMsg += timeBuffer;
				consoleMsg += timeBuffer;
			}

			if (Logger::m_LogToFile)
				logMsg += " " + std::string(Logger::GetSeverityId(severity)) + ": " + msg + "\n";
			consoleMsg += " " + std::string(Logger::GetSeverityConsoleColor(severity)) + std::string(Logger::GetSeverityId(severity)) + "\033[0m: " + msg + "\n";

			if (Logger::m_LogToFile)
				Logger::m_Buffer.push_back(logMsg);
			printf("%s", consoleMsg.c_str());
		}

		if (Logger::m_LogToFile) {
			if (Logger::m_Buffer.size() > Logger::GetSeverityMaxBufferCount(severity)) {
				Flush();
			}
		}
	}

}
