local common = {
	binDir = "%{wks.location}/Bin/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/",
	objDir = "%{wks.location}/Bin/Int-%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/",
	host = os.host()
}

function common:executableOutDirs()
	targetdir(self.binDir)
	objdir(self.objDir)
end

function common:sharedLibOutDirs(isCSharp)
	targetdir(self.binDir)
	objdir(self.objDir)
end

function common:staticLibOutDirs()
	targetdir(self.objDir)
	objdir(self.objDir)
end

function common:modOutDirs()
	local projectName = self:projectName()
	targetdir("%{wks.location}/Carbonite/Run/Base/")
	objdir(self.objDir)
end

function common:debugDir()
	if _ACTION == "xcode4" then
		local projectName = self:projectName()
		local projectLocation = self:projectLocation()
		
		print([[xcode4 action doesn't support using debug directory.
So you have to edit the scheme of ']] .. projectName .. [[' (Top center) to use this as the debug directory:
]] .. projectLocation .. "/Run")
	elseif _ACTION == "gmake2" then
		local projectName = self:projectName()
		local projectLocation = self:projectLocation()
		
		print([[gmake2 action doesn't support using debug directory.
So you have to manually 'cd' into the debug directory:
]] .. projectLocation .. "/Run")
	end

	debugdir("%{prj.location}/Run/")
end

function common:addPCH(source, header)
	pchsource(source)
	filter("action:xcode4")
		pchheader(header)

	filter("action:not xcode4")
		pchheader(path.getname(header))

	filter({})
end

function common:addCoreDefines()
	filter("configurations:Debug")
		defines({ "CARBONITE_CONFIG=CARBONITE_CONFIG_DEBUG" })
		optimize("Off")
		symbols("On")

	filter("configurations:Release")
		defines({ "CARBONITE_CONFIG=CARBONITE_CONFIG_RELEASE" })
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
			"NOMINMAX", -- Windows.h disables
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
end

function common:setConfigsAndPlatforms()
	configurations({ "Debug", "Release", "Dist" })
	platforms({ "x64" })
end

function common:projectName()
	return premake.api.scope.current.name
end

function common:projectLocation()
	return premake.api.scope.current.current.location
end

function common:hasLib(lib, searchPaths)
	for _, searchPath in ipairs(searchPaths) do
		return #os.matchfiles(searchPath .. "/*" .. lib .. ".*") > 0
	end
	return false
end

return common