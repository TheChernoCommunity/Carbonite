#pragma once

#include "Utils/Core.h"

#include <cstdint>

namespace CSharp
{
#if CARBONITE_IS_SYSTEM_WINDOWS
#ifdef _WCHAR_T_DEFINED
#define CSHARP_STR(str) L##str
	using CharT = wchar_t;
#else
#define CSHARP_STR(str) L##str
	using CharT = unsigned short;
#endif
#else
#define CSHARP_STR(str) str
	using CharT = char;
#endif
	
	using StringT = std::basic_string<CharT>;

	enum class EDelegateType : std::int32_t
	{
		HDTComActivation,
		HDTLoadInMemoryAssembly,
		HDTWinRTActivation,
		HDTComRegister,
		HDTComUnregister,
		HDTLoadAssemblyAndGetFunctionPointer,
		HDTGetFunctionPointer
	};

	using ErrorWriterFn    = void (*)(const CharT* message);
	using SetErrorWriterFn = ErrorWriterFn (*)(ErrorWriterFn errorWriter);

	using Handle = void*;

	struct InitializeParameters
	{
	public:
		std::size_t  m_Size;
		const CharT* m_HostPath;
		const CharT* m_DotNetRoot;
	};

	using InitializeForCommandLineFn   = std::int32_t (*)(int argc, const CharT** argv, const InitializeParameters* parameters, Handle* hostContextHandle);
	using InitializeForRuntimeConfigFn = std::int32_t (*)(const CharT* runtimeConfigPath, const InitializeParameters* parameters, Handle* hostContextHandle);

	using GetRuntimePropertyValueFn = std::int32_t (*)(Handle hostContextHandle, const CharT* name, const CharT** value);
	using SetRuntimePropertyValueFn = std::int32_t (*)(Handle hostContextHandle, const CharT* name, const CharT* value);
	using GetRuntimePropertiesFn    = std::int32_t (*)(Handle hostContextHandle, std::size_t& count, const CharT** keys, const CharT** values);

	using GetRuntimeDelegateFn = std::int32_t (*)(Handle hostContextHandle, EDelegateType type, void** delegate);

	using CloseFn = std::int32_t (*)(Handle hostContextHandle);

	using LoadAssemblyAndGetFunctionPointerFn = int (*)(const CharT* assemblyPath, const CharT* typeName, const CharT* methodName, const CharT* delegateTypeName, void* reserved, void** delegate);
	using GetFunctionPointerFn                = int (*)(const CharT* typeName, const CharT* methodName, const CharT* delegateTypeName, void* load_context, void* reserved, void** delegate);
	using ComponentEntryPointFn               = int (*)(void* arg, std::int32_t argSizeInBytes);

	static const CharT* UnmanagedCallersOnlyMethod = reinterpret_cast<const CharT*>(~0ULL);

	bool LoadFXR();
	void UnloadFXR();

	std::int32_t InitializeForCommandLine(int argc, const CharT** argv, const InitializeParameters* parameters, Handle* hostContextHandle);
	std::int32_t InitializeForRuntimeConfig(const CharT* runtimeConfigPath, const InitializeParameters* parameters, Handle* hostContextHandle);

	std::int32_t GetRuntimePropertyValue(Handle hostContextHandle, const CharT* name, const CharT** value);
	std::int32_t SetRuntimePropertyValue(Handle hostContextHandle, const CharT* name, const CharT* value);
	std::int32_t GetRuntimeProperties(Handle hostContextHandle, std::size_t& count, const CharT** keys, const CharT** values);

	std::int32_t GetRuntimeDelegate(Handle hostContextHandle, EDelegateType type, void** delegate);

	LoadAssemblyAndGetFunctionPointerFn GetLoadAssemblyAndGetFunctionPointer(Handle hostContextHandle);
	GetFunctionPointerFn                GetGetFunctionPointer(Handle hostContextHandle);

	std::int32_t Close(Handle hostContextHandle);
} // namespace CSharp
