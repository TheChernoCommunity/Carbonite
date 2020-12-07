//
//	Created by FancyKillerPanda on 8. Oct. 2020
//	Edited by MarcasRealAccount on 17. Oct. 2020
//

#pragma once

#include <stdint.h>
#include <string>
#include <unordered_set>
#include <vector>

namespace gp1
{
	enum class Severity
	{
		Trace,
		Debug,
		Warning,
		Error
	};

	class Logger
	{
	public:
		Logger(const char* name);

		// Log a message with the given severity and message.
		void Log(Severity severity, const char* format, ...);
		// Log a trace severity message.
		void LogTrace(const char* format, ...);
		// Log a debug severity message.
		void LogDebug(const char* format, ...);
		// Log a warning severity message.
		void LogWarning(const char* format, ...);
		// Log an error severity message.
		void LogError(const char* format, ...);

	public:
		// Initialize the logger system.
		static void Init();
		// Deinitialize the logger system.
		static void DeInit();

		// Enable the given severity to be logged.
		static void EnableSeverity(Severity severity);
		// Disable the given severity from being logged.
		static void DisableSeverity(Severity severity);

		// Flush the logger system's buffer.
		static void Flush();

	private:
		// Get the max buffer count of the given severity.
		static uint32_t GetSeverityMaxBufferCount(Severity severity);
		// Get the name of the given severity.
		static const char* GetSeverityId(Severity severity);
		// Get the console color of the given severity.
		static const char* GetSeverityConsoleColor(Severity severity);

		// Log to the console and to a file.
		static void Log(const char* name, Severity severity, const char* format, va_list args);

	private:
		const char* m_Name; // The name of this logger.

	private:
		static std::unordered_set<Severity> s_DisabledSeverities; // The disabled severities.

		static std::vector<std::string> s_Buffer; // The buffer to hold messages for writing to a file.

		static bool        s_LogToFile;    // Can log to file.
		static bool        s_LogToConsole; // Can log to console.
		static const char* s_PreviousFile; // The previous log file name.
		static const char* s_CurrentFile;  // The current log file name.
	};

} // namespace gp1
