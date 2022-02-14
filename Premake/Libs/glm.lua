if not libs then libs = {} end
if not libs.glm then
	libs.glm = {
		name       = "",
		location   = ""
	}
end

local glm = libs.glm

function glm:setup()
	self.name     = common:projectName()
	self.location = common:projectLocation()

	kind("StaticLib")
	common:outDirs(true)

	includedirs({
		self.location,
		self.location .. "/glm/"
	})

	files({ self.location .. "/glm/**" })
end

function glm:setupDep()
	sysincludedirs({ self.location })
end