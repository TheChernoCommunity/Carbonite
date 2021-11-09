local vma = {
	sourceDir = "/src/",
	includeDir = "/include/",
	name = "",
	location = ""
}

function vma:setup()
	self.name = common:projectName()
	self.location = common:projectLocation()

	kind("StaticLib")
	common:staticLibOutDirs()

	includedirs({ "%{prj.location}/include/" })
	
	filter("system:windows")
		removedefines({ "NOMINMAX", "WIN32_LEAN_AND_MEAN" })

	filter({})

	vulkan:setupDep(true)

	files({
		"%{prj.location}" .. self.includeDir .. "**",
		"%{prj.location}" .. self.sourceDir .. "VmaUsage.h",
		"%{prj.location}" .. self.sourceDir .. "VmaUsage.cpp"
	})
end

function vma:setupDep()
	links({ self.name })
	sysincludedirs({ self.location .. self.includeDir })
end

return vma