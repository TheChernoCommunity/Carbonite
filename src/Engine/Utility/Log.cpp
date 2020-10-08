#include <ctime>
#include <stdio.h>
#include <stdarg.h>

#include "Engine/Utility/Log.h"

#define WHITE "\033[0;97m"
#define BLUE "\033[0;36m"
#define YELLOW "\033[0;93m"
#define RED "\033[0;91m"
#define DEFAULT_COLOUR "\033[0m"

namespace gp1
{

void log(Severity severity, const char* message, ...)
{
	va_list args;
	va_start(args, message);

	constexpr unsigned int timeBufferSize = 16;
	std::time_t currentTime = std::time(nullptr);
	char timeBuffer[timeBufferSize];
	
	if (std::strftime(timeBuffer, timeBufferSize, "[%H:%M:%S]", std::localtime(&currentTime)))
	{
		printf("%s ", timeBuffer);
	}
	
	switch (severity)
	{
	case Severity::Trace:
		printf(WHITE "Trace" DEFAULT_COLOUR ": ");
		break;

	case Severity::Debug:
		printf(BLUE "Debug" DEFAULT_COLOUR ": ");
		break;

	case Severity::Warning:
		printf(YELLOW "Warning" DEFAULT_COLOUR ": ");
		break;

	case Severity::Error:
		printf(RED "Error" DEFAULT_COLOUR ": ");
		break;
	}
	
	vprintf(message, args);
	printf("\n");
	
	va_end(args);
}

}

#undef WHITE
#undef BLUE
#undef YELLOW
#undef RED
#undef DEFAULT_COLOUR
