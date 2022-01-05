local dotnet = {
	runtimeDir = "",
	dotnetVersion = "",
	sdkRuntimeIdentifier = "",
	hostDir = ""
}

newoption({
	trigger = "dotnet-runtime-dir",
	description = "Overrides DOTNET_RUNTIME_DIR environment variable",
	value = "path",
	default = os.getenv("DOTNET_RUNTIME_DIR")
})

function dotnet:getDotNet()
	self.runtimeDir = _OPTIONS["dotnet-runtime-dir"]
	if self.runtimeDir then
		self.runtimeDir = path.translate(self.runtimeDir, "/")
	end

	local dotnetExe
	if common.host == "windows" then
		if not self.runtimeDir or #self.runtimeDir == 0 then
			dotnetExe = "dotnet.exe"
		else
			dotnetExe = "\"" .. path.translate(self.runtimeDir, "\\") .. "\\dotnet.exe\""
		end
		self.sdkRuntimeIdentifier = "win-%{cfg.platform}"
	else
		if not self.runtimeDir or #self.runtimeDir == 0 then
			dotnetExe = "dotnet"
		else
			dotnetExe = "'" .. self.runtimeDir .. "/dotnet'"
		end
		
		if common.host == "macosx" then
			self.sdkRuntimeIdentifier = "osx-%{cfg.platform}"
		else
			self.sdkRuntimeIdentifier = "%{cfg.system}-%{cfg.platform}"
		end
	end

	local dotnetOutput, errorCode = os.outputof(dotnetExe .. " --list-runtimes")
	if not dotnetOutput then
		error([[You don't seem to have dotnet 6.0 sdk downloaded and installed.
Please visit this download page and if your system isn't on the list you'll have to compile yourself.
https://dotnet.microsoft.com/download/dotnet/6.0]])
	end

	local runtimes = string.explode(dotnetOutput, "\n")
	for k, runtime in ipairs(runtimes) do
		local name, versionMajor, versionMinor, versionPatch, runtimePath = string.match(runtime, "(%g+)%s*(%d+).(%d+).(%d+)%s*%[(.+)%]")
		local majorVersion = tonumber(versionMajor)
		local minorVersion = tonumber(versionMinor)
		local patchVersion = tonumber(versionPatch)
		if majorVersion >= 6 and name == "Microsoft.NETCore.App" then
			self.dotnetVersion = "6." .. tostring(minorVersion) .. "." ..tostring(patchVersion)
			self.runtimeDir = path.translate(path.getabsolute("../../", runtimePath), "/")
			self.hostDir = string.format("%s/packs/Microsoft.NETCore.App.Host.%s/%s/runtimes/%s/native", self.runtimeDir, self.sdkRuntimeIdentifier, self.dotnetVersion, self.sdkRuntimeIdentifier)
		end
	end

	if not self.runtimeDir then
		error([[Your dotnet install doesn't include the Microsoft.NETCore.App framework with a 6.0.0 or higher version]])
	end
end

dotnet:getDotNet()

function dotnet:setupDep()
	sysincludedirs({ self.hostDir })
	libdirs({ self.hostDir })
	links({ "nethost" })
	if common.host == "windows" then
		prelinkcommands({ "{COPYFILE} \"" .. self.hostDir .. "\\nethost.dll\" \"%{cfg.linktarget.directory}\\nethost.dll\"" })
	elseif common.host == "macosx" then
		prelinkcommands({ "{COPYFILE} \"" .. self.hostDir .. "/libnethost.dylib\" \"%{cfg.linktarget.directory}/libnethost.dylib\"" })
	else
		prelinkcommands({ "{COPYFILE} \"" .. self.hostDir .. "/libnethost.so\" \"%{cfg.linktarget.directory}/libnethost.so\"" })
	end
end

return dotnet
