require("Premake/Actions/clean")
require("Premake/Actions/format-tidy")
require("Premake/Actions/pch")

newoption({
	trigger = "only-csharp",
	description = "Only generate a C# workspace"
})
newoption({
	trigger = "only-cpp",
	description = "Only generate a C++ workspace"
})

local addCSharp = true
local addCpp = true
if _OPTIONS["only-csharp"] then
	addCpp = false
elseif _OPTIONS["only-cpp"] then
	addCSharp = false
end

common = require("Premake/common")
dotnet = require("Premake/Libs/dotnet")

if addCpp then
	glfw = require("Premake/Libs/glfw")
	vma = require("Premake/Libs/vma")
	imgui = require("Premake/Libs/imgui")
	stb = require("Premake/Libs/stb")
	inipp = require("Premake/Libs/inipp")
	spdlog = require("Premake/Libs/spdlog")
	vulkan = require("Premake/Libs/vulkan")
end

workspace((function()
		if addCSharp and addCpp then
			return "Carbonite"
		elseif addCpp then
			return "Carbonite-Cpp"
		elseif addCSharp then
			return "Carbonite-CSharp"
		else
			return "Carbonite"
		end
	end)())
	common:setConfigsAndPlatforms()
	
	common:addCoreDefines()

if addCSharp then
	csversion("10")
	dotnetframework("net6.0")
end

if addCpp then
	cppdialect("C++17")
	rtti("Off")
	exceptionhandling("On")
	flags("MultiProcessorCompile")

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

	project("Inipp")
		location("ThirdParty/inipp/")
		warnings("Off")
		inipp:setup()

	project("Spdlog")
		location("ThirdParty/spdlog/")
		warnings("Off")
		spdlog:setup()

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
		
		prebuildcommands({ _PREMAKE_COMMAND .. " \"--file=" .. _MAIN_SCRIPT .. "\" \"--vulkan-sdk=" .. vulkan.sdkPath .. "\" \"--dotnet-runtime-dir=" .. dotnet.runtimeDir .. "\" force-pch" })

		includedirs({
			"%{prj.location}/Include/",
			"%{prj.location}/Source/"
		})

		glfw:setupDep()
		vma:setupDep()
		imgui:setupDep()
		stb:setupDep()
		inipp:setupDep()
		spdlog:setupDep()
		vulkan:setupDep(false)
		dotnet:setupDep()

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
end

if addCSharp then
	group("Mods")
	project("API")
		location("CarboniteModAPI/")
		language("C#")
		kind("SharedLib")
		warnings("Extra")

		common:sharedLibOutDirs()

		files({ "%{prj.location}/**" })
		removefiles({ "*.vcxproj", "*.vcxproj.*", "*.Make", "*.mak", "*.xcodeproj/", "*.DS_Store" })

		filter("files:**.cs")
			runclangformat(true)

		filter({})

	project("Base")
		location("CarboniteBaseMod/")
		language("C#")
		kind("SharedLib")
		warnings("Extra")

		common:modOutDirs()

		links({ "API" })

		files({ "%{prj.location}/**" })
		removefiles({ "*.vcxproj", "*.vcxproj.*", "*.Make", "*.mak", "*.xcodeproj/", "*.DS_Store" })

		filter("files:**.cs")
			runclangformat(true)

		filter({})
end