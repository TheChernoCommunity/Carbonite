if not libs then libs = {} end
if not libs.spdlog then
	libs.spdlog = {
		name       = "",
		location   = ""
	}
end

local spdlog = libs.spdlog

function spdlog:setup()
	self.name     = common:projectName()
	self.location = common:projectLocation()

	kind("StaticLib")
	common:outDirs(true)

	defines({ "SPDLOG_COMPILED_LIB", "FMT_CONSTEVAL=" })

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

	defines({ "SPDLOG_COMPILED_LIB", "FMT_CONSTEVAL=" })
end