return function()
	warnings 'Off'

	includedirs
	{
		"third_party/openal-soft/src",
		"third_party/openal-soft/src/alc",
		"third_party/openal-soft/src/common",
		"third_party/openal-soft/include",
		"third_party/openal-soft/include/AL"
	}

	files
	{
		"third_party/openal-soft/src/**.h",
		"third_party/openal-soft/src/**.cpp"
	}

	excludes
	{
		"third_party/openal-soft/src/alc/mixer/mixer_neon.cpp"
	}

	defines
	{
		"AL_LIBTYPE_STATIC"
	}

	filter 'system:windows'
		systemversion "latest"

		defines
		{
			"WIN32",
			"_WINDOWS",
			"AL_BUILD_LIBRARY",
			"AL_ALEXT_PROTOTYPES",
			"_WIN32",
			"_WIN32_WINNT=0x0502",
			"_CRT_SECURE_NO_WARNINGS",
			"NOMINMAX",
			"CMAKE_INTDIR=\"Debug\"",
			"OpenAL_EXPORTS"
		}

		links
		{
			"winmm"
		}
end
