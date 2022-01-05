require("Premake/Actions/clean")
require("Premake/Actions/format-tidy")
require("Premake/Actions/pch")

common = require("Premake/common")
dotnet = require("Premake/Libs/dotnet")

glfw = require("Premake/Libs/glfw")
vma = require("Premake/Libs/vma")
imgui = require("Premake/Libs/imgui")
stb = require("Premake/Libs/stb")
inipp = require("Premake/Libs/inipp")
spdlog = require("Premake/Libs/spdlog")
vulkan = require("Premake/Libs/vulkan")
glm = require("Premake/Libs/glm")
entt = require("Premake/Libs/entt")

workspace("Carbonite")
	common:setConfigsAndPlatforms()

	common:addCoreDefines()

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
		location("ThirdParty/")

	project("VMA")
		location("ThirdParty/VMA/")
		warnings("Off")
		vma:setup()
		location("ThirdParty/")

	project("ImGUI")
		location("ThirdParty/ImGUI/")
		warnings("Off")
		imgui:setup()
		location("ThirdParty/")

	project("STB")
		location("ThirdParty/STB/")
		warnings("Off")
		stb:setup()
		location("ThirdParty/")

	project("Inipp")
		location("ThirdParty/inipp/")
		warnings("Off")
		inipp:setup()
		location("ThirdParty/")

	project("Spdlog")
		location("ThirdParty/spdlog/")
		warnings("Off")
		spdlog:setup()
		location("ThirdParty/")

	project("VulkanHeaders")
		location("")
		warnings("Off")
		vulkan:setup()
		location("ThirdParty/")

	project("glm")
		location("ThirdParty/glm/")
		warnings("Off")
		glm:setup()
		location("ThirdParty/")

	project("entt")
		location("ThirdParty/entt/")
		warnings("Off")
		entt:setup()
		location("ThirdParty/")

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

		common:addPCH("%{prj.location}/Source/PCH.cpp", "%{prj.location}/Source/PCH.h")

		includedirs({ "%{prj.location}/Source/" })

		if common.host == "windows" then
			linkoptions({ "/IGNORE:4099" })
		elseif common.host == "macosx" then
			linkoptions({ "-Wl,-rpath,'@executable_path'" })
		end

		glfw:setupDep()
		vma:setupDep()
		imgui:setupDep()
		stb:setupDep()
		inipp:setupDep()
		spdlog:setupDep()
		vulkan:setupDep(false)
		dotnet:setupDep()
		glm:setupDep()
		entt:setupDep()

		files({ "%{prj.location}/Source/**" })
		removefiles({ "*.DS_Store" })

		common:addActions()
