local entt = {
	location = ""
}

function entt:setup()
	self.location = common:projectLocation()

	kind("Utility")

	includedirs({ self.location .. "/single_include/" })

	files({ self.location .. "/single_include/**" })
end

function entt:setupDep()
	sysincludedirs({ self.location .. "/single_include/" })
end

return entt
