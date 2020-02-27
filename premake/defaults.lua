
require 'customizations'

cppdialect 'C++17'
debugdir '../assets'
exceptionhandling 'Off'
flags { 'MultiProcessorCompile' }
includedirs { '../include/' }
objdir '../obj'
rtti 'Off'
targetdir '../%{iif(prj.kind == "StaticLib" or prj.kind == "SharedLib","lib","bin")}/%{cfg.platform}/%{cfg.buildcfg}'
warnings 'Extra'

filter 'configurations:Debug'
	optimize 'Off'
	symbols 'On'
	defines { 'DEBUG' }

filter 'configurations:Release'
	optimize 'Full'
	symbols 'Off'
	defines { 'RELEASE', 'NDEBUG' }

filter 'system:windows'
	toolset 'msc'
	defines { 'NOMINMAX' }

filter 'system:not windows'
	toolset 'gcc'

filter 'system:linux'
	debugenvs { 'LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../%{OUTDIR}' }

filter { }
