#include "CSharp/Assembly.h"
#include "CSharp/Runtime.h"
#include "Carbonite/Carbonite.h"
#include "Utils/Core.h"
#include "Utils/FileIO.h"
#include "Utils/Log.h"

#include <cstdlib>

#include <filesystem>
#include <stdexcept>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
#if BUILD_IS_CONFIG_DIST
	try
	{
#endif
#if false
		auto& runtime = CSharp::Runtime::Get();
		runtime.init();
		while (true)
		{
			CSharp::EAssemblyLoadStatus status;

			auto assembly = runtime.loadAssembly(FileIO::getGameDir() / "Mods/Test/ModAPI.dll", status);
			if (!assembly)
			{
				Log::error("Failed to load assembly: {}", status);
				break;
			}

			auto clazz = assembly->getClass("Test", "Test");
			if (!clazz)
			{
				Log::error("Assembly doesn't have the class Test.Test");
				break;
			}

			for (auto& field : clazz->getFields())
				Log::info("Field '{} {} {}'", field.second.getVisibility(), "?", field.second.getName());

			runtime.unloadAssembly(assembly);
			break;
		}
		runtime.deinit();
		CSharp::Runtime::Destroy();
#else
	auto& carbonite = Carbonite::Get(); // Get Carbonite instance
	carbonite.init();                   // Initialize Carbonite
	carbonite.run();                    // Run Carbonite
	carbonite.deinit();                 // Deinitialize Carbonite
	Carbonite::Destroy();               // Destroy Carbonite instance
#endif
#if BUILD_IS_CONFIG_DIST
	}
	catch (const std::exception& e)
	{
		Log::critical(e.what());
		return EXIT_FAILURE;
	}
#endif
	return EXIT_SUCCESS;
}

#if BUILD_IS_SYSTEM_WINDOWS
#undef APIENTRY
#include <Windows.h>

int WinMain([[maybe_unused]] _In_ HINSTANCE hInstance, [[maybe_unused]] _In_opt_ HINSTANCE hPrevInstance, [[maybe_unused]] _In_ LPSTR lpCmdLine, [[maybe_unused]] _In_ int nShowCmd)
{
	return main(__argc, __argv);
}
#endif
