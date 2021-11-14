local stb = {
	location = ""
}

function stb:setup()
	self.location = common:projectLocation()

	kind("Utility")

	includedirs({ "%{prj.location}/" })

	files({ "%{prj.location}/stb_image.h" })
end

function stb:setupDep()
	sysincludedirs({ self.location })
end

return stb