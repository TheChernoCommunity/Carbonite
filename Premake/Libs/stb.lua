if not libs then libs = {} end
if not libs.stb then
	libs.stb = {
		location = ""
	}
end

local stb = libs.stb

function stb:setup()
	self.location = common:projectLocation()

	kind("Utility")

	includedirs({ self.location })

	files({ self.location .. "/stb_image.h" })
end

function stb:setupDep()
	sysincludedirs({ self.location })
end