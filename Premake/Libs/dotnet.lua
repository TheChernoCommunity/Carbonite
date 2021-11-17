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
			local result, errorCode = os.outputof("where dotnet.exe")
			if not result then
				error([[You don't seem to have dotnet 6.0 downloaded and installed.
Please visit this download page and if your system isn't on the list you'll have to compile yourself.
https://dotnet.microsoft.com/download/dotnet/6.0/runtime]])
			end
			
			self.runtimeDir = path.getdirectory(result)
		end
		dotnetExe = "\"" .. self.runtimeDir .. "\\dotnet.exe\""
	else
		if not self.runtimeDir or #self.runtimeDir == 0 then
			local result, errorCode = os.outputof("whereis dotnet")
			if not result then
				error([[You don't seem to have dotnet 6.0 downloaded and installed.
Please visit this download page and if your system isn't on the list you'll have to compile yourself.
https://dotnet.microsoft.com/download/dotnet/6.0/runtime]])
			end
			
			local realMatch = string.match(result, ".*:%s*(%g+)")
			if not realMatch then
				error([[You don't seem to have dotnet 6.0 downloaded and installed.
Please visit this download page and if your system isn't on the list you'll have to compile yourself.
https://dotnet.microsoft.com/download/dotnet/6.0/runtime]])
			end
			self.runtimeDir = path.getdirectory(realMatch)
		end
		dotnetExe = "\"" .. self.runtimeDir .. "/dotnet\""
	end

	local dotnetOutput, errorCode = os.outputof(dotnetExe .. " --list-runtimes")
	if not dotnetOutput then
		error([[You don't seem to have dotnet 6.0 downloaded and installed.
Please visit this download page and if your system isn't on the list you'll have to compile yourself.
https://dotnet.microsoft.com/download/dotnet/6.0/runtime]])
	end

	local runtimes = string.explode(dotnetOutput, "\n")
	for k, runtime in ipairs(runtimes) do
		local name, versionMajor, versionMinor, versionPatch, path = string.match(runtime, "(%g+)%s*(%d+).(%d+).(%d+)%s*%[(.+)%]")
		if name == "Microsoft.NETCore.App" then
			self.dotnetVersion[1] = 6
			self.dotnetVersion[2] = versionMinor
			self.dotnetVersion[3] = versionPatch
			self.hostDir = self.runtimeDir .. "/host/fxr/" .. versionMajor .. "." .. versionMinor .. "." .. versionPatch
			self.sharedDir = path .. "/" .. versionMajor .. "." .. versionMinor .. "." .. versionPatch
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
	
	prelinkcommands({ "{COPYDIR} " .. self.sharedDir .. " %{cfg.linktarget.directory}" })
end

-- Override Visual Studio CSharp project generator to fix output directories

require('vstudio')

local cs2005 = premake.vstudio.cs2005
local dotnetbase = premake.vstudio.dotnetbase

dotnetbase.outputProps = function(cfg)
	local outdir = premake.vstudio.path(cfg, cfg.buildtarget.directory)
	local objdir = premake.vstudio.path(cfg, cfg.objdir)
	_x(2, '<BaseOutputPath>%s\\</BaseOutputPath>', outdir)
	_x(2, '<BaseIntermediateOutputPath>%s\\</BaseIntermediateOutputPath>', objdir)
end

cs2005.elements.projectProperties = function(cfg)
	if dotnetbase.isNewFormatProject(cfg) then
		return {
			dotnetbase.outputType,
			dotnetbase.appDesignerFolder,
			dotnetbase.rootNamespace,
			dotnetbase.assemblyName,
			dotnetbase.netcore.targetFramework,
			dotnetbase.allowUnsafeBlocks,
			dotnetbase.fileAlignment,
			dotnetbase.bindingRedirects,
			dotnetbase.netcore.useWpf,
			dotnetbase.csversion,
			dotnetbase.outputProps,
			dotnetbase.netcore.enableDefaultCompileItems,
		}
	else
		return {
			dotnetbase.configurationCondition,
			dotnetbase.platformCondition,
			dotnetbase.productVersion,
			dotnetbase.schemaVersion,
			dotnetbase.projectGuid,
			dotnetbase.outputType,
			dotnetbase.appDesignerFolder,
			dotnetbase.rootNamespace,
			dotnetbase.assemblyName,
			dotnetbase.targetFrameworkVersion,
			dotnetbase.targetFrameworkProfile,
			dotnetbase.fileAlignment,
			dotnetbase.bindingRedirects,
			dotnetbase.projectTypeGuids,
			dotnetbase.csversion,
		}
	end
end
cs2005.elements.configuration = function()
	return {
		dotnetbase.propertyGroup,
		dotnetbase.debugProps,
		dotnetbase.compilerProps,
		dotnetbase.NoWarn
	}
end

return dotnet