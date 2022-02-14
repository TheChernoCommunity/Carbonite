if not libs then libs = {} end
if not libs.vulkan then
	libs.vulkan = {
		sdkPath         = "",
		libPath         = "",
		includePath     = "",
		requiredSDKLibs = nil,
		initialized     = false
	}
end

local vulkan = libs.vulkan

newoption({
	trigger     = "vulkan-sdk",
	description = "Overrides VULKAN_SDK environment variable",
	value       = "path",
	default     = os.getenv("VULKAN_SDK")
})

function vulkan:getRequiredSDKLibraries()
	if common.host == "windows" then
		self.requiredSDKLibs = {
			all   = { "vulkan-1" },
			dist  = { "shaderc_combined" },
			debug = { "shaderc_combinedd" }
		}
	else
		self.requiredSDKLibs = {
			all = {
				"vulkan",
				"shaderc_combined"
			},
			dist  = {},
			debug = {}
		}
	end
end

function vulkan:validate()
	self:getRequiredSDKLibraries()

	if self.sdkPath then
		local searchPath = self.sdkPath .. self.libPath

		local missingLibs      = {}
		local missingDebugLibs = false
		local errorMessage     = ""
		for _, v in ipairs(self.requiredSDKLibs.all) do
			if not common:hasLib(v, searchPath) then
				missingLibs[v] = true
			end
		end
		for _, v in ipairs(self.requiredSDKLibs.dist) do
			if not common:hasLib(v, searchPath) then
				missingLibs[v] = true
			end
		end
		for _, v in ipairs(self.requiredSDKLibs.debug) do
			if not common:hasLib(v, searchPath) then
				missingLibs[v]   = true
				missingDebugLibs = true
			end
		end

		if #missingLibs > 0 then
			errorMessage = [[Missing required sdk libraries.
If you think this is an issue with the premake setup please open an issue.]]
		end

		if common.host == "windows" then
			-- Test to make sure debug libraries are available in the vulkan sdkPath
			if missingDebugLibs then
				if errorMessage:len() > 0 then
					errorMessage = errorMessage .. "\n"
				end
				errorMessage = errorMessage .. [[Missing required debug sdk libraries.
If you haven't installed the debug sdk libraries go to vulkan sdk download page and find 'Shader Libs (Debug)'.]]
			end
		end

		if #missingLibs > 0 then
			for k, v in pairs(missingLibs) do
				if v then
					errorMessage = errorMessage .. "\n  " .. k
				end
			end
		end

		if errorMessage:len() > 0 then
			error(errorMessage)
		end
	else
		if common.host == "windows" then
			error([[Have you installed the Vulkan SDK correctly.
If you have then please go into environment variables and add 'VULKAN_SDK' with the path to the SDK!]])
		elseif common.host == "macosx" then
			error([[Please find the Vulkan SDK and run the 'setup-env.sh' script in a terminal environment before running premake again!
You can open '~/.zshrc' or '~/bashrc' and add:
cd "PathToVulkanSDK"
source setup-env.sh
cd ~/]])
		else
			error([[Please find the Vulkan SDK and run the 'setup-env.sh' script in a terminal environment before running premake again!
You can open '~/.zshrc' or '~/bashrc' and add:
source "PathToVulkanSDK/setup-env.sh"]])
		end
	end
end

function vulkan:getVulkanSDKPath()
	if initialized then
		return
	end
	initialized = true

	self.sdkPath = path.translate(_OPTIONS["vulkan-sdk"], "/")

	if common.host == "windows" then
		self.libPath     = "/Lib/"
		self.includePath = "/Include/"
	else
		self.libPath     = "/lib/"
		self.includePath = "/include/"
	end

	self:validate()
end

function vulkan:setup()
	kind("Utility")

	if not common.fullSetup then
		return
	end

	self:getVulkanSDKPath()

	includedirs({ self.sdkPath .. self.includePath })
	files({ self.sdkPath .. self.includePath .. "**" })
end

function vulkan:setupDep(noLink)
	if not common.fullSetup then
		return
	end

	self:getVulkanSDKPath()

	sysincludedirs({ self.sdkPath .. self.includePath })

	if not noLink then
		libdirs({ self.sdkPath .. self.libPath })
		links(self.requiredSDKLibs.all)
		filter("configurations:Debug")
			links(self.requiredSDKLibs.debug)

		filter("configurations:not Debug")
			links(self.requiredSDKLibs.dist)

		filter({})
	end
end