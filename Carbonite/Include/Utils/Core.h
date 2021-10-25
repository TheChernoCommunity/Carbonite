#pragma once

#ifndef CARBONITE_ISFLAG
#define CARBONITE_ISFLAG(flags, flag) ((flags & flag) == flag)
#endif

#ifndef CARBONITE_CONFIG_UNKNOWN
#define CARBONITE_CONFIG_UNKNOWN 0
#define CARBONITE_CONFIG_DEBUG   1
#define CARBONITE_CONFIG_DIST    2
#define CARBONITE_CONFIG_RELEASE CARBONITE_CONFIG_DIST

#define CARBONITE_IS_CONFIG_DEBUG CARBONITE_ISFLAG(CARBONITE_CONFIG, CARBONITE_CONFIG_DEBUG)
#define CARBONITE_IS_CONFIG_DIST  CARBONITE_ISFLAG(CARBONITE_CONFIG, CARBONITE_CONFIG_DIST)
#endif

#ifndef CARBONITE_SYSTEM_UNKNOWN
#define CARBONITE_SYSTEM_UNKNOWN 0
#define CARBONITE_SYSTEM_WINDOWS 1
#define CARBONITE_SYSTEM_MACOSX  2
#define CARBONITE_SYSTEM_LINUX   4

#define CARBONITE_IS_SYSTEM_WINDOWS CARBONITE_ISFLAG(CARBONITE_SYSTEM, CARBONITE_SYSTEM_WINDOWS)
#define CARBONITE_IS_SYSTEM_MACOSX  CARBONITE_ISFLAG(CARBONITE_SYSTEM, CARBONITE_SYSTEM_MACOSX)
#define CARBONITE_IS_SYSTEM_LINUX   CARBONITE_ISFLAG(CARBONITE_SYSTEM, CARBONITE_SYSTEM_LINUX)
#endif

#ifndef CARBONITE_TOOLSET_UNKNOWN
#define CARBONITE_TOOLSET_UNKNOWN 0
#define CARBONITE_TOOLSET_MSVC    1
#define CARBONITE_TOOLSET_CLANG   2
#define CARBONITE_TOOLSET_GCC     3

#define CARBONITE_IS_TOOLSET_MSVC  CARBONITE_ISFLAG(CARBONITE_TOOLSET, CARBONITE_TOOLSET_MSVC)
#define CARBONITE_IS_TOOLSET_CLANG CARBONITE_ISFLAG(CARBONITE_TOOLSET, CARBONITE_TOOLSET_CLANG)
#define CARBONITE_IS_TOOLSET_GCC   CARBONITE_ISFLAG(CARBONITE_TOOLSET, CARBONITE_TOOLSET_GCC)
#endif

#ifndef CARBONITE_PLATFORM_UNKNOWN
#define CARBONITE_PLATFORM_UNKNOWN 0
#define CARBONITE_PLATFORM_X64     1

#define CARBONITE_IS_PLATFORM_X64 CARBONITE_ISFLAG(CARBONITE_PLATFORM, CARBONITE_PLATFORM_X64)
#endif

namespace Core
{
#if CARBONITE_IS_CONFIG_DIST
	static constexpr bool s_IsDebugMode = false;
	static constexpr bool s_IsDistMode  = true;
#elif CARBONITE_IS_CONFIG_DEBUG
	static constexpr bool s_IsDebugMode = true;
	static constexpr bool s_IsDistMode  = false;
#else
	static constexpr bool s_IsDebugMode = false;
	static constexpr bool s_IsDistMode  = false;
#endif

#if CARBONITE_IS_SYSTEM_WINDOWS
	static constexpr bool s_IsWindows = true;
	static constexpr bool s_IsMacosx  = false;
	static constexpr bool s_IsLinux   = false;
#elif CARBONITE_IS_SYSTEM_MACOSX
	static constexpr bool s_IsWindows   = false;
	static constexpr bool s_IsMacosx    = true;
	static constexpr bool s_IsLinux     = false;
#elif CARBONITE_IS_SYSTEM_LINUX
	static constexpr bool s_IsWindows   = false;
	static constexpr bool s_IsMacosx    = false;
	static constexpr bool s_IsLinux     = true;
#else
	static constexpr bool s_IsWindows = false;
	static constexpr bool s_IsMacosx  = false;
	static constexpr bool s_IsLinux   = false;
#endif

#if CARBONITE_IS_PLATFORM_X64
	static constexpr bool s_IsX64 = true;
#else
	static constexpr bool s_IsX64       = false;
#endif
} // namespace Core

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif