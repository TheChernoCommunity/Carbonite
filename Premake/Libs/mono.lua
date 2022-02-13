if not libs then libs = {} end
if not libs.mono then
	libs.mono = {
		name                = "",
		location            = "",
		requiredLibs        = require("mono/RequiredLibs"),
		requiredNativeLibs  = require("mono/RequiredNativeLibs"),
		requiredRuntimeLibs = require("mono/RequiredRuntimeLibs")
	}
end

local mono = libs.mono

require("mono/Build")
require("mono/Validation")

function mono:setup()
	self.name     = common:projectName()
	self.location = common:projectLocation()
	
	kind("Utility")
	
	if not common.fullSetup then
		return
	end
	
	self:validate()
	
	for _, arch in ipairs(common.targetArchs) do
		for _, config in ipairs({ "Debug", "Release", "Dist" }) do
			files({ self.location .. "/Backends/" .. self:toMonoTriple(common.target, arch, config) .. "/include/**" })
		end
	end
end

function mono:setupDep()
	if not common.fullSetup then
		return
	end
	
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
					"{COPYDIR} \"" .. native .. "/bin/\" \"%{!cfg.linktarget.directory}/\"",
					"{COPYDIR} \"" .. self.location .. "/.NET/\" \"%{!cfg.linktarget.directory}/.NET/\""
				})
		end
	end
	
	filter({})
	
	links(self.requiredLibs.static)
	if common.target == "windows" then
		links({
			"Bcrypt",
			"ws2_32",
			"Winmm"
		})
	elseif common.target == "macosx" then
	    links({
	        "z"
	    })
	else
		links(self.requiredLibs.shared)
	end
end