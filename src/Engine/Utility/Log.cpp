#include <ctime>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdarg.h>
#include <filesystem>

#include "Engine/Utility/Core/Log.h"

#define WHITE "\033[0;97m"
#define BLUE "\033[0;36m"
#define YELLOW "\033[0;93m"
#define RED "\033[0;91m"
#define DEFAULT_COLOUR "\033[0m"

namespace gp1
{

    bool fileLoggingEnabled = false;
    std::string logFilepath = "log.txt";

    // TODO(fkp): This currently opens the file each time we log. We
    // should instead probably save to a buffer first and flush it every
    // so often.
    void log(Severity severity, const char* format, ...)
    {
        va_list args;
        va_start(args, format);

        FILE* file = nullptr;

        if (fileLoggingEnabled)
        {
            std::filesystem::path filepath { logFilepath };
            std::filesystem::create_directories(filepath.parent_path());

            file = fopen(logFilepath.c_str(), "a");

            if (file)
            {
                static bool hasDone = false;

                if (!hasDone)
                {
                    hasDone = true;
                    fprintf(file, "\n\n================================================================\n\n");
                }
            }
            else
            {
                fileLoggingEnabled = false;
                log(Severity::Warning, "Failed to open log file '%s' (error: %s).", logFilepath.c_str(), std::strerror(errno));
            }
        }

        constexpr unsigned int timeBufferSize = 16;
        std::time_t currentTime = std::time(nullptr);
        char timeBuffer[timeBufferSize];

        if (std::strftime(timeBuffer, timeBufferSize, "[%H:%M:%S]", std::localtime(&currentTime)))
        {
            printf("%s ", timeBuffer);

            if (file)
            {
                fprintf(file, "%s ", timeBuffer);
            }
        }

        switch (severity)
        {
            case Severity::Trace:
                printf(WHITE "Trace" DEFAULT_COLOUR ": ");

                if (file)
                {
                    fprintf(file, "Trace: ");
                }
                break;

            case Severity::Debug:
                printf(BLUE "Debug" DEFAULT_COLOUR ": ");
                if (file)
                {
                    fprintf(file, "Debug: ");
                }
                break;

            case Severity::Warning:
                printf(YELLOW "Warning" DEFAULT_COLOUR ": ");
                if (file)
                {
                    fprintf(file, "Warning: ");
                }
                break;

            case Severity::Error:
                printf(RED "Error" DEFAULT_COLOUR ": ");

                if (file)
                {
                    fprintf(file, "Error: ");
                }
                break;
        }

        vprintf(format, args);
        printf("\n");

        if (file)
        {
            vfprintf(file, format, args);
            fprintf(file, "\n");

            fclose(file);
        }

        va_end(args);
    }

}

#undef WHITE
#undef BLUE
#undef YELLOW
#undef RED
#undef DEFAULT_COLOUR
