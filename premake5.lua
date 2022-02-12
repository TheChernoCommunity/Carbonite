require("Premake/Common")

require("Premake/Libs/entt")
require("Premake/Libs/glfw")
require("Premake/Libs/glm")
require("Premake/Libs/imgui")
require("Premake/Libs/mono")
require("Premake/Libs/spdlog")
require("Premake/Libs/stb")
require("Premake/Libs/vma")
require("Premake/Libs/vulkan")
-- require("Premake/Libs/inipp")

workspace("Carbonite")
	common:setConfigsAndPlatforms()

	common:addCoreDefines()

	cppdialect("C++20")
	rtti("Off")
	exceptionhandling("On")
	flags("MultiProcessorCompile")

	startproject("Carbonite")

	group("Dependencies")
	project("GLFW")
		location("ThirdParty/GLFW/")
		warnings("Off")
		libs.glfw:setup()
		location("ThirdParty/")

	project("VMA")
		location("ThirdParty/VMA/")
		warnings("Off")
		libs.vma:setup()
		location("ThirdParty/")

	project("ImGUI")
		location("ThirdParty/ImGUI/")
		warnings("Off")
		libs.imgui:setup()
		location("ThirdParty/")

	project("STB")
		location("ThirdParty/STB/")
		warnings("Off")
		libs.stb:setup()
		location("ThirdParty/")

	-- project("Inipp")
		-- location("ThirdParty/inipp/")
		-- warnings("Off")
		-- inipp:setup()
		-- location("ThirdParty/")

	project("Spdlog")
		location("ThirdParty/spdlog/")
		warnings("Off")
		libs.spdlog:setup()
		location("ThirdParty/")

	project("VulkanHeaders")
		location("")
		warnings("Off")
		libs.vulkan:setup()
		location("ThirdParty/")

	project("glm")
		location("ThirdParty/glm/")
		warnings("Off")
		libs.glm:setup()
		location("ThirdParty/")

	project("entt")
		location("ThirdParty/entt/")
		warnings("Off")
		libs.entt:setup()
		location("ThirdParty/")

	project("mono")
		location("ThirdParty/mono/")
		warnings("Off")
		libs.mono:setup()
		location("ThirdParty/")

	group("Game")
	project("Carbonite")
		location("Carbonite/")
		warnings("Extra")

		common:outDirs()
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

		libs.glfw:setupDep()
		libs.vma:setupDep()
		libs.imgui:setupDep()
		libs.stb:setupDep()
		-- libs.inipp:setupDep()
		libs.spdlog:setupDep()
		libs.vulkan:setupDep(false)
		libs.glm:setupDep()
		libs.entt:setupDep()
		libs.mono:setupDep()

		files({ "%{prj.location}/Source/**" })
		removefiles({ "*.DS_Store" })

		common:addActions()
