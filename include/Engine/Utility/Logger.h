//	
//	Created by FancyKillerPanda on 8. Oct. 2020
//	Edited by MarcasRealAccount on 17. Oct. 2020
//	

#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_set>

namespace gp1
{

	enum class Severity {
		Trace,
		Debug,
		Warning,
		Error
	};

	class Logger {
	public:
		Logger(const char* name);

		void Log(Severity severity, const char* format, ...);
		void LogTrace(const char* format, ...);
		void LogDebug(const char* format, ...);
		void LogWarning(const char* format, ...);
		void LogError(const char* format, ...);

	private:
		const char* m_Name;

	public:
		static void Init();
		static void Deinit();

		static void EnableSeverity(Severity severity);
		static void DisableSeverity(Severity severity);

		static void Flush();

	private:
		static uint32_t GetSeverityMaxBufferCount(Severity severity);
		static const char* GetSeverityId(Severity severity);
		static const char* GetSeverityConsoleColor(Severity severity);

		static void Log(const char* name, Severity severity, const char* format, va_list args);

	private:
		static std::unordered_set<Severity> m_DisabledSeverities;

		static std::vector<std::string> m_Buffer;

		static bool m_LogToFile;
		static const char* m_PreviousFile;
		static const char* m_CurrentFile;
	};

}
