local function writeNonBinaryFile(filename, content)
	local file = io.open(filename, "w")
	if file then
		file:write(content)
		file:close()
		return true
	end
end

local function readNonBinaryFile(filename)
	local file = io.open(filename, "r")
	if file then
		local content = file:read("*a")
		file:close()
		return content
	end
end

local function forcePCH(cfg, file)
	-- TODO(MarcasRealAccount): Stop assuming single space between #include and quote ""
	
	local fileStr = readNonBinaryFile(file.abspath)
	if string.startswith(fileStr, "#include \"" .. cfg.pchheader .. "\"") then
		return
	end

	local newFileStr = "#include \"" .. cfg.pchheader .. "\"\n"
	for l, v in next, string.explode(fileStr, "\n") do
		if not string.startswith(v, "#include \"" .. cfg.pchheader .. "\"") then
			newFileStr = newFileStr .. "\n" .. v
		end
	end

	writeNonBinaryFile(file.abspath, newFileStr)
end

premake.api.register({
	name = "allowforcepch",
	scope = "config",
	kind = "boolean",
	default = false
})

newaction({
	trigger = "force-pch",
	description = "Force PCH include",

	onProject = function(prj)
		local cfg = premake.project.getconfig(prj, "Dist", "x64")
		local tr = premake.project.getsourcetree(prj)
		premake.tree.traverse(tr, {
			onleaf = function(node, depth)
				if node.allowforcepch then
					local relpath = premake.workspace.getrelative(cfg.workspace, node.abspath)
					print(relpath)
					forcePCH(cfg, node)
				end
			end
		})
	end
})