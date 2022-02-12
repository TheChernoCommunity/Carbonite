local mono = libs.mono

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
					if not common:hasLib(v, searchPath) then
						table.insert(missing.missingLibs, v)
					end
				end

				searchPath = folder .. "bin/"
				for _, v in ipairs(self.requiredLibs.shared) do
					if not common:hasSharedLib(v, searchPath) then
						table.insert(missing.missingLibs, v)
					end
				end

				for _, v in ipairs(self.requiredNativeLibs) do
					if not common:hasSharedLib(v, searchPath) then
						table.insert(missing.missingLibs, v)
					end
				end

				if not os.isfile(searchPath .. "System.Private.CoreLib.dll") or
				   not os.isfile(searchPath .. "System.Private.CoreLib.pdb") then
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

	local missingNETLibraries = {
		hasFolder = true,
		missingLibs = {}
	}
	if not os.isdir(self.location .. "/.NET/") then
		missingNETLibraries.hasFolder = false
	else
		for _, v in ipairs(self.requiredRuntimeLibs) do
			if not os.isfile(self.location .. "/.NET/" .. v .. ".dll") or
			   not os.isfile(self.location .. "/.NET/" .. v .. ".pdb") then
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
						message = message .. "Incomplete '" .. self:toMonoTriple(common.target, arch, config) .. "' is missing:\n"
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
			message = message .. "Incomplete .NET libraries is missing:\n"
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
		term.pushColor(term.warningColor)
		print(message)
		term.popColor()
		term.pushColor(term.infoColor)
		print("Please go clone https://github.com/dotnet/runtime\nCurrently Carbonite uses the release/6.0 branch with 'git checkout release/6.0'\nSo if you encounter any issues with newer versions please open an issue on our github repo\n")
		term.popColor()
		local built = false
		if canAutomaticallyBuild then
			io.write("Should premake setup everything automatically (Y/N)? ")
			local result = io.read()
			local firstChar = result:sub(1, 1)
			if result:len() > 0 and (firstChar == "Y" or firstChar == "y") then
				print("Where's the repository downloaded to?")
				local repo = io.read("*line")
				print("What dotnet version (net6.0)? Not sure then check the repo for some pointers idk.")
				local dotnetVersion = io.read("*line")
				built = self:buildMono(repo, dotnetVersion, missingTriples, missingNETLibraries)
			end
		end

		if built then
			self:validate(true)
		else
			local commands = self:getBuildCommands(missingTriples, missingNETLibraries)
			local commandBase
			if common.target == "windows" then
				commandBase = "build.cmd "
			else
				commandBase = "build.sh "
			end

			message = "Please head over to the repository directory and run:\n"
			for _, v in ipairs(commands) do
				message = message .. commandBase .. v .. "\n"
			end

			if common.target == "windows" then
				message = message .. [[
The build scripts may fail to build for Windows x86 on a x64 machine because cmake's FindPython3 library can't find python3 as
it doesn't see the x64 version as a valid python3 install.]]
			end

			term.pushColor(term.errorColor)
			print(message)
			term.popColor()
			error("^")
		end
	end
end