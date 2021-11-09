-- Delets Visual STudio, XCode4 and GMake2 build files.

local function deleteLocalDir(dir)
	local ok, err = os.rmdir(_MAIN_SCRIPT_DIR .. dir)
	if ok then
		print("Deleted " .. _MAIN_SCRIPT_DIR .. dir)
	end
end

local function deleteFile(file)
	local ok, err = os.remove(file)
	if ok then
		print("Deleted " .. file)
	end
end

local function deleteDir(dir)
	local ok, err = os.rmdir(dir)
	if ok then
		print("Deleted " .. dir)
	end
end

local function getMakeFilename(this, searchprjs)
	local count = 0
	for wks in premake.global.eachWorkspace() do
		if wks.location == this.location then
			count = count + 1
		end

		if searchprjs then
			for _, prj in ipairs(wks.projects) do
				if prj.location == this.location then
					count = count + 1
				end
			end
		end
	end

	if count == 1 then
		return "Makefile"
	else
		return ".make"
	end
end

newaction({
	trigger = "clean",
	description = "Delete all build files",

	onStart = function()
		deleteLocalDir("/Bin/")

		-- Visual Studio:
		deleteLocalDir("/.vs/")
	end,

	onWorkspace = function(wks)
		-- Visual Studio:
		deleteFile(premake.filename(wks, ".sln"))

		-- XCode4:
		deleteDir(premake.filename(wks, ".xcworkspace") .. "/")

		-- GMake2:
		deleteFile(premake.filename(wks, getMakeFilename(wks, false)))
	end,

	onProject = function(prj)
		-- Visual Studio:
		if premake.project.iscsharp(prj) then
			deleteFile(premake.filename(prj, ".csproj"))
			deleteFile(premake.filename(prj, ".csproj.user"))
		elseif premake.project.isfsharp(prj) then
			deleteFile(premake.filename(prj, ".fsproj"))
			deleteFile(premake.filename(prj, ".fsproj.user"))
		elseif premake.project.isc(prj) or premake.project.iscpp(prj) then
			if prj.kind == premake.SHAREDITEMS then
				deleteFile(premake.filename(prj, ".vcxitems"))
				deleteFile(premake.filename(prj, ".vcxitems.filters"))
			else
				deleteFile(premake.filename(prj, ".vcxproj"))
				deleteFile(premake.filename(prj, ".vcxproj.user"))
				deleteFile(premake.filename(prj, ".vcxproj.filters"))
			end
		end

		if not premake.vstudio.nuget2010.supportsPackageReferences(prj) then
			deleteFile(premake.filename(prj, "packages.config"))
			deleteFile(premake.filename(prj, "NuGet.Config"))
		end

		-- XCode4:
		deleteDir(premake.filename(prj, ".xcodeproj") .. "/")

		-- GMake2:
		deleteFile(premake.filename(prj, getMakeFilename(prj, true)))
	end,

	onEnd = function()
		print("Cleaned")
	end
})