#include "Engine/Utility/Core/Log.h"

#include <iostream>

int main( int /*argc*/, char* /*argv*/[] )
{
	gp1::log(gp1::Severity::Trace, "This is a trace message.");
	gp1::log(gp1::Severity::Debug, "Another string: '%s'", "Hello, World!");
	gp1::log(gp1::Severity::Warning, "Oh no!");
	gp1::log(gp1::Severity::Error, "Code: %d.", 1);

	return 0;
}

#if defined( _WIN32 )

#include <Windows.h>

int WINAPI WinMain( _In_ HINSTANCE /*instance*/, _In_opt_ HINSTANCE /*prev_instance*/, _In_ LPSTR /*cmd_line*/, _In_ int /*cmd_show*/ )
{
	return main( __argc, __argv );
}

#endif // _WIN32
