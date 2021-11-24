local inipp = {
	location = ""
}

function inipp:setup()
	self.location = common:projectLocation()

	kind("Utility")

	includedirs({ self.location .. "/inipp/" })

	files({ self.location .. "/inipp/inipp.h" })
end

function inipp:setupDep()
	sysincludedirs({ self.location .. "/inipp/" })
end

return inipp
