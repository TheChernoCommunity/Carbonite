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

	includedirs({ self.location .. self.includeDir })

	files({
		self.location .. self.includeDir .. "**",
		self.location .. self.sourceDir .."context.c",
		self.location .. self.sourceDir .."init.c",
		self.location .. self.sourceDir .."input.c",
		self.location .. self.sourceDir .."internal.h",
		self.location .. self.sourceDir .."mappings.h",
		self.location .. self.sourceDir .."monitor.c",
		self.location .. self.sourceDir .."null_*",
		self.location .. self.sourceDir .."platform.h",
		self.location .. self.sourceDir .."platform.c",
		self.location .. self.sourceDir .."vulkan.c",
		self.location .. self.sourceDir .."window.c",
		self.location .. self.sourceDir .."egl_*",
		self.location .. self.sourceDir .."osmesa_*"
	})

	filter("system:windows")
		files({
			self.location .. self.sourceDir .. "win32_*",
			self.location .. self.sourceDir .. "wgl_*"
		})

		defines({ "_GLFW_WIN32" })

	filter("system:linux")
		files({
			self.location .. self.sourceDir .. "linux_*",
			self.location .. self.sourceDir .. "posix_*",
			self.location .. self.sourceDir .. "xkb_*",
			self.location .. self.sourceDir .. "glx_*"
		})
	
	if _OPTIONS["glfw-use-wayland"] then
		files({
			self.location .. self.sourceDir .. "wl_*"
		})

		defines({ "_GLFW_WAYLAND" })
	else
		files({
			self.location .. self.sourceDir .. "x11_*"
		})

		defines({ "_GLFW_X11" })
	end

	filter("system:macosx")
		files({
			self.location .. self.sourceDir .. "cocoa_*",
			self.location .. self.sourceDir .. "nsgl_*",
			self.location .. self.sourceDir .. "posix_*"
		})
		removefiles({
			self.location .. self.sourceDir .. "posix_time.h",
			self.location .. self.sourceDir .. "posix_time.c"
		})

		defines({ "_GLFW_COCOA" })

	filter({})
end

function glfw:setupDep()
	filter("system:linux")
		links({ "dl" })

		linkoptions({ "-pthread" })

	filter("system:macosx")
		links({
			"CoreGraphics.framework",
			"IOKit.framework",
			"AppKit.framework"
		})

	filter({})

	links({ self.name })
	sysincludedirs({ self.location .. self.includeDir })
end

return glfw
