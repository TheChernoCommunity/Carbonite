#include "Engine/Utility/Log.h"
#include "Engine/Utility/AssetLoader.h"

#include <iostream>

int main( int /*argc*/, char* /*argv*/[] )
{
	gp1::log(gp1::Severity::Trace, "This is a trace message.");
	gp1::log(gp1::Severity::Debug, "Another string: '%s'", "Hello, World!");
	gp1::log(gp1::Severity::Warning, "Oh no!");
	gp1::log(gp1::Severity::Error, "Code: %d.", 1);

	gp1::AssetLoader& assetLoader = gp1::AssetLoader::Get();

	gp1::AssetLoadResult fooResult = assetLoader.LoadAsset("foo.txt");
	if (fooResult.success)
	{
		gp1::log(gp1::Severity::Trace, "Successfully loaded foo.txt! Contents: %s", std::string(fooResult.data).c_str());
	}
	else
	{
		gp1::log(gp1::Severity::Warning, "Failed to load foo.txt");
	}

	gp1::AssetLoadResult fooAgain = assetLoader.LoadAsset("foo.txt");

	return 0;
}

#if defined( _WIN32 )

#include <Windows.h>

int WINAPI WinMain( _In_ HINSTANCE /*instance*/, _In_opt_ HINSTANCE /*prev_instance*/, _In_ LPSTR /*cmd_line*/, _In_ int /*cmd_show*/ )
{
	return main( __argc, __argv );
}

#endif // _WIN32
