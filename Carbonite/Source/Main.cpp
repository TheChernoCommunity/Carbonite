#include "PCH.h"

#include "CSharp/CSharpRuntime.h"
#include "Carbonite.h"
#include "Log.h"
#include "Utils/Core.h"

#include <cstdlib>

#include <filesystem>
#include <stdexcept>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
#if CARBONITE_IS_CONFIG_DIST
	try
	{
#endif
#if true
		if (!CSharp::LoadFXR())
			throw std::runtime_error("Failed to load HostFXR");

		CSharp::Handle handle = nullptr;
		{
			auto cwd = std::filesystem::current_path().string() + "/runtimeconfig.json";
			auto rc  = CSharp::InitializeForRuntimeConfig(cwd.c_str(), nullptr, &handle);
			if (rc || !handle)
				throw std::runtime_error("Failed to initialize HostFXR handle");
		}

		auto loadAssemblyAndGetFunctionPtr = CSharp::GetLoadAssemblyAndGetFunctionPointer(handle);
		if (!loadAssemblyAndGetFunctionPtr)
			throw std::runtime_error("Failed to get delegate");

		auto getFunctionPtr = CSharp::GetGetFunctionPointer(handle);
		if (!getFunctionPtr)
			throw std::runtime_error("Failed to get delegate");

		CSharp::Close(handle);

		CSharp::ComponentEntryPointFn hello = nullptr;
		{
			auto cwd = std::filesystem::current_path().string() + "/Test.dll";
			auto rc  = loadAssemblyAndGetFunctionPtr(cwd.c_str(), CSHARP_STR("DotNetLib.Lib, Test"), CSHARP_STR("Hello"), nullptr, nullptr, reinterpret_cast<void**>(&hello));
			if (rc || !hello)
				throw std::runtime_error("Failed to load assembly and get function");
		}

		struct LibArgs
		{
			const CSharp::CharT* message;

			std::uint32_t number;
		};

		for (std::uint32_t i = 0; i < 3; ++i)
		{
			LibArgs args = { CSHARP_STR("from host!"), i };
			hello(&args, sizeof(args));
		}

		using CustomEntryPointFn  = void (*)(LibArgs args);
		CustomEntryPointFn custom = nullptr;

		{
			auto cwd = std::filesystem::current_path().string() + "/Test.dll";
			auto rc  = loadAssemblyAndGetFunctionPtr(cwd.c_str(), CSHARP_STR("DotNetLib.Lib, Test"), CSHARP_STR("CustomEntryPointUnmanaged"), CSharp::UnmanagedCallersOnlyMethod, nullptr, reinterpret_cast<void**>(&custom));
			if (rc || !custom)
				throw std::runtime_error("Failed to load assembly and get function");
		}

		LibArgs args = { CSHARP_STR("from host!"), ~0U };
		custom(args);

		CSharp::UnloadFXR();
#else
		auto& carbonite = Carbonite::Get(); // Get carbonite instance
		carbonite.init();                   // Initialize carbonite
		carbonite.run();                    // Run carbonite
		carbonite.deinit();                 // Deinitialize carbonite
		Carbonite::Destroy();               // Destroy carbonite instance
#endif
#if CARBONITE_IS_CONFIG_DIST
	}
	catch (const std::exception& e)
	{
		Log::critical(e.what());
		return EXIT_FAILURE;
	}
#endif
	return EXIT_SUCCESS;
}

#if _WIN32
#undef APIENTRY
#include <Windows.h>

int WinMain([[maybe_unused]] _In_ HINSTANCE hInstance, [[maybe_unused]] _In_opt_ HINSTANCE hPrevInstance, [[maybe_unused]] _In_ LPSTR lpCmdLine, [[maybe_unused]] _In_ int nShowCmd)
{
	return main(__argc, __argv);
}
#endif
