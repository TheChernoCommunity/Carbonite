local common = {
	binDir = "%{wks.location}/Bin/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/",
	objDir = "%{wks.location}/Bin/Int-%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/",
	host = os.host()
}

function common:executableOutDirs()
	targetdir(self.binDir)
	objdir(self.objDir)
end

function common:sharedLibOutDirs()
	targetdir(self.binDir)
	objdir(self.objDir)
end

function common:staticLibOutDirs()
	targetdir(self.objDir)
	objdir(self.objDir)
end

function common:copyCSharpBinary(project, to, from)
	local copy
	local isVS = _ACTION == "vs2017" or _ACTION == "vs2019" or _ACTION == "vs2022"
	if isVS then
		if common.host == "windows" then
			copy = "mkdir %{wks.location}/" .. path.getdirectory(to) .. " && copy /B /Y "
		else
			copy = "mkdir -p %{wks.location}/" .. path.getdirectory(to) .. " && cp -f "
		end
	else
		copy = "{MKDIR} %{wks.location}/" .. path.getdirectory(to) .. " && {COPYFILE} "
	end

	copy = copy .. "%{wks.location}/Bin/Int-%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/" .. project .. "/"
	
	if isVS then
		copy = copy .. "/%{cfg.platform}/%{cfg.buildcfg}/net6.0/"
	else
		copy = copy .. "/"
	end
	
	copy = copy .. from .. " %{wks.location}/" .. to

	return copy
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
	
	if common.host == "windows" then
		prebuildcommands({ "\"" .. _PREMAKE_COMMAND .. "\" \"--file=" .. _MAIN_SCRIPT .. "\" \"--vulkan-sdk=" .. vulkan.sdkPath .. "\" \"--dotnet-runtime-dir=" .. dotnet.runtimeDir .. "\" force-pch" })
	else
		prebuildcommands({ "'" .. _PREMAKE_COMMAND .. "' \"--file=" .. _MAIN_SCRIPT .. "\" \"--vulkan-sdk=" .. vulkan.sdkPath .. "\" \"--dotnet-runtime-dir=" .. dotnet.runtimeDir .. "\" force-pch" })
	end
end

function common:addActions()
	filter("files:**.inl")
		runclangformat(true)

	filter("files:**.h")
		runclangformat(true)

	filter("files:**.cpp")
		runclangformat(true)
		runclangtidy(true)
		allowforcepch(true)

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
