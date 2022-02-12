if not libs then libs = {} end
if not libs.vma then
	libs.vma = {
		name       = "",
		location   = ""
	}
end

local vma = libs.vma

require("vulkan")

function vma:setup()
	self.name     = common:projectName()
	self.location = common:projectLocation()

	kind("StaticLib")
	common:outDirs(true)

	includedirs({ self.location .. "/include/" })

	filter("system:windows")
		removedefines({ "NOMINMAX", "WIN32_LEAN_AND_MEAN" })

	filter({})

	libs.vulkan:setupDep(true)

	files({
		self.location .. "/include/**",
		self.location .. "/src/VmaUsage.h",
		self.location .. "/src/VmaUsage.cpp"
	})
end

function vma:setupDep()
	links({ self.name })
	sysincludedirs({ self.location .. "/include/" })
end