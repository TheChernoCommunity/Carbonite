require("Premake/Actions/clean")
require("Premake/Actions/format-tidy")
require("Premake/Actions/pch")

common = require("Premake/common")
glfw = require("Premake/Libs/glfw")
vma = require("Premake/Libs/vma")
imgui = require("Premake/Libs/imgui")
stb = require("Premake/Libs/stb")
vulkan = require("Premake/Libs/vulkan")

workspace("Carbonite")
	common:setConfigsAndPlatforms()

	cppdialect("C++17")
	rtti("Off")
	exceptionhandling("On")
	flags("MultiProcessorCompile")

	common:addCoreDefines()
	
	startproject("Carbonite")
	
	group("Dependencies")
	project("GLFW")
		location("ThirdParty/GLFW/")
		warnings("Off")
		glfw:setup()

	project("VMA")
		location("ThirdParty/VMA/")
		warnings("Off")
		vma:setup()

	project("ImGUI")
		location("ThirdParty/ImGUI/")
		warnings("Off")
		imgui:setup()

	project("STB")
		location("ThirdParty/STB/")
		warnings("Off")
		stb:setup()

	project("VulkanHeaders")
		location("")
		warnings("Off")
		vulkan:setup()

	group("Game")
	project("Carbonite")
		location("Carbonite/")
		warnings("Extra")

		common:executableOutDirs()
		common:debugDir()

		filter("configurations:Debug")
			kind("ConsoleApp")

		filter("configurations:not Debug")
			kind("WindowedApp")

		filter({})

		common:addPCH("%{prj.location}/Source/PCH.cpp", "%{prj.location}/Include/PCH.h")
		
		prebuildcommands({ _PREMAKE_COMMAND .. " \"--file=" .. _MAIN_SCRIPT .. "\" \"--vulkan-sdk=" .. vulkan.sdkPath .. "\" force-pch" })

		includedirs({
			"%{prj.location}/Include/",
			"%{prj.location}/Source/"
		})

		glfw:setupDep()
		vma:setupDep()
		imgui:setupDep()
		stb:setupDep()
		vulkan:setupDep(false)

		sysincludedirs({
			"%{wks.location}/ThirdParty/inipp/inipp/",
			"%{wks.location}/ThirdParty/spdlog/include/"
		})

		files({ "%{prj.location}/**" })
		removefiles({ "*.vcxproj", "*.vcxproj.*", "*.Make", "*.mak", "*.xcodeproj/", "*.DS_Store" })

		filter("files:**.inl")
			runclangformat(true)

		filter("files:**.h")
			runclangformat(true)

		filter("files:**.cpp")
			runclangformat(true)
			runclangtidy(true)
			allowforcepch(true)

		filter({})
