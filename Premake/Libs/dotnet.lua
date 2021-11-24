local dotnet = {
	runtimeDir = "",
	dotnetVersion = { 0, 0, 0 },
	hostDir = "",
	sharedDir = ""
}

newoption({
	trigger = "dotnet-runtime-dir",
	description = "Overrides DOTNET_RUNTIME_DIR environment variable",
	value = "path",
	default = os.getenv("DOTNET_RUNTIME_DIR")
})

function dotnet:getDotNet()
	self.runtimeDir = _OPTIONS["dotnet-runtime-dir"]

	local dotnetExe
	if common.host == "windows" then
		if not self.runtimeDir or #self.runtimeDir == 0 then
			dotnetExe = "dotnet.exe"
		else
			dotnetExe = "\"" .. self.runtimeDir .. "\\dotnet.exe\""
		end
	else
		if not self.runtimeDir or #self.runtimeDir == 0 then
			dotnetExe = "dotnet"
		else
			dotnetExe = "'" .. self.runtimeDir .. "/dotnet'"
		end
	end

	local dotnetOutput, errorCode = os.outputof(dotnetExe .. " --list-runtimes")
	if not dotnetOutput then
		error([[You don't seem to have dotnet 6.0 downloaded and installed.
Please visit this download page and if your system isn't on the list you'll have to compile yourself.
https://dotnet.microsoft.com/download/dotnet/6.0/runtime]])
	end

	local runtimes = string.explode(dotnetOutput, "\n")
	for k, runtime in ipairs(runtimes) do
		local name, versionMajor, versionMinor, versionPatch, runtimePath = string.match(runtime, "(%g+)%s*(%d+).(%d+).(%d+)%s*%[(.+)%]")
		if name == "Microsoft.NETCore.App" then
			self.dotnetVersion[1] = 6
			self.dotnetVersion[2] = versionMinor
			self.dotnetVersion[3] = versionPatch
			self.runtimeDir = path.getabsolute("../../", runtimePath)
			self.hostDir = self.runtimeDir .. "/host/fxr/" .. versionMajor .. "." .. versionMinor .. "." .. versionPatch
			self.sharedDir = runtimePath .. "/" .. versionMajor .. "." .. versionMinor .. "." .. versionPatch
		end
	end
end

dotnet:getDotNet()

function dotnet:setupDep()
	if common.host == "windows" then
		prelinkcommands({ "{COPYFILE} " .. self.hostDir .. "/hostfxr.dll %{cfg.linktarget.directory}/hostfxr.dll" })
	elseif common.host == "macosx" then
		prelinkcommands({ "{COPYFILE} " .. self.hostDir .. "/libhostfxr.dylib %{cfg.linktarget.directory}/libhostfxr.dylib" })
	else
		prelinkcommands({ "{COPYFILE} " .. self.hostDir .. "/libhostfxr.so %{cfg.linktarget.directory}/libhostfxr.so" })
	end
end

return dotnet
