local formatTidy = {
	formatCommand = "",
	tidyCommand = "",
	canFormat = true,
	canTidy = true
}

local function clangFormatFile(cfg, file)
	if not formatTidy.canFormat then
		return
	end

	local relpath = premake.workspace.getrelative(cfg.workspace, file.abspath)

	os.execute(formatTidy.formatCommand .. " -i " .. relpath)
end

local function list(value, quoted)
	quoted = false
	if #value > 0 then
		if quoted then
			local result = ""
			for _, v in ipairs (value) do
				if #result then
					result = result .. " "
				end
				result = result .. p.quoted(v)
			end
			return result
		else
			return " " .. table.concat(value, " ")
		end
	else
		return ""
	end
end

local function getIncludeDirs(cfg, dirs, sysdirs, frameworkdirs)
	local result = {}
	for _, dir in ipairs(dirs) do
		dir = premake.workspace.getrelative(cfg.project.workspace, dir)
		table.insert(result, "-I" .. premake.quoted(dir))
	end
	for _, dir in ipairs(sysdirs) do
		dir = premake.workspace.getrelative(cfg.project.workspace, dir)
		table.insert(result, "-isystem " .. premake.quoted(dir))
	end
	return result
end

local function getCommandLine(cfg, file)
	local fcfg = premake.fileconfig.getconfig(file, cfg)
	local toolset = premake.tools["clang"]
	local isCFile = path.iscfile(fcfg.name)
	local getflags = iif(isCFile, toolset.getcflags, function(cfg) return table.join(toolset.getcppflags(cfg), toolset.getcxxflags(cfg)) end)
	local value = list(table.join(getflags(cfg), cfg.buildoptions), table.join(getflags(fcfg), fcfg.buildoptions))

	if cfg.defines or cfg.undefines then
		local defs = table.join(toolset.getdefines(cfg.defines, cfg), toolset.getundefines(cfg.undefines))
		if #defs > 0 then
			value = value .. list(defs)
		end
	end

	if cfg.includedirs or cfg.sysincludedirs or cfg.frameworkdirs then
		local includes = getIncludeDirs(cfg, cfg.includedirs, cfg.sysincludedirs, cfg.frameworkdirs)
		if #includes > 0 then
			value = value .. list(includes)
		end
	end

	if fcfg.defines or fcfg.undefines then
		local defs = table.join(toolset.getdefines(fcfg.defines, cfg), toolset.getundefines(fcfg.undefines))
		if #defs > 0 then
			value = value .. list(defs)
		end
	end

	if fcfg.includedirs or fcfg.sysincludedirs or fcfg.frameworkdirs then
		local includes = getIncludeDirs(cfg, fcfg.includedirs, fcfg.sysincludedirs, fcfg.frameworkdirs)
		if #includes > 0 then
			value = value .. list(includes)
		end
	end

	return value
end

local function clangTidyFile(cfg, file)
	if not formatTidy.canTidy then
		return
	end

	local relpath = premake.workspace.getrelative(cfg.workspace, file.abspath)

	os.execute(formatTidy.tidyCommand .. " " .. relpath .. " --" .. getCommandLine(cfg, file))
end

premake.api.register({
	name = "runclangformat",
	scope = "config",
	kind = "boolean",
	default = false
})

premake.api.register({
	name = "runclangtidy",
	scope = "config",
	kind = "boolean",
	default = false
})

newaction({
	trigger = "format-tidy",
	description = "Run Clang-Format and Clang-Tidy on all project files",

	onStart = function()
		if common.host == "windows" then
			formatTidy.formatCommand = "clang-format.exe"
			formatTidy.tidyCommand = "clang-tidy.exe"
		else
			formatTidy.formatCommand = "clang-format"
			formatTidy.tidyCommand = "clang-tidy"
		end

		local result, errorCode = os.outputof(formatTidy.formatCommand .. " --version")
		formatTidy.canFormat = result ~= nil
		result, errorCode = os.outputof(formatTidy.tidyCommand .. " --version")
		formatTidy.canTidy = result ~= nil

		if not formatTidy.canFormat then
			print("format-tidy will not format because " .. formatTidy.formatCommand .. " is unavailable")
		end
		if not formatTidy.canTidy then
			print("format-tidy will not tidy because " .. formatTidy.tidyCommand .. " is unavailable")
		end
	end,

	onProject = function(prj)
		if not formatTidy.canFormat and not formatTidy.canTidy then
			return
		end

		local cfg = premake.project.getconfig(prj, "Dist", common.targetArchs[1])
		local tr = premake.project.getsourcetree(prj)
		premake.tree.traverse(tr, {
			onleaf = function(node, depth)
				if (formatTidy.canFormat and node.runclangformat) or (formatTidy.canTidy and node.runclangtidy) then
					local relpath = premake.workspace.getrelative(cfg.workspace, node.abspath)
					print(relpath)
				end

				if formatTidy.canFormat and node.runclangformat then
					clangFormatFile(cfg, node)
				end

				if formatTidy.canTidy and node.runclangtidy then
					clangTidyFile(cfg, node)
				end
			end
		})
	end
})

newaction({
	trigger = "format",
	description = "Run Clang-Format on all project files",

	onStart = function()
		if common.host == "windows" then
			formatTidy.formatCommand = "clang-format.exe"
		else
			formatTidy.formatCommand = "clang-format"
		end

		local result, errorCode = os.outputof(formatTidy.formatCommand .. " --version")
		formatTidy.canFormat = result ~= nil

		if not formatTidy.canFormat then
			print("Formatting will not take place because " .. formatTidy.formatCommand .. " is unavailable")
		end
	end,

	onProject = function(prj)
		if not formatTidy.canFormat then
			return
		end

		local cfg = premake.project.getconfig(prj, "Dist", common.targetArchs[1])
		local tr = premake.project.getsourcetree(prj)
		premake.tree.traverse(tr, {
			onleaf = function(node, depth)
				if formatTidy.canFormat and node.runclangformat then
					local relpath = premake.workspace.getrelative(cfg.workspace, node.abspath)
					print(relpath)
					clangFormatFile(cfg, node)
				end
			end
		})
	end
})

newaction({
	trigger = "tidy",
	description = "Run Clang-Tidy on all project files",

	onStart = function()
		if common.host == "windows" then
			formatTidy.tidyCommand = "clang-tidy.exe"
		else
			formatTidy.tidyCommand = "clang-tidy"
		end

		local result, errorCode = os.outputof(formatTidy.tidyCommand .. " --version")
		formatTidy.canTidy = result ~= nil

		if not formatTidy.canTidy then
			print("Tidying will not take place because " .. formatTidy.tidyCommand .. " is unavailable")
		end
	end,

	onProject = function(prj)
		if not formatTidy.canTidy then
			return
		end

		local cfg = premake.project.getconfig(prj, "Dist", common.targetArchs[1])
		local tr = premake.project.getsourcetree(prj)
		premake.tree.traverse(tr, {
			onleaf = function(node, depth)
				if formatTidy.canTidy and node.runclangtidy then
					local relpath = premake.workspace.getrelative(cfg.workspace, node.abspath)
					print(relpath)
					clangTidyFile(cfg, node)
				end
			end
		})
	end
})