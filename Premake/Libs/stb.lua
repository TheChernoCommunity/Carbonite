local stb = {
	location = ""
}

function stb:setup()
	self.location = common:projectLocation()

	kind("Utility")

	includedirs({ self.location })

	files({ self.location .. "/stb_image.h" })
end

function stb:setupDep()
	sysincludedirs({ self.location })
end

return stb
