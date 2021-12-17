#include "PCH.h"

#include "CSharp/CSharpRuntime.h"

#include <nethost.h>

#if CARBONITE_IS_SYSTEM_WINDOWS
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

namespace CSharp
{
	void* s_Library = nullptr;

	InitializeForCommandLineFn   s_InitializeForCommandLine   = nullptr;
	InitializeForRuntimeConfigFn s_InitializeForRuntimeConfig = nullptr;

	GetRuntimePropertyValueFn s_GetRuntimePropertyValue = nullptr;
	SetRuntimePropertyValueFn s_SetRuntimePropertyValue = nullptr;
	GetRuntimePropertiesFn    s_GetRuntimeProperties    = nullptr;

	GetRuntimeDelegateFn s_GetRuntimeDelegate = nullptr;

	CloseFn s_Close = nullptr;

	static void* getSymbolAddress(const char* symbol)
	{
#if CARBONITE_IS_SYSTEM_WINDOWS
		return GetProcAddress(static_cast<HINSTANCE>(s_Library), symbol);
#else
		return dlsym(s_Library, symbol);
#endif
	}

	bool LoadFXR()
	{
		std::string hostfxrPath;
		{
			char* buffer;
			std::size_t bufSize;
#if CARBONITE_IS_SYSTEM_WINDOWS
			buffer = new char[32767];
			bufSize = 32767;
#else
			buffer = new char[2048];
			bufSize = 2048;
#endif
			int result = get_hostfxr_path(buffer, &bufSize, nullptr);
			if (!result)
				hostfxrPath = buffer;
			delete[] buffer;
			if (result)
				return false;
		}
		
#if CARBONITE_IS_SYSTEM_WINDOWS
		s_Library = static_cast<void*>(LoadLibraryA(hostfxrPath.c_str()));
#else
		s_Library = dlopen(hostfxrPath.c_str(), RTLD_NOW);
#endif
		if (!s_Library)
			return false;

		s_InitializeForCommandLine   = reinterpret_cast<InitializeForCommandLineFn>(getSymbolAddress("hostfxr_initialize_for_dotnet_command_line"));
		s_InitializeForRuntimeConfig = reinterpret_cast<InitializeForRuntimeConfigFn>(getSymbolAddress("hostfxr_initialize_for_runtime_config"));

		s_GetRuntimePropertyValue = reinterpret_cast<GetRuntimePropertyValueFn>(getSymbolAddress("hostfxr_get_runtime_property_value"));
		s_SetRuntimePropertyValue = reinterpret_cast<SetRuntimePropertyValueFn>(getSymbolAddress("hostfxr_set_runtime_property_value"));
		s_GetRuntimeProperties    = reinterpret_cast<GetRuntimePropertiesFn>(getSymbolAddress("hostfxr_get_runtime_properties"));

		s_GetRuntimeDelegate = reinterpret_cast<GetRuntimeDelegateFn>(getSymbolAddress("hostfxr_get_runtime_delegate"));

		s_Close = reinterpret_cast<CloseFn>(getSymbolAddress("hostfxr_close"));
		return true;
	}

	void UnloadFXR()
	{
		if (s_Library)
		{
#if CARBONITE_IS_SYSTEM_WINDOWS
			FreeLibrary(static_cast<HINSTANCE>(s_Library));
#else
			dlclose(s_Library);
#endif
		}
	}

	std::int32_t InitializeForCommandLine(int argc, const CharT** argv, const InitializeParameters* parameters, Handle* hostContextHandle)
	{
		return s_InitializeForCommandLine(argc, argv, parameters, hostContextHandle);
	}

	std::int32_t InitializeForRuntimeConfig(const CharT* runtimeConfigPath, const InitializeParameters* parameters, Handle* hostContextHandle)
	{
		return s_InitializeForRuntimeConfig(runtimeConfigPath, parameters, hostContextHandle);
	}

	std::int32_t GetRuntimePropertyValue(Handle hostContextHandle, const CharT* name, const CharT** value)
	{
		return s_GetRuntimePropertyValue(hostContextHandle, name, value);
	}

	std::int32_t SetRuntimePropertyValue(Handle hostContextHandle, const CharT* name, const CharT* value)
	{
		return s_SetRuntimePropertyValue(hostContextHandle, name, value);
	}

	std::int32_t GetRuntimeProperties(Handle hostContextHandle, std::size_t& count, const CharT** keys, const CharT** values)
	{
		return s_GetRuntimeProperties(hostContextHandle, count, keys, values);
	}

	std::int32_t GetRuntimeDelegate(Handle hostContextHandle, EDelegateType type, void** delegate)
	{
		return s_GetRuntimeDelegate(hostContextHandle, type, delegate);
	}

	LoadAssemblyAndGetFunctionPointerFn GetLoadAssemblyAndGetFunctionPointer(Handle hostContextHandle)
	{
		void* loadAssemblyAndGetFunctionPtr = nullptr;

		auto rc = CSharp::GetRuntimeDelegate(hostContextHandle, CSharp::EDelegateType::HDTLoadAssemblyAndGetFunctionPointer, &loadAssemblyAndGetFunctionPtr);
		if (rc || !loadAssemblyAndGetFunctionPtr)
			return nullptr;

		return reinterpret_cast<LoadAssemblyAndGetFunctionPointerFn>(loadAssemblyAndGetFunctionPtr);
	}

	GetFunctionPointerFn GetGetFunctionPointer(Handle hostContextHandle)
	{
		void* getFunctionPointer = nullptr;

		auto rc = CSharp::GetRuntimeDelegate(hostContextHandle, CSharp::EDelegateType::HDTGetFunctionPointer, &getFunctionPointer);
		if (rc || !getFunctionPointer)
			return nullptr;

		return reinterpret_cast<GetFunctionPointerFn>(getFunctionPointer);
	}

	std::int32_t Close(Handle hostContextHandle)
	{
		return s_Close(hostContextHandle);
	}
} // namespace CSharp
