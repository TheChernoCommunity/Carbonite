#pragma once

#include "Flags.h"

#define BUILD_CONFIG_UNKNOWN 0
#define BUILD_CONFIG_DEBUG   1
#define BUILD_CONFIG_RELEASE 2
#define BUILD_CONFIG_DIST    3

#define BUILD_SYSTEM_UNKNOWN 0
#define BUILD_SYSTEM_WINDOWS 1
#define BUILD_SYSTEM_MACOSX  2
#define BUILD_SYSTEM_LINUX   3

#define BUILD_TOOLSET_UNKNOWN 0
#define BUILD_TOOLSET_MSVC    1
#define BUILD_TOOLSET_CLANG   2
#define BUILD_TOOLSET_GCC     3

#define BUILD_PLATFORM_UNKNOWN 0
#define BUILD_PLATFORM_AMD64   1

#define BUILD_IS_CONFIG_DEBUG (BUILD_CONFIG == BUILD_CONFIG_DEBUG)
#define BUILD_IS_CONFIG_DIST  ((BUILD_CONFIG == BUILD_CONFIG_RELEASE) || (BUILD_CONFIG == BUILD_CONFIG_DIST))

#define BUILD_IS_SYSTEM_WINDOWS (BUILD_SYSTEM == BUILD_SYSTEM_WINDOWS)
#define BUILD_IS_SYSTEM_MACOSX  (BUILD_SYSTEM == BUILD_SYSTEM_MACOSX)
#define BUILD_IS_SYSTEM_LINUX   (BUILD_SYSTEM == BUILD_SYSTEM_LINUX)
#define BUILD_IS_SYSTEM_UNIX    (BUILD_IS_SYSTEM_MACOSX || BUILD_IS_SYSTEM_LINUX)

#define BUILD_IS_TOOLSET_MSVC  (BUILD_TOOLSET == BUILD_TOOLSET_MSVC)
#define BUILD_IS_TOOLSET_CLANG (BUILD_TOOLSET == BUILD_TOOLSET_CLANG)
#define BUILD_IS_TOOLSET_GCC   (BUILD_TOOLSET == BUILD_TOOLSET_GCC)

#define BUILD_IS_PLATFORM_AMD64 (BUILD_PLATFORM == BUILD_PLATFORM_AMD64)

namespace Core
{
	using BuildConfigFlags   = Flags<std::uint16_t>;
	using BuildSystemFlags   = Flags<std::uint16_t>;
	using BuildToolsetFlags  = Flags<std::uint16_t>;
	using BuildPlatformFlags = Flags<std::uint16_t>;

	std::ostream& printBuildConfigFlags(std::ostream& stream, const BuildConfigFlags& flags);
	std::ostream& printBuildSystemFlags(std::ostream& stream, const BuildSystemFlags& flags);
	std::ostream& printBuildToolsetFlags(std::ostream& stream, const BuildToolsetFlags& flags);
	std::ostream& printBuildPlatformFlags(std::ostream& stream, const BuildPlatformFlags& flags);

	namespace BuildConfigFlag
	{
		static constexpr BuildConfigFlags Unknown = 0;
		static constexpr BuildConfigFlags Debug   = 1;
		static constexpr BuildConfigFlags Dist    = 2;
	} // namespace BuildConfigFlag

	namespace BuildSystemFlag
	{
		static constexpr BuildSystemFlags Unknown = 0;
		static constexpr BuildSystemFlags Windows = 1;
		static constexpr BuildSystemFlags Macosx  = 2;
		static constexpr BuildSystemFlags Linux   = 4;
		static constexpr BuildSystemFlags Unix    = 8;
	} // namespace BuildSystemFlag

	namespace BuildToolsetFlag
	{
		static constexpr BuildToolsetFlags Unknown = 0;
		static constexpr BuildToolsetFlags MSVC    = 1;
		static constexpr BuildToolsetFlags Clang   = 2;
		static constexpr BuildToolsetFlags GCC     = 4;
	} // namespace BuildToolsetFlag

	namespace BuildPlatformFlag
	{
		static constexpr BuildPlatformFlags Unknown = 0;
		static constexpr BuildPlatformFlags X86     = 1;
		static constexpr BuildPlatformFlags AMD64   = 2;
	} // namespace BuildPlatformFlag

#if BUILD_IS_CONFIG_DEBUG
	static constexpr BuildConfigFlags s_Config        = BuildConfigFlag::Debug;
	static constexpr bool             s_IsConfigDebug = true;
	static constexpr bool             s_IsConfigDist  = false;
#elif BUILD_IS_CONFIG_RELEASE
	static constexpr BuildConfigFlags   s_Config          = BuildConfigFlag::Debug | BuildConfigFlags::Dist;
	static constexpr bool               s_IsConfigDebug   = true;
	static constexpr bool               s_IsConfigDist    = true;
#elif BUILD_IS_CONFIG_DIST
	static constexpr BuildConfigFlags  s_Config          = BuildConfigFlag::Dist;
	static constexpr bool              s_IsConfigDebug   = false;
	static constexpr bool              s_IsConfigDist    = true;
#else
	static constexpr BuildConfigFlags  s_Config          = BuildConfigFlag::Unknown;
	static constexpr bool              s_IsConfigDebug   = false;
	static constexpr bool              s_IsConfigDist    = false;
#endif

#if BUILD_IS_SYSTEM_WINDOWS
	static constexpr BuildSystemFlags s_System          = BuildSystemFlag::Windows;
	static constexpr bool             s_IsSystemWindows = true;
	static constexpr bool             s_IsSystemMacosx  = false;
	static constexpr bool             s_IsSystemLinux   = false;
	static constexpr bool             s_IsSystemUnix    = false;
#elif BUILD_IS_SYSTEM_MACOSX
	static constexpr BuildSystemFlags   s_System          = BuildSystemFlag::Macosx | BuildSystemFlag::Unix;
	static constexpr bool               s_IsSystemWindows = false;
	static constexpr bool               s_IsSystemMacosx  = true;
	static constexpr bool               s_IsSystemLinux   = false;
	static constexpr bool               s_IsSystemUnix    = true;
#elif BUILD_IS_SYSTEM_LINUX
	static constexpr BuildSystemFlags  s_System          = BuildSystemFlag::Linux | BuildSystemFlag::Unix;
	static constexpr bool              s_IsSystemWindows = false;
	static constexpr bool              s_IsSystemMacosx  = false;
	static constexpr bool              s_IsSystemLinux   = true;
	static constexpr bool              s_IsSystemUnix    = true;
#else
	static constexpr BuildSystemFlags  s_System          = BuildSystemFlag::Unknown;
	static constexpr bool              s_IsSystemWindows = false;
	static constexpr bool              s_IsSystemMacosx  = false;
	static constexpr bool              s_IsSystemLinux   = false;
	static constexpr bool              s_IsSystemUnix    = false;
#endif

#if BUILD_IS_TOOLSET_MSVC
	static constexpr BuildToolsetFlags s_Toolset        = BuildToolsetFlag::MSVC;
	static constexpr bool              s_IsToolsetMSVC  = true;
	static constexpr bool              s_IsToolsetClang = false;
	static constexpr bool              s_IsToolsetGCC   = false;
#elif BUILD_IS_TOOLSET_CLANG
	static constexpr BuildToolsetFlags  s_Toolset         = BuildToolsetFlag::Clang;
	static constexpr bool               s_IsToolsetMSVC   = false;
	static constexpr bool               s_IsToolsetClang  = true;
	static constexpr bool               s_IsToolsetGCC    = false;
#elif BUILD_IS_TOOLSET_GCC
	static constexpr BuildToolsetFlags s_Toolset         = BuildToolsetFlag::GCC;
	static constexpr bool              s_IsToolsetMSVC   = false;
	static constexpr bool              s_IsToolsetClang  = false;
	static constexpr bool              s_IsToolsetGCC    = true;
#else
	static constexpr BuildToolsetFlags s_Toolset         = BuildToolsetFlag::Unknown;
	static constexpr bool              s_IsToolsetMSVC   = false;
	static constexpr bool              s_IsToolsetClang  = false;
	static constexpr bool              s_IsToolsetGCC    = false;
#endif

#if BUILD_IS_PLATFORM_AMD64
	static constexpr BuildPlatformFlags s_Platform        = BuildPlatformFlag::AMD64;
	static constexpr bool               s_IsPlatformX86   = false;
	static constexpr bool               s_IsPlatformAMD64 = true;
#else
	static constexpr BuildPlatformFlags s_Platform        = BuildPlatformFlag::Unknown;
	static constexpr bool               s_IsPlatformX86   = false;
	static constexpr bool               s_IsPlatformAMD64 = false;
#endif
} // namespace Core
