if not libs then libs = {} end
if not libs.glfw then
	libs.glfw = {
		name       = "",
		location   = ""
	}
end

local glfw = libs.glfw

newoption({
	trigger     = "glfw-use-wayland",
	description = "Should glfw use wayland for linux builds"
})

function glfw:setup()
	self.name     = common:projectName()
	self.location = common:projectLocation()

	kind("StaticLib")
	common:outDirs(true)

	includedirs({ self.location .. "/include/" })

	files({
		self.location .. "/include/**",
		self.location .. "/src/context.c",
		self.location .. "/src/init.c",
		self.location .. "/src/input.c",
		self.location .. "/src/internal.h",
		self.location .. "/src/mappings.h",
		self.location .. "/src/monitor.c",
		self.location .. "/src/null_*",
		self.location .. "/src/platform.h",
		self.location .. "/src/platform.c",
		self.location .. "/src/vulkan.c",
		self.location .. "/src/window.c",
		self.location .. "/src/egl_*",
		self.location .. "/src/osmesa_*"
	})

	filter("system:windows")
		files({
			self.location .. "/src/win32_*",
			self.location .. "/src/wgl_*"
		})

		defines({ "_GLFW_WIN32" })

	filter("system:linux")
		files({
			self.location .. "/src/linux_*",
			self.location .. "/src/posix_*",
			self.location .. "/src/xkb_*",
			self.location .. "/src/glx_*"
		})

	if _OPTIONS["glfw-use-wayland"] then
		files({ self.location .. "/src/wl_*" })
		defines({ "_GLFW_WAYLAND" })
	else
		files({ self.location .. "/src/x11_*" })
		defines({ "_GLFW_X11" })
	end

	filter("system:macosx")
		files({
			self.location .. "/src/cocoa_*",
			self.location .. "/src/nsgl_*",
			self.location .. "/src/posix_*"
		})
		removefiles({
			self.location .. "/src/posix_time.h",
			self.location .. "/src/posix_time.c"
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
	sysincludedirs({ self.location .. "/include/" })
end