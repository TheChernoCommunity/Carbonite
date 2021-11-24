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

	sysincludedirs({ self.location .. "/include/" })
	includedirs({ self.location .. "/include/" })

	files({
		self.location .. "/include/**",
		self.location .. "/src/**"
	})
end

function spdlog:setupDep()
	links({ self.name })
	sysincludedirs({ self.location .. "/include/" })

	defines({ "SPDLOG_COMPILED_LIB" })
end

return spdlog
