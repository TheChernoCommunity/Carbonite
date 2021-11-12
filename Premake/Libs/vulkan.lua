local vulkan = {
	sdkPath = "",
	libPath = "",
	includePath = "",
	requiredSDKLibs = nil
}

newoption({
	trigger = "vulkan-sdk",
	description = "Overrides VULKAN_SDK environment variable",
	value = "path",
	default = os.getenv("VULKAN_SDK")
})

function vulkan:getRequiredSDKLibraries()
	if common.host == "windows" then
		self.requiredSDKLibs = {
			dist = {
				"vulkan-1",
				"glslang",
				"SPIRV",
				"SPVRemapper",
				"GenericCodeGen",
				"MachineIndependent",
				"OSDependent",
				"OGLCompiler",
				"SPIRV-Tools",
				"SPIRV-Tools-opt",
				"SPIRV-Tools-link"
			},
			debug = {
				"vulkan-1",
				"glslangd",
				"SPIRVd",
				"SPVRemapperd",
				"GenericCodeGend",
				"MachineIndependentd",
				"OSDependentd",
				"OGLCompilerd",
				"SPIRV-Toolsd",
				"SPIRV-Tools-optd",
				"SPIRV-Tools-linkd"
			}
		}
	else
		self.requiredSDKLibs = {
			dist = {
				"vulkan",
				"glslang",
				"SPIRV",
				"SPVRemapper",
				"GenericCodeGen",
				"MachineIndependent",
				"OSDependent",
				"OGLCompiler",
				"SPIRV-Tools",
				"SPIRV-Tools-opt",
				"SPIRV-Tools-link"
			},
			debug = {
				"vulkan",
				"glslang",
				"SPIRV",
				"SPVRemapper",
				"GenericCodeGen",
				"MachineIndependent",
				"OSDependent",
				"OGLCompiler",
				"SPIRV-Tools",
				"SPIRV-Tools-opt",
				"SPIRV-Tools-link"
			}
		}
	end
end

function vulkan:validateVulkanSDK()
	if common.host == "windows" then
		if self.sdkPath then
			-- Test to make sure debug libraries are available in the vulkan sdk
			local searchPath = self.sdkPath .. self.libPath

			local missingLibs = {}
			for _, v in ipairs(self.requiredSDKLibs.debug) do
				if not common:hasLib(v, { searchPath }) then
					missingLibs[v] = true
				end
			end

			if #missingLibs > 0 then
				local errorMessage = [[Missing required debug sdk libraries.
If you haven't installed the debug sdk libraries go to vulkan sdk download page and find 'Shader Libs (Debug)'.]]

				for k, v in pairs(missingLibs) do
					if v then
						errorMessage = errorMessage .. "\n  " .. k
					end
				end

				error(errorMessage)
			end
		else
			error([[Have you installed the Vulkan SDK correctly.
If you have then please go into environment variables and add 'VULKAN_SDK' with the path to the SDK!]])
		end
	elseif common.host == "macosx" then
		if not self.sdkPath then
			error([[Please find the Vulkan SDK and run the 'setup-env.sh' script in a terminal environment before running premake again!
You can open '~/.zshrc' or '~/.bashrc' and add:
cd "PathToVulkanSDK"
source setup-env.sh
cd ~/]])
		end
	else
		if not self.sdkPath then
			error([[Please find the Vulkan SDK and run the 'setup-env.sh' script in a terminal environment before running premake again!
You can open '~/.zshrc' or '~/.bashrc' and add:
source "PathToVulkanSDK/setup-env.sh"]])
		end
	end
	
	if self.sdkPath then
		local searchPath = self.sdkPath .. self.libPath

		local missingLibs = {}
		for _, v in ipairs(self.requiredSDKLibs.dist) do
			if not common:hasLib(v, { searchPath }) then
				missingLibs[v] = true
			end
		end
		for _, v in ipairs(self.requiredSDKLibs.debug) do
			if not common:hasLib(v, { searchPath }) then
				missingLibs[v] = true
			end
		end

		if #missingLibs > 0 then
			local errorMessage = [[Missing required sdk libraries.
If you think this is an issue with the premake setup please open an issue.]]

			for k, v in pairs(missingLibs) do
				if v then
					errorMessage = errorMessage .. "\n  " .. k
				end
			end

			error(errorMessage)
		end
	end
end

function vulkan:getVulkanSDKPath()
	self.sdkPath = _OPTIONS["vulkan-sdk"]

	if common.host == "windows" then
		self.libPath = "/Lib/"
		self.includePath = "/Include/"
	else
		self.libPath = "/lib/"
		self.includePath = "/include/"
	end

	self:validateVulkanSDK()
end

vulkan:getRequiredSDKLibraries()
vulkan:getVulkanSDKPath()

function vulkan:setup()
	kind("Utility")
	
	common:staticLibOutDirs()
	
	includedirs({ self.sdkPath .. self.includePath })
	
	files({ self.sdkPath .. self.includePath .. "**" })
end

function vulkan:setupDep(noLink)
	sysincludedirs({ self.sdkPath .. self.includePath })

	if not noLink then
		libdirs({ self.sdkPath .. self.libPath })
		filter("configurations:Debug")
			links(self.requiredSDKLibs.debug)

		filter("configurations:not Debug")
			links(self.requiredSDKLibs.dist)

		filter({})
	end
end

return vulkan
