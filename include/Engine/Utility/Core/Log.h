#pragma once

namespace gp1
{

enum class Severity
{
	Trace,
	Debug,
	Warning,
	Error,
};

void log(Severity severity, const char* message, ...);

}
