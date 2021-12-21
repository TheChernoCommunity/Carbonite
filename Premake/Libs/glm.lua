local glm = {
	name = "",
	location = ""
}

function glm:setup()
	self.name = common:projectName()
	self.location = common:projectLocation()

	kind("StaticLib")
	common:staticLibOutDirs()

	includedirs({ self.location .. "/glm/" })

	files({ self.location .. "/glm/**" })
end

function glm:setupDep()
	sysincludedirs({ self.location })
end

return glm
