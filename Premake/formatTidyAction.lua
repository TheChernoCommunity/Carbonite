local function formatTidyExecuteClangFormatOnFile(cfg, file)
	local relpath = premake.workspace.getrelative(cfg.workspace, file.abspath)
	
	local command
	local host = os.host()
	if host == "windows" then
		command = "clang-format.exe "
	else
		command = "clang-format "
	end
	command = command .. "-i " .. relpath
	os.execute(command)
end

local function formatTidyList(value, quoted)
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

local function formatTidyGetIncludeDirs(cfg, dirs, sysdirs, frameworkdirs)
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

local function formatTidyGetCommandLine(cfg, file)
	local fcfg = premake.fileconfig.getconfig(file, cfg)
	local toolset = premake.tools["clang"]
	local isCFile = path.iscfile(fcfg.name)
	local getflags = iif(isCFile, toolset.getcflags, function(cfg) return table.join(toolset.getcppflags(cfg), toolset.getcxxflags(cfg)) end)
	local value = formatTidyList(table.join(getflags(cfg), cfg.buildoptions), table.join(getflags(fcfg), fcfg.buildoptions))
	
	if cfg.defines or cfg.undefines then
		local defs = table.join(toolset.getdefines(cfg.defines, cfg), toolset.getundefines(cfg.undefines))
		if #defs > 0 then
			value = value .. formatTidyList(defs)
		end
	end
	
	if cfg.includedirs or cfg.sysincludedirs or cfg.frameworkdirs then
		local includes = formatTidyGetIncludeDirs(cfg, cfg.includedirs, cfg.sysincludedirs, cfg.frameworkdirs)
		if #includes > 0 then
			value = value .. formatTidyList(includes)
		end
	end
	
	if fcfg.defines or fcfg.undefines then
		local defs = table.join(toolset.getdefines(fcfg.defines, cfg), toolset.getundefines(fcfg.undefines))
		if #defs > 0 then
			value = value .. formatTidyList(defs)
		end
	end
	
	if fcfg.includedirs or fcfg.sysincludedirs or fcfg.frameworkdirs then
		local includes = formatTidyGetIncludeDirs(cfg, fcfg.includedirs, fcfg.sysincludedirs, fcfg.frameworkdirs)
		if #includes > 0 then
			value = value .. formatTidyList(includes)
		end
	end
	
	return value
end

local function formatTidyExecuteClangTidyOnFile(cfg, file)
	local relpath = premake.workspace.getrelative(cfg.workspace, file.abspath)
	
	local command
	local host = os.host()
	if host == "windows" then
		command = "clang-tidy.exe "
	else
		command = "clang-tidy "
	end
	command = command .. relpath .. " --" .. formatTidyGetCommandLine(cfg, file)
	os.execute(command)
end

premake.api.register({
	name = "runclangformat",
	scope = "config",
	kind = "boolean"
})

premake.api.register({
	name = "runclangtidy",
	scope = "config",
	kind = "boolean"
})

newaction({
	trigger = "format-tidy",
	description = "Run Clang-Format and Clang-Tidy on all project files",
	
	onProject = function(prj)
		local cfg = premake.project.getconfig(prj, "Dist", "x64")
		local tr = premake.project.getsourcetree(prj)
		premake.tree.traverse(tr, {
			onleaf = function(node, depth)
				if node.runclangformat or node.runclangtidy then
					local relpath = premake.workspace.getrelative(cfg.workspace, node.abspath)
					print(relpath)
				end
				if node.runclangformat then
					formatTidyExecuteClangFormatOnFile(cfg, node)
				end
				if node.runclangtidy then
					formatTidyExecuteClangTidyOnFile(cfg, node)
				end
			end
		})
	end
})

newaction({
	trigger = "format",
	description = "Run Clang-Format on all project files",
	
	onProject = function(prj)
		local cfg = premake.project.getconfig(prj, "Dist", "x64")
		local tr = premake.project.getsourcetree(prj)
		premake.tree.traverse(tr, {
			onleaf = function(node, depth)
				if node.runclangformat then
					local relpath = premake.workspace.getrelative(cfg.workspace, node.abspath)
					print(relpath)
					formatTidyExecuteClangFormatOnFile(cfg, node)
				end
			end
		})
	end
})

newaction({
	trigger = "tidy",
	description = "Run Clang-Tidy on all project files",
	
	onProject = function(prj)
		local cfg = premake.project.getconfig(prj, "Dist", "x64")
		local tr = premake.project.getsourcetree(prj)
		premake.tree.traverse(tr, {
			onleaf = function(node, depth)
				if node.runclangtidy then
					local relpath = premake.workspace.getrelative(cfg.workspace, node.abspath)
					print(relpath)
					formatTidyExecuteClangTidyOnFile(cfg, node)
				end
			end
		})
	end
})
