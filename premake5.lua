require("Premake/cleanAction")
require("Premake/formatTidyAction")

newoption({
	trigger = "glfw_use_wayland",
	description = "Should glfw use wayland for linux build",
	value = "boolean",
	allowed = {
		{ "N", "No" },
		{ "Y", "Yes" }
	},
	default = "N"
})

local vulkanSDKPath = os.getenv("VULKAN_SDK")
if not vulkanSDKPath then
	local hostOS = os.host()
	if hostOS == "windows" then
		error("Have you installed the Vulkan SDK correctly.\nIf you have then please go into environment variables and add 'VULKAN_SDK' with the path to the SDK!")
	elseif hostOS == "macosx" then
		error("Please find the Vulkan SDK and run the 'setup-env.sh' script in a terminal environment before running premake again!\nYou can open '~/.zshrc' or '~/.bashrc' and add:\ncd \"PathToVulkanSDK\"\nsource setup-env.sh\ncd ~/")
	else
		error("Please find the Vulkan SDK and run the 'setup-env.sh' script in a terminal environment before running premake again!\nYou can open '~/.zshrc' or '~/.bashrc' and add 'source \"PathToVulkanSDK/setup-env.sh\"'")
	end
end

workspace("Carbonite")
	configurations({ "Debug", "Release", "Dist" })
	platforms({ "x64" })

	cppdialect("C++17")
	rtti("Off")
	exceptionhandling("On")
	flags("MultiProcessorCompile")
	runclangformat(false)
	runclangtidy(false)

	filter("configurations:Debug")
		defines({
			"CARBONITE_CONFIG=CARBONITE_CONFIG_DEBUG",
			"_DEBUG",
			"NRELEASE"
		})
		optimize("Off")
		symbols("On")

	filter("configurations:Release")
		defines({
			"CARBONITE_CONFIG=CARBONITE_CONFIG_RELEASE",
			"NDEBUG",
			"_RELEASE"
		})
		optimize("Full")
		symbols("On")

	filter("configurations:Dist")
		defines({ "CARBONITE_CONFIG=CARBONITE_CONFIG_DIST" })
		optimize("Full")
		symbols("Off")
	
	filter("system:windows")
		toolset("msc")
		defines({
			"CARBONITE_SYSTEM=CARBONITE_SYSTEM_WINDOWS",
			"NOMINMAX",
			"WIN32_LEAN_AND_MEAN",
			"_CRT_SECURE_NO_WARNINGS"
		})
	
	filter("system:macosx")
		defines({ "CARBONITE_SYSTEM=CARBONITE_SYSTEM_MACOSX" })
	
	filter("system:linux")
		defines({ "CARBONITE_SYSTEM=CARBONITE_SYSTEM_LINUX" })
	
	filter("toolset:msc")
		defines({ "CARBONITE_TOOLSET=CARBONITE_TOOLSET_MSVC" })
	
	filter("toolset:clang")
		defines({ "CARBONITE_TOOLSET=CARBONITE_TOOLSET_CLANG" })
	
	filter("toolset:gcc")
		defines({ "CARBONITE_TOOLSET=CARBONITE_TOOLSET_GCC" })
	
	filter("platforms:x64")
		defines({ "CARBONITE_PLATFORM=CARBONITE_PLATFORM_X64" })

	filter({})
	
	startproject("Carbonite")
	
	group("Dependencies")
	project("GLFW")
		location("ThirdParty/GLFW/")
		kind("StaticLib")
		targetdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
		objdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
		
		warnings("Off")

		includedirs({ "%{prj.location}/include/" })

		files({
			"%{prj.location}/include/**",
			"%{prj.location}/src/context.c",
			"%{prj.location}/src/init.c",
			"%{prj.location}/src/input.c",
			"%{prj.location}/src/internal.h",
			"%{prj.location}/src/mappings.h",
			"%{prj.location}/src/monitor.c",
			"%{prj.location}/src/null_*",
			"%{prj.location}/src/platform.h",
			"%{prj.location}/src/platform.c",
			"%{prj.location}/src/vulkan.c",
			"%{prj.location}/src/window.c",
			"%{prj.location}/src/egl_*",
			"%{prj.location}/src/osmesa_*"
		})

		filter("system:windows")
			files({
				"%{prj.location}/src/win32_*",
				"%{prj.location}/src/wgl_*"
			})

			defines({ "_GLFW_WIN32" })

		filter("system:linux")
			files({
				"%{prj.location}/src/linux_*",
				"%{prj.location}/src/posix_*",
				"%{prj.location}/src/xkb_*",
				"%{prj.location}/src/glx_*"
			})
			
if _OPTIONS["glfw_use_wayland"] == "Y" then
			files({
				"%{prj.location}/src/wl_*"
			})

			defines({ "_GLFW_WAYLAND" })
else
			files({
				"%{prj.location}/src/x11_*"
			})

			defines({ "_GLFW_X11" })
end

		filter("system:macosx")
			files({
				"%{prj.location}/src/cocoa_*",
				"%{prj.location}/src/nsgl_*",
				"%{prj.location}/src/posix_*"
			})
			removefiles({
				"%{prj.location}/src/posix_time.h",
				"%{prj.location}/src/posix_time.c"
			})

			defines({ "_GLFW_COCOA" })

		filter({})

	project("VMA")
		location("ThirdParty/VMA/")
		kind("StaticLib")
		targetdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
		objdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
		removedefines({ "NOMINMAX", "WIN32_LEAN_AND_MEAN" })
		
		warnings("Off")

		includedirs({ "%{prj.location}/include/" })
		filter("system:windows")
			sysincludedirs({ vulkanSDKPath .. "/Include/" })

		filter("system:linux")
			sysincludedirs({ vulkanSDKPath .. "/include/" })
			
		filter("system:macosx")
			sysincludedirs({ vulkanSDKPath .. "/include/" })
		
		filter({})

		files({
			"%{prj.location}/include/**",
			"%{prj.location}/src/VmaUsage.h",
			"%{prj.location}/src/VmaUsage.cpp"
		})

	project("ImGUI")
		location("ThirdParty/ImGUI/")
		kind("StaticLib")
		targetdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
		objdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
		
		warnings("Off")

		includedirs({ "%{prj.location}/" })

		files({
			"%{prj.location}/imgui.h",
			"%{prj.location}/imgui.cpp",
			"%{prj.location}/imgui_draw.cpp",
			"%{prj.location}/imgui_internal.h",
			"%{prj.location}/imgui_tables.cpp",
			"%{prj.location}/imgui_widgets.cpp",
			"%{prj.location}/imstb_rectpack.h",
			"%{prj.location}/imstb_textedit.h",
			"%{prj.location}/imstb_truetype.h"
		})

	project("STB")
		location("ThirdParty/STB/")
		kind("Utility")
		
		warnings("Off")

		includedirs({ "%{prj.location}/include/" })

		files({
			"%{prj.location}/stb_image.h"
		})

	group("Game")
	project("Carbonite")
		location("Carbonite/")
		targetdir("%{wks.location}/Bin/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/")
		objdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
		debugdir("%{prj.location}/")
		
		warnings("Extra")
		
		filter("action:xcode4")
			pchheader("%{prj.location}/Include/PCH.h")
		
		filter("action:not xcode4")
			pchheader("PCH.h")
		
		filter({})
		pchsource("%{prj.location}/Source/PCH.cpp")

		filter("configurations:Debug")
			kind("ConsoleApp")

		filter("configurations:Release or Dist")
			kind("WindowedApp")

		filter("system:windows")
			libdirs({ vulkanSDKPath .. "/Lib/" })
			links({
				"vulkan-1.lib",
				"glslang.lib",
				"SPIRV.lib",
				"SPVRemapper.lib",
				"GenericCodeGen.lib",
				"MachineIndependent.lib",
				"OSDependent.lib",
				"OGLCompiler.lib",
				"SPIRV-Tools.lib",
				"SPIRV-Tools-opt.lib",
				"SPIRV-Tools-link.lib"
			})
			sysincludedirs({ vulkanSDKPath .. "/Include/" })

		filter("system:linux")
			libdirs({ vulkanSDKPath .. "/lib/" })
			links({
				"libvulkan.so.1",
				"libglslang.a"
			})
			sysincludedirs({ vulkanSDKPath .. "/include/" })
			
		filter("system:macosx")
			libdirs({ vulkanSDKPath .. "/lib/" })
			links({
				"vulkan",
				"glslang",
				"SPIRV",
				"SPVRemapper",
				"GenericCodeGen",
				"MachineIndependent",
				"OSDependent",
				"OGLCompiler",
				"SPIRV-Tools",
				"SPIRV-Tools-opt",
				"SPIRV-Tools-link",
				"CoreGraphics.framework",
				"IOKit.framework",
				"AppKit.framework"
			})
			sysincludedirs({ vulkanSDKPath .. "/include/" })
		
		filter({})

		links({ "GLFW", "VMA", "ImGUI" })
		sysincludedirs({
			"%{wks.location}/ThirdParty/GLFW/include/",
			"%{wks.location}/ThirdParty/VMA/include/",
			"%{wks.location}/ThirdParty/ImGUI/",
			"%{wks.location}/ThirdParty/STB/",
			"%{wks.location}/ThirdParty/inipp/inipp/",
			"%{wks.location}/ThirdParty/spdlog/include/"
		})

		includedirs({
			"%{prj.location}/Include/",
			"%{prj.location}/Source/"
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
		
		filter({})
