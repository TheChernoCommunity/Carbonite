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

local workspaceName = "VulkanTemplate"
local programName = "VulkanProgram"

local vulkanSDKPath = os.getenv("VULKAN_SDK")
if not vulkanSDKPath then
	local hostOS = os.host()
	if hostOS == "windows" then
		error("Have you installed the Vulkan SDK correctly.\nIf you have then please go into environment variables and add 'VULKAN_SDK' with the path to the SDK!")
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

	filter("configurations:Debug")
		defines({ "_DEBUG" })
		optimize("Off")
		symbols("On")

	filter("configurations:Release")
		defines({ "_RELEASE" })
		optimize("Full")
		symbols("On")

	filter("configurations:Dist")
		defines({ "_RELEASE" })
		optimize("Full")
		symbols("Off")

	filter("system:windows")
		toolset("msc")
		defines({ "NOMINMAX", "WIN32_LEAN_AND_MEAN", "_CRT_SECURE_NO_WARNINGS" })

	filter({})
	
	startproject(programName)
	
	group("Dependencies")
	project("GLFW")
		location("ThirdParty/GLFW/")
		kind("StaticLib")
		targetdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
		objdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")

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

		includedirs({ "%{prj.location}/include/" })
		sysincludedirs({
			"%{wks.location}/Deps/Vulkan/Vulkan-Headers/include/"
		})

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
		kind("StaticLib")
		targetdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
		objdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")

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

		filter("configurations:Debug")
			kind("ConsoleApp")

		filter("configurations:Release or Dist")
			kind("WindowedApp")

		filter("system:windows")
			libdirs({ vulkanSDKPath .. "/Lib/" })
			links({ "vulkan-1.lib" })
			sysincludedirs({ vulkanSDKPath .. "/Include/vulkan/" })

		filter("system:linux")
			libdirs({ vulkanSDKPath .. "/lib/" })
			links({ "libvulkan.so.1" })
			sysincludedirs({ vulkanSDKPath .. "/include/vulkan/" })
			
		filter("system:macosx")
			libdirs({ vulkanSDKPath .. "/lib/" })
			links({
				"libvulkan.1.dylib",
				"CoreGraphics.framework",
				"IOKit.framework",
				"AppKit.framework"
				--, "OpenGL.framework" -- Not sure if this is needed, so I'll keep it out for now
			})
			sysincludedirs({ vulkanSDKPath .. "/include/vulkan/" })
		
		filter({})
		
		defines({ "GLFW_INCLUDE_NONE" })

		links({ "GLFW", "VMA", "ImGUI" })
		sysincludedirs({
			"%{wks.location}/ThirdParty/GLFW/include/",
			"%{wks.location}/ThirdParty/VMA/include/",
			"%{wks.location}/ThirdParty/ImGUI/",
			"%{wks.location}/ThirdParty/STB/"
		})

		includedirs({
			"%{prj.location}/inc",
			"%{prj.location}/src"
		})

		files({ "%{prj.location}/**" })
		removefiles({ "*.vcxproj", "*.vcxproj.*", "*.Make", "*.mak", "*.xcodeproj/", "*.DS_Store" })