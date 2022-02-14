local mono = libs.mono

mono.subsets = {
	triple = {
		"Mono",
		"Clr.Native",
		"Libs.Native"
	},
	libs = {
		"Clr",
		"Host",
		"Libs"
	}
}

function mono:getTriplesBuildCommand(arch, config)
	local tripleSubsets = ""
	for _, v in ipairs(mono.subsets.triple) do
		if tripleSubsets:len() > 0 then tripleSubsets = tripleSubsets .. "+" end
		tripleSubsets = tripleSubsets .. v
	end

	return tripleSubsets .. " -a " .. self:toMonoArch(arch) .. " -rf Mono -lc " .. config .. " -rc " .. config .. " -c " .. config
end

function mono:getNETBuildCommand()
	local libsSubsets = ""
	for _, v in ipairs(mono.subsets.libs) do
		if libsSubsets:len() > 0 then
			libsSubsets = libsSubsets .. "+"
		end
		libsSubsets = libsSubsets .. v
	end

	return libsSubsets .. " -a " .. self:toMonoArch(common.targetArchs[1]) .. " -rf Mono -lc Release -rc Release -c Release"
end

function mono:getBuildCommands(missingTriples, missingNETLibraries)
	local commands = {}
	
	local tripleSubsets = ""
	local libsSubsets   = ""
	for _, v in ipairs(mono.subsets.triple) do
		if tripleSubsets:len() > 0 then tripleSubsets = tripleSubsets .. "+" end
		tripleSubsets = tripleSubsets .. v
	end
	for _, v in ipairs(mono.subsets.libs) do
		if libsSubsets:len() > 0 then
			libsSubsets = libsSubsets .. "+"
		end
		libsSubsets = libsSubsets .. v
	end
	for arch, configs in pairs(missingTriples) do
		for config, missing in pairs(configs) do
			table.insert(commands, tripleSubsets .. " -a " .. self:toMonoArch(arch) .. " -rf Mono -lc " .. config .. " -rc " .. config .. " -c " .. config)
		end
	end
	
	if not missingNETLibraries.hasFolder or #missingNETLibraries.missingLibs > 0 then
		table.insert(commands, libsSubsets .. " -a " .. self:toMonoArch(common.targetArchs[1]) .. " -rf Mono -lc Release -rc Release -c Release")
	end
	
	return commands
end

function mono:buildMono(repoDir, dotnetVersion, missingTriples, missingNETLibraries)
	local failed         = false
	local failureMessage = ""

	local commandBase
	if common.target == "windows" then
		commandBase = "\"" .. repoDir .. "\\build.cmd\" "
	else
		commandBase = "'" .. repoDir .. "/build.sh' "
	end
	
	for arch, configs in pairs(missingTriples) do
		for config, missing in pairs(configs) do
			local monoTriple        = nil
			local monoObjArtifact   = nil
			local monoBinArtifact   = nil
			local nativeBinArtifact = nil
			local monoBackend       = nil
			local code, err         = nil, nil
			
			local command = commandBase .. self:getTriplesBuildCommand(arch, config)
			if not os.execute(command) then
				goto failed
			end
			
			monoTriple        = self:toMonoTriple(common.target, arch, config)
			monoObjArtifact   = repoDir .. "/artifacts/obj/mono/" .. monoTriple .. "/out/"
			monoBinArtifact   = repoDir .. "/artifacts/bin/mono/" .. monoTriple .. "/"
			nativeBinArtifact = repoDir .. "/artifacts/bin/native/" .. dotnetVersion .. "-" .. self:toMonoOS(common.target) .. "-" .. self:toMonoConfig(config) .. "-" .. self:toMonoArch(arch) .. "/"
			monoBackend       = self.location .. "/Backends/" .. monoTriple .. "/"
			
			code, err = common:rmdir(monoBackend)
			if code < 0 then goto copyFailure end
			code, err = common:copyDir(monoObjArtifact .. "include/mono-2.0/", monoBackend .. "/include/")
			if code < 0 then goto copyFailure end
			code, err = common:copyFiles(monoObjArtifact .. "lib/", common:libName(self.requiredLibs.static), monoBackend .. "/lib/")
			if code < 0 then goto copyFailure end
			code, err = common:copyFiles(monoBinArtifact, { common:sharedLibName("coreclr"), "System.Private.CoreLib.dll", "System.Private.CoreLib.pdb" }, monoBackend .. "/bin/")
			if code < 0 then goto copyFailure end
			code, err = common:copyFiles(nativeBinArtifact, common:sharedLibName(self.requiredNativeLibs, true), monoBackend .. "/bin/")
			if code < 0 then goto copyFailure end
			
			goto continue
			
			::failed::
			failed         = true
			failureMessage = failureMessage .. "\"" .. command .. "\" failed to build\n"
			goto continue
			
			::copyFailure::
			failed         = true
			failureMessage = failureMessage .. "Copy failed with " .. code .. " '" .. err .. "'\n"
			
			::continue::
		end
	end
	
	if not missingNETLibraries.hasFolder or #missingNETLibraries.missingLibs > 0 then
		local monoRID   = nil
		local code, err = nil, nil
		
		local command = commandBase .. self:getNETBuildCommand()
		if not os.execute(command) then
			goto failed
		end
		
		common:rmdir(self.location .. "/.NET/")
		monoRID = self:toMonoRID(common.target, common.targetArchs[1])
		code, err = common:copyFiles(repoDir .. "/artifacts/bin/microsoft.netcore.app.runtime." .. monoRID .. "/Release/runtimes/" .. monoRID .. "/lib/" .. dotnetVersion .. "/", self:toMonoLibraries(self.requiredRuntimeLibs), self.location .. "/.NET/")
		if code < 0 then goto copyFailure end
		
		goto continue
		
		::failed::
		failed         = true
		failureMessage = failureMessage .. "\"" .. command .. "\" failed to build\n"
		goto continue
		
		::copyFailure::
		failed         = true
		failureMessage = failureMessage .. "Copy failed with " .. code .. " '" .. err .. "'\n"
		
		::continue::
	end
	
	if failed then
		term.pushColor(term.errorColor)
		print(failureMessage)
		term.popColor()
	end

	return not failed
end