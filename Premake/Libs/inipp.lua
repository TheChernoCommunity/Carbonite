local inipp = {
	location = ""
}

function inipp:setup()
	self.location = common:projectLocation()

	kind("Utility")

	includedirs({ "%{prj.location}/inipp/" })

	files({ "%{prj.location}/inipp/inipp.h" })
end

function inipp:setupDep()
	sysincludedirs({ self.location .. "/inipp/" })
end

return inipp