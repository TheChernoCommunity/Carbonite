local glfw = {
	sourceDir = "/src/",
	includeDir = "/include/",
	name = "",
	location = ""
}

-- Add --glfw-use-wayland option to premake
newoption({
	trigger = "glfw-use-wayland",
	description = "Should glfw use wayland for linux builds"
})

function glfw:setup()
	self.name = common:projectName()
	self.location = common:projectLocation()

	kind("StaticLib")
	common:staticLibOutDirs()

	includedirs({ "%{prj.location}" .. self.includeDir })

	files({
		"%{prj.location}" .. self.includeDir .. "**",
		"%{prj.location}" .. self.sourceDir .."context.c",
		"%{prj.location}" .. self.sourceDir .."init.c",
		"%{prj.location}" .. self.sourceDir .."input.c",
		"%{prj.location}" .. self.sourceDir .."internal.h",
		"%{prj.location}" .. self.sourceDir .."mappings.h",
		"%{prj.location}" .. self.sourceDir .."monitor.c",
		"%{prj.location}" .. self.sourceDir .."null_*",
		"%{prj.location}" .. self.sourceDir .."platform.h",
		"%{prj.location}" .. self.sourceDir .."platform.c",
		"%{prj.location}" .. self.sourceDir .."vulkan.c",
		"%{prj.location}" .. self.sourceDir .."window.c",
		"%{prj.location}" .. self.sourceDir .."egl_*",
		"%{prj.location}" .. self.sourceDir .."osmesa_*"
	})

	filter("system:windows")
		files({
			"%{prj.location}" .. self.sourceDir .. "win32_*",
			"%{prj.location}" .. self.sourceDir .. "wgl_*"
		})

		defines({ "_GLFW_WIN32" })

	filter("system:linux")
		files({
			"%{prj.location}" .. self.sourceDir .. "linux_*",
			"%{prj.location}" .. self.sourceDir .. "posix_*",
			"%{prj.location}" .. self.sourceDir .. "xkb_*",
			"%{prj.location}" .. self.sourceDir .. "glx_*"
		})
	
	if _OPTIONS["glfw-use-wayland"] then
		files({
			"%{prj.location}" .. self.sourceDir .. "wl_*"
		})

		defines({ "_GLFW_WAYLAND" })
	else
		files({
			"%{prj.location}" .. self.sourceDir .. "x11_*"
		})

		defines({ "_GLFW_X11" })
	end

	filter("system:macosx")
		files({
			"%{prj.location}" .. self.sourceDir .. "cocoa_*",
			"%{prj.location}" .. self.sourceDir .. "nsgl_*",
			"%{prj.location}" .. self.sourceDir .. "posix_*"
		})
		removefiles({
			"%{prj.location}" .. self.sourceDir .. "posix_time.h",
			"%{prj.location}" .. self.sourceDir .. "posix_time.c"
		})

		defines({ "_GLFW_COCOA" })

	filter({})
end

function glfw:setupDep()
	filter("system:macosx")
		links({
			"CoreGraphics.framework",
			"IOKit.framework",
			"AppKit.framework"
		})

	links({ self.name })
	sysincludedirs({ self.location .. self.includeDir })
end

return glfw
