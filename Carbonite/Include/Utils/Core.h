#pragma once

#include "Flags.h"

#define CARBONITE_CONFIG_UNKNOWN 0
#define CARBONITE_CONFIG_DEBUG   1
#define CARBONITE_CONFIG_RELEASE 2
#define CARBONITE_CONFIG_DIST    3

#define CARBONITE_SYSTEM_UNKNOWN 0
#define CARBONITE_SYSTEM_WINDOWS 1
#define CARBONITE_SYSTEM_MACOSX  2
#define CARBONITE_SYSTEM_LINUX   3

#define CARBONITE_TOOLSET_UNKNOWN 0
#define CARBONITE_TOOLSET_MSVC    1
#define CARBONITE_TOOLSET_CLANG   2
#define CARBONITE_TOOLSET_GCC     3

#define CARBONITE_PLATFORM_UNKNOWN 0
#define CARBONITE_PLATFORM_AMD64   1

#define CARBONITE_IS_CONFIG_DEBUG (CARBONITE_CONFIG == CARBONITE_CONFIG_DEBUG)
#define CARBONITE_IS_CONFIG_DIST  ((CARBONITE_CONFIG == CARBONITE_CONFIG_RELEASE) || (CARBONITE_CONFIG == CARBONITE_CONFIG_DIST))

#define CARBONITE_IS_SYSTEM_WINDOWS (CARBONITE_SYSTEM == CARBONITE_SYSTEM_WINDOWS)
#define CARBONITE_IS_SYSTEM_MACOSX  (CARBONITE_SYSTEM == CARBONITE_SYSTEM_MACOSX)
#define CARBONITE_IS_SYSTEM_LINUX   (CARBONITE_SYSTEM == CARBONITE_SYSTEM_LINUX)

#define CARBONITE_IS_TOOLSET_MSVC  (CARBONITE_TOOLSET == CARBONITE_TOOLSET_MSVC)
#define CARBONITE_IS_TOOLSET_CLANG (CARBONITE_TOOLSET == CARBONITE_TOOLSET_CLANG)
#define CARBONITE_IS_TOOLSET_GCC   (CARBONITE_TOOLSET == CARBONITE_TOOLSET_GCC)

#define CARBONITE_IS_PLATFORM_AMD64 (CARBONITE_PLATFORM == CARBONITE_PLATFORM_AMD64)

namespace Core
{
	using CarboniteConfigFlags   = Flags<std::uint16_t>;
	using CarboniteSystemFlags   = Flags<std::uint16_t>;
	using CarboniteToolsetFlags  = Flags<std::uint16_t>;
	using CarbonitePlatformFlags = Flags<std::uint16_t>;

	std::ostream& printCarboniteConfigFlags(std::ostream& stream, const CarboniteConfigFlags& flags);
	std::ostream& printCarboniteSystemFlags(std::ostream& stream, const CarboniteSystemFlags& flags);
	std::ostream& printCarboniteToolsetFlags(std::ostream& stream, const CarboniteToolsetFlags& flags);
	std::ostream& printCarbonitePlatformFlags(std::ostream& stream, const CarbonitePlatformFlags& flags);

	namespace CarboniteConfigFlag
	{
		static constexpr CarboniteConfigFlags Unknown = 0;
		static constexpr CarboniteConfigFlags Debug   = 1;
		static constexpr CarboniteConfigFlags Dist    = 2;
	} // namespace CarboniteConfigFlag

	namespace CarboniteSystemFlag
	{
		static constexpr CarboniteSystemFlags Unknown = 0;
		static constexpr CarboniteSystemFlags Windows = 1;
		static constexpr CarboniteSystemFlags Macosx  = 2;
		static constexpr CarboniteSystemFlags Linux   = 4;
		static constexpr CarboniteSystemFlags Unix    = 8;
	} // namespace CarboniteSystemFlag

	namespace CarboniteToolsetFlag
	{
		static constexpr CarboniteToolsetFlags Unknown = 0;
		static constexpr CarboniteToolsetFlags MSVC    = 1;
		static constexpr CarboniteToolsetFlags Clang   = 2;
		static constexpr CarboniteToolsetFlags GCC     = 4;
	} // namespace CarboniteToolsetFlag

	namespace CarbonitePlatformFlag
	{
		static constexpr CarbonitePlatformFlags Unknown = 0;
		static constexpr CarbonitePlatformFlags X86     = 1;
		static constexpr CarbonitePlatformFlags AMD64   = 2;
	} // namespace CarbonitePlatformFlag

#if CARBONITE_IS_CONFIG_DEBUG
	static constexpr CarboniteConfigFlags s_Config        = CarboniteConfigFlag::Debug;
	static constexpr bool                 s_IsConfigDebug = true;
	static constexpr bool                 s_IsConfigDist  = false;
#elif CARBONITE_IS_CONFIG_RELEASE
	static constexpr CarboniteConfigFlags   s_Config          = CarboniteConfigFlag::Debug | CarboniteConfigFlags::Dist;
	static constexpr bool                   s_IsConfigDebug   = true;
	static constexpr bool                   s_IsConfigDist    = true;
#elif CARBONITE_IS_CONFIG_DIST
	static constexpr CarboniteConfigFlags  s_Config          = CarboniteConfigFlag::Dist;
	static constexpr bool                  s_IsConfigDebug   = false;
	static constexpr bool                  s_IsConfigDist    = true;
#else
	static constexpr CarboniteConfigFlags  s_Config          = CarboniteConfigFlag::Unknown;
	static constexpr bool                  s_IsConfigDebug   = false;
	static constexpr bool                  s_IsConfigDist    = false;
#endif

#if CARBONITE_IS_SYSTEM_WINDOWS
	static constexpr CarboniteSystemFlags s_System          = CarboniteSystemFlag::Windows;
	static constexpr bool                 s_IsSystemWindows = true;
	static constexpr bool                 s_IsSystemMacosx  = false;
	static constexpr bool                 s_IsSystemLinux   = false;
	static constexpr bool                 s_IsSystemUnix    = false;
#elif CARBONITE_IS_SYSTEM_MACOSX
	static constexpr CarboniteSystemFlags   s_System          = CarboniteSystemFlag::Macosx | CarboniteSystemFlag::Unix;
	static constexpr bool                   s_IsSystemWindows = false;
	static constexpr bool                   s_IsSystemMacosx  = true;
	static constexpr bool                   s_IsSystemLinux   = false;
	static constexpr bool                   s_IsSystemUnix    = true;
#elif CARBONITE_IS_SYSTEM_LINUX
	static constexpr CarboniteSystemFlags  s_System          = CarboniteSystemFlag::Linux | CarboniteSystemFlag::Unix;
	static constexpr bool                  s_IsSystemWindows = false;
	static constexpr bool                  s_IsSystemMacosx  = false;
	static constexpr bool                  s_IsSystemLinux   = true;
	static constexpr bool                  s_IsSystemUnix    = true;
#else
	static constexpr CarboniteSystemFlags  s_System          = CarboniteSystemFlag::Unknown;
	static constexpr bool                  s_IsSystemWindows = false;
	static constexpr bool                  s_IsSystemMacosx  = false;
	static constexpr bool                  s_IsSystemLinux   = false;
	static constexpr bool                  s_IsSystemUnix    = false;
#endif

#if CARBONITE_IS_TOOLSET_MSVC
	static constexpr CarboniteToolsetFlags s_Toolset        = CarboniteToolsetFlag::MSVC;
	static constexpr bool                  s_IsToolsetMSVC  = true;
	static constexpr bool                  s_IsToolsetClang = false;
	static constexpr bool                  s_IsToolsetGCC   = false;
#elif CARBONITE_IS_TOOLSET_CLANG
	static constexpr CarboniteToolsetFlags  s_Toolset         = CarboniteToolsetFlag::Clang;
	static constexpr bool                   s_IsToolsetMSVC   = false;
	static constexpr bool                   s_IsToolsetClang  = true;
	static constexpr bool                   s_IsToolsetGCC    = false;
#elif CARBONITE_IS_TOOLSET_GCC
	static constexpr CarboniteToolsetFlags s_Toolset         = CarboniteToolsetFlag::GCC;
	static constexpr bool                  s_IsToolsetMSVC   = false;
	static constexpr bool                  s_IsToolsetClang  = false;
	static constexpr bool                  s_IsToolsetGCC    = true;
#else
	static constexpr CarboniteToolsetFlags s_Toolset         = CarboniteToolsetFlag::Unknown;
	static constexpr bool                  s_IsToolsetMSVC   = false;
	static constexpr bool                  s_IsToolsetClang  = false;
	static constexpr bool                  s_IsToolsetGCC    = false;
#endif

#if CARBONITE_IS_PLATFORM_AMD64
	static constexpr CarbonitePlatformFlags s_Platform        = CarbonitePlatformFlag::AMD64;
	static constexpr bool                   s_IsPlatformX86   = false;
	static constexpr bool                   s_IsPlatformAMD64 = true;
#else
	static constexpr CarbonitePlatformFlags s_Platform        = CarbonitePlatformFlag::Unknown;
	static constexpr bool                   s_IsPlatformX86   = false;
	static constexpr bool                   s_IsPlatformAMD64 = false;
#endif
} // namespace Core