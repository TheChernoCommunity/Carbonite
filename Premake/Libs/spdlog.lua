local spdlog = {
	name = "",
	location = ""
}

function spdlog:setup()
	self.name = common:projectName()
	self.location = common:projectLocation()

	kind("StaticLib")
	common:staticLibOutDirs()

	defines({ "SPDLOG_COMPILED_LIB" })

	sysincludedirs({ "%{prj.location}/include/" })
	includedirs({ "%{prj.location}/include/" })

	files({
		"%{prj.location}/include/**",
		"%{prj.location}/src/**"
	})
end

function spdlog:setupDep()
	links({ self.name })
	sysincludedirs({ self.location .. "/include/" })

	defines({ "SPDLOG_COMPILED_LIB" })
end

return spdlog
