local mono = {
	name = "",
	location = "",
	requiredLibs = nil,
	requiredNativeLibs = nil,
	requiredRuntimeLibs = nil
}

function mono:getRequiredLibs()
	if common.host == "windows" then
		mono.requiredLibs = {
			static = {
				"monosgen-2.0",
				"mono-component-debugger-static",
				"mono-component-diagnostics_tracing-static",
				"mono-component-hot_reload-static",
				"mono-profiler-aot",
				"coreclr.import"
			},
			shared = {
				"coreclr"
			}
		}
	else
		mono.requiredLibs = {
			static = {
				"monosgen-2.0",
				"mono-component-debugger-static",
				"mono-component-diagnostics_tracing-static",
				"mono-component-hot_reload-static",
				"mono-profiler-aot"
			},
			shared = {
				"coreclr"
			}
		}
	end
end

function mono:getRequiredRuntimeLibs()
    mono.requiredNativeLibs = {
        "System.Globalization.Native",
        "System.IO.Compression.Native",
        "System.IO.Ports.Native",
        "System.Native",
        "System.Net.Security.Native",
        "System.Security.Cryptography.Native.OpenSsl"
    }
	mono.requiredRuntimeLibs = {
		"Microsoft.CSharp",
		"System",
		"System.AppContext",
		"System.Buffers",
		"System.Collections",
		"System.Collections.Concurrent",
		"System.Collections.Immutable",
		"System.Collections.NonGeneric",
		"System.Collections.Specialized",
		"System.ComponentModel",
		"System.ComponentModel.Annotations",
		"System.ComponentModel.DataAnnotations",
		"System.ComponentModel.EventBasedAsync",
		"System.ComponentModel.Primitives",
		"System.ComponentModel.TypeConverter",
		"System.Core",
		"System.Data",
		"System.Data.Common",
		"System.Data.DataSetExtensions",
		"System.Diagnostics.Contracts",
		"System.Diagnostics.Debug",
		"System.Diagnostics.DiagnosticSource",
		"System.Diagnostics.FileVersionInfo",
		"System.Diagnostics.Process",
		"System.Diagnostics.StackTrace",
		"System.Diagnostics.TextWriterTraceListener",
		"System.Diagnostics.Tools",
		"System.Diagnostics.TraceSource",
		"System.Diagnostics.Tracing",
		"System.Dynamic.Runtime",
		"System.Formats.Asn1",
		"System.Globalization",
		"System.Globalization.Extensions",
		"System.IO",
		"System.IO.Compression",
		"System.IO.Compression.Brotli",
		"System.IO.Compression.FileSystem",
		"System.IO.Compression.ZipFile",
		"System.IO.FileSystem",
		"System.IO.FileSystem.AccessControl",
		"System.IO.FileSystem.Primitives",
		"System.IO.FileSystem.Watcher",
		"System.IO.IsolatedStorage",
		"System.IO.MemoryMappedFiles",
		"System.IO.Pipes",
		"System.IO.Pipes.AccessControl",
		"System.IO.UnmanagedMemoryStream",
		"System.Linq",
		"System.Linq.Expressions",
		"System.Linq.Parallel",
		"System.Linq.Queryable",
		"System.Memory",
		"System.Net",
		"System.Net.Http",
		"System.Net.Http.Json",
		"System.Net.HttpListener",
		"System.Net.Mail",
		"System.Net.NameResolution",
		"System.Net.NetworkInformation",
		"System.Net.Ping",
		"System.Net.Primitives",
		"System.Net.Quic",
		"System.Net.Requests",
		"System.Net.Security",
		"System.Net.ServicePoint",
		"System.Net.Sockets",
		"System.Net.WebClient",
		"System.Net.WebHeaderCollection",
		"System.Net.WebProxy",
		"System.Net.WebSockets",
		"System.Net.WebSockets.Client",
		"System.Numerics",
		"System.Numerics.Vectors",
		"System.ObjectModel",
		"System.Private.DataContractSerialization",
		"System.Private.Uri",
		"System.Private.Xml",
		"System.Private.Xml.Linq",
		"System.Reflection",
		"System.Reflection.DispatchProxy",
		"System.Reflection.Emit",
		"System.Reflection.Emit.ILGeneration",
		"System.Reflection.Emit.Lightweight",
		"System.Reflection.Extensions",
		"System.Reflection.Metadata",
		"System.Reflection.Primitives",
		"System.Reflection.TypeExtensions",
		"System.Resources.Reader",
		"System.Resources.ResourceManager",
		"System.Resources.Writer",
		"System.Runtime",
		"System.Runtime.CompilerServices.Unsafe",
		"System.Runtime.Extensions",
		"System.Runtime.Handles",
		"System.Runtime.InteropServices",
		"System.Runtime.InteropServices.RuntimeInformation",
		"System.Runtime.Intrinsics",
		"System.Runtime.Loader",
		"System.Runtime.Numerics",
		"System.Runtime.Serialization",
		"System.Runtime.Serialization.Formatters",
		"System.Runtime.Serialization.Json",
		"System.Runtime.Serialization.Primitives",
		"System.Runtime.Serialization.Xml",
		"System.Security",
		"System.Security.AccessControl",
		"System.Security.Claims",
		"System.Security.Cryptography.Algorithms",
		"System.Security.Cryptography.Cng",
		"System.Security.Cryptography.Csp",
		"System.Security.Cryptography.Encoding",
		"System.Security.Cryptography.OpenSsl",
		"System.Security.Cryptography.Primitives",
		"System.Security.Cryptography.X509Certificates",
		"System.Security.Principal",
		"System.Security.Principal.Windows",
		"System.Security.SecureString",
		"System.ServiceModel.Web",
		"System.ServiceProcess",
		"System.Text.Encoding",
		"System.Text.Encoding.CodePages",
		"System.Text.Encoding.Extensions",
		"System.Text.Encodings.Web",
		"System.Text.Json",
		"System.Text.RegularExpressions",
		"System.Threading",
		"System.Threading.Channels",
		"System.Threading.Overlapped",
		"System.Threading.Tasks",
		"System.Threading.Tasks.Dataflow",
		"System.Threading.Tasks.Extensions",
		"System.Threading.Tasks.Parallel",
		"System.Threading.Thread",
		"System.Threading.ThreadPool",
		"System.Threading.Timer",
		"System.Transactions",
		"System.Transactions.Local",
		"System.ValueTuple",
		"System.Web",
		"System.Web.HttpUtility",
		"System.Xml",
		"System.Xml.Linq",
		"System.Xml.ReaderWriter",
		"System.Xml.Serialization",
		"System.Xml.XDocument",
		"System.Xml.XmlDocument",
		"System.Xml.XmlSerializer",
		"System.Xml.XPath",
		"System.Xml.XPath.XDocument"
	}
end

function mono:toMonoLibraries(libraries)
	local out = {}
	
	for _, v in ipairs(libraries) do
		table.insert(out, v .. ".dll")
		table.insert(out, v .. ".pdb")
	end
	
	return out
end

function mono:toMonoOS(name)
	if name == "macosx" then
		return "OSX"
	else
		return name
	end
end

function mono:toMonoOSShort(name)
	if name == "windows" then
		return "win"
	elseif name == "macosx" then
		return "osx"
	else
		return name
	end
end

function mono:toMonoArch(name)
	if name == "amd64" then
		return "x64"
	elseif name == "arm32" then
		return "arm"
	else
		return name
	end
end

function mono:toMonoConfig(name)
	if name == "Dist" then
		return "Release"
	else
		return name
	end
end

function mono:toMonoRID(platform, arch)
	return self:toMonoOSShort(platform) .. "-" .. self:toMonoArch(arch)
end

function mono:toMonoTriple(platform, arch, config)
	return self:toMonoOS(platform) .. "." .. self:toMonoArch(arch) .. "." .. self:toMonoConfig(config)
end

function mono:validate(secondRun)
	if secondRun == nil then secondRun = false end
	local next = next

	local missingTriples = {}
	for _, arch in ipairs(common.targetArchs) do
		local missingTriple = {}
		for _, config in ipairs({ "Debug", "Release" }) do
			local missing = {
				hasFolder = false,
				missingLibs = {}
			}
			
			local folder = self.location .. "/Backends/" .. self:toMonoTriple(common.target, arch, config) .. "/"
			if os.isdir(folder) then
				missing.hasFolder = true
				
				local searchPath = folder .. "lib/"
				for _, v in ipairs(self.requiredLibs.static) do
					if not common:hasLib(v, { searchPath }) then
						table.insert(missing.missingLibs, v)
					end
				end
				
				searchPath = folder .. "bin/"
				for _, v in ipairs(self.requiredLibs.shared) do
					if not common:hasSharedLib(v, { searchPath }) then
						table.insert(missing.missingLibs, v)
					end
				end

				for _, v in ipairs(self.requiredNativeLibs) do
				    if not common:hasSharedLib(v, searchPath) then
				        table.insert(missing.missingLibs, v)
				    end
				end
				
				if not os.isfile(searchPath .. "System.Private.CoreLib.dll") or not os.isfile(searchPath .. "System.Private.CoreLib.pdb") then
					table.insert(missing.missingLibs, "System.Private.CoreLib")
				end
			end
			
			if not missing.hasFolder or #missing.missingLibs > 0 then
				missingTriple[config] = missing
			end
		end
		if next(missingTriple) ~= nil then
			missingTriples[arch] = missingTriple
		end
	end
	
	local missingNETLibraries = { hasFolder = true, missingLibs = {} }
	if not os.isdir(self.location .. "/.NET/") then
		missingNETLibraries.hasFolder = false
	else
		for _, v in ipairs(self.requiredRuntimeLibs) do
			if not os.isfile(self.location .. "/.NET/" .. v .. ".dll") or not os.isfile(self.location .. "/.NET/" .. v .. ".pdb") then
				table.insert(missingNETLibraries.missingLibs, v)
			end
		end
	end
	
	if next(missingTriples) ~= nil or not missingNETLibraries.hasFolder or #missingNETLibraries.missingLibs > 0 then
		local message = "!! Setup required !!\n"
		if next(missingTriples) ~= nil then
			message = message .. "Missing mono libraries\n"
			for arch, configs in pairs(missingTriples) do
				for config, missing in pairs(configs) do
					if missing.hasFolder then
						message = message .. "Incomplete '" .. self:toMonoTriple(common.target, arch, config) .. "' missing:\n"
						for _, lib in ipairs(missing.missingLibs) do
							message = message .. "\t" .. lib .. "\n"
						end
					else
						message = message .. "Folder '" .. self:toMonoTriple(common.target, arch, config) .. "' is missing.\n"
					end
				end
			end
		end
		
		if not missingNETLibraries.hasFolder then
			message = message .. "Missing .NET libraries\n"
		elseif #missingNETLibraries.missingLibs > 0 then
			message = message .. "Incomplete .NET libraries\n"
			for _, lib in ipairs(missingNETLibraries.missingLibs) do
				message = message .. "\t" .. lib .. "\n"
			end
		end
		
		local canAutomaticallyBuild = not secondRun and common.host == common.target
		if canAutomaticallyBuild and common.target == "windows" then
			for arch, configs in pairs(missingTriples) do
				if arch ~= common.arch then
					canAutomaticallyBuild = false
				end
			end
		end
		local built = false
		message = message .. "Please go clone https://github.com/dotnet/runtime\nCurrently Carbonite uses the release/6.0 branch with 'git checkout release/6.0'\n"
		term.pushColor(term.green)
		print(message)
		term.popColor()
		if canAutomaticallyBuild then
			io.write("Should premake setup everything automatically (Y/N)? ")
			local result = io.read()
			local firstChar = result:sub(1,1)
			if result:len() > 0 and (firstChar == "Y" or firstChar == "y") then
				print("Where's the repository downloaded to?")
				local repo = io.read("*line")
				
				local failed = false
				local failureMessage = ""
				
				local commandBase
				if common.target == "windows" then
					commandBase = repo .. "\\build.cmd"
				else
					commandBase = repo .. "/build.sh"
				end
				
				local subsets = {
					triple = {
						"Mono",
						"Clr.Native",
						"Libs.Native"
					},
					libs = {
						"Clr",
						"Host",
						"Libs" -- TOOD(MarcasRealAccount): Find bare minimum subsets for the managed assemblies
					}
				}
				local dotnetVersion = "net6.0" -- TODO(MarcasRealAccount): Get this from the build somehow
				for arch, configs in pairs(missingTriples) do
					for config, missing in pairs(configs) do
						local args = " -a " .. self:toMonoArch(arch) .. " -rf Mono -lc " .. config .. " -rc " .. config .. " -c " .. config
						local monoRID = nil
						local monoArtifact = nil
						local monoBackend = nil
						local ok, err = nil, nil
						
						for _, subset in ipairs(subsets.triple) do
							command = commandBase .. " " .. subset .. args
							if not os.execute(command) then
								goto failed
							end
						end
						
						monoTriple = self:toMonoTriple(common.target, arch, config)
						monoObjArtifact = repo .. "/artifacts/obj/mono/" .. monoTriple .. "/out/"
						monoBinArtifact = repo .. "/artifacts/bin/mono/" .. monoTriple .. "/"
						nativeBinArtifact = repo .. "/artifacts/bin/native/" .. dotnetVersion .. "-" .. self:toMonoOS(common.target) .. "-" .. self:toMonoConfig(config) .. "-" .. self:toMonoArch(arch) .. "/"
						monoBackend = self.location .. "/Backends/" .. monoTriple .. "/"
						
						code, err = common:rmdir(monoBackend)
						if code < 0 then goto copyFailure end
						code, err = common:copyDir(monoObjArtifact .. "include/mono-2.0/", monoBackend .. "/include/")
						if code < 0 then goto copyFailure end
						code, err = common:copyFiles(monoObjArtifact .. "lib/", common:libname(self.requiredLibs.static), monoBackend .. "/lib/")
						if code < 0 then goto copyFailure end
						code, err = common:copyFiles(monoBinArtifact, { common:sharedlibname("coreclr"), "System.Private.CoreLib.dll", "System.Private.CoreLib.pdb" }, monoBackend .. "/bin/")
						if code < 0 then goto copyFailure end
						code, err = common:copyFiles(nativeBinArtifact, common:sharedlibname(self.requiredNativeLibs, true), monoBackend .. "/bin/")
						if code < 0 then goto copyFailure end
						
						goto continue
						
						::failed::
						failed = true
						failureMessage = failureMessage .. "\"" .. command .. "\" failed to build\n"
						goto continue
						
						::copyFailure::
						failed = true
						failureMessage = failureMessage .. "Copy failed with " .. code .. " '" .. err .. "'\n"
						
						::continue::
					end
				end
				
				if not missingNETLibraries.hasFolder or #missingNETLibraries.missingLibs > 0 then
					local code, err = nil, nil
					local rid = nil
					for _, subset in ipairs(subsets.libs) do
						command = commandBase .. " " .. subset .. " -a " .. self:toMonoArch(common.targetArchs[1]) .. " -rf Mono -lc Release -rc Release -c Release"
						if not os.execute(command) then
							goto failed
						end
					end
					
					common:rmdir(self.location .. "/.NET/")
					code, err = common:mkdirs(self.location .. "/.NET/")
					if code < 0 then goto copyFailure end
					rid = self:toMonoRID(common.target, common.targetArchs[1])
					code, err = common:copyFiles(repo .. "/artifacts/bin/microsoft.netcore.app.runtime." .. rid .. "/Release/runtimes/" .. rid .. "/lib/" .. dotnetVersion .. "/", self:toMonoLibraries(self.requiredRuntimeLibs), self.location .. "/.NET/")
					if code < 0 then goto copyFailure end
					
					goto continue
					
					::failed::
					failed = true
					failureMessage = failureMessage .. "\"" .. command .. "\" failed to build\n"
					goto continue
					
					::copyFailure::
					failed = true
					failureMessage = failureMessage .. "Copy failed with " .. code .. " '" .. err .. "'\n"
					
					::continue::
				end
				built = not failed
				
				term.pushColor(term.red)
				print(failureMessage)
				term.popColor()
			end
		end
		
		if not built then
			if common.target == "windows" then
				message = [[Please head over to the repository directory and run:
"build.bat mono -c Debug,Release -cmakeargs -DDISABLE_AOT=1" on the target machine,
Mono's script fails to build for Windows x86 on a x64 machine because cmake's FindPython3 library can't find python3 as
it doesn't see the x64 version as a valid python3 install.
]]
			else
				message = [[Please head over to the repository directory and run:
build.sh mono -a x86 -c Debug -cmakeargs -DDISABLE_AOT=1 && \
build.sh mono -a x86 -c Release -cmakeargs -DDISABLE_AOT=1 && \
build.sh mono -a x64 -c Debug -cmakeargs -DDISABLE_AOT=1 && \
build.sh mono -a x64 -c Release -cmakeargs -DDISABLE_AOT=1 && \
build.sh mono -a arm -c Debug -cmakeargs -DDISABLE_AOT=1 && \
build.sh mono -a arm -c Release -cmakeargs -DDISABLE_AOT=1 && \
build.sh mono -a arm64 -c Debug -cmakeargs -DDISABLE_AOT=1 && \
build.sh mono -a arm64 -c Release -cmakeargs -DDISABLE_AOT=1
Just build the Debug and Release lines for the architecture of your choosing.
Cross compilation could be done by adding -cross and -os <os> but that requires a bit of work
]]
			end
			
			message = message .. [[
Now open 'artifacts/obj/mono/' and copy the '<os>.<arch>.<config>/' folders you just built into 'ThirdParty/mono/Backends/'
Then move the contents of '<os>.<arch>.<config>/out/' into '<os>.<arch>.<config>/'
(P.S it is completely safe to delete all the other folders inside it, as well as the 'out/include/' folder)]]
			
			term.pushColor(term.red)
			print(message)
			term.popColor()
			error("^")
		else
			self:validate(true)
		end
	end
end

function mono:setup()
	self.name = common:projectName()
	self.location = common:projectLocation()
	
	self:validate()
	
	kind("Utility")
	
	for _, arch in ipairs(common.targetArchs) do
		for _, config in ipairs({ "Debug", "Release", "Dist" }) do
			files({ self.location .. "/Backends/" .. self:toMonoTriple(common.target, arch, config) .. "/include/**" })
		end
	end
end

function mono:setupDep()
	for _, arch in ipairs(common.targetArchs) do
		for _, config in ipairs({ "Debug", "Release", "Dist" }) do
			local native = self.location .. "/Backends/" .. self:toMonoTriple(common.target, arch, config)
			filter({ "architecture:" .. arch, "configurations:" .. config })
				sysincludedirs({ native .. "/include/" })
				libdirs({
				    native .. "/bin/",
				    native .. "/lib/"
				})
			
				prelinkcommands({
					"{COPYDIR} \"" .. native .. "/bin/\" \"%{cfg.linktarget.directory}/\"",
					"{COPYDIR} \"" .. self.location .. "/.NET/\" \"%{cfg.linktarget.directory}/.NET/\""
				})
		end
	end
	
	filter({})
	
	links(self.requiredLibs.static)
	if common.target == "windows" then
		links({
			"ws2_32",
			"Winmm"
		})
	else
		links(self.requiredLibs.shared)
	end
end

mono:getRequiredLibs()
mono:getRequiredRuntimeLibs()

return mono
