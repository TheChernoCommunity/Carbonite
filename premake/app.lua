
require 'library'
require 'settings'
require 'third_party_library'

apps = { }

function app( name )
	group 'Apps'
	project( name )

	debugdir 'src/%{prj.name}/Assets'
	links( libraries )
	links( third_party_libraries )
	location 'build/%{_ACTION}'
	xcodebuildresources 'src/%{prj.name}/Assets'

	sysincludedirs {
		'include',
		'third_party/glfw/include',
		'third_party/glad/include',
		'third_party/glm/glm',
		'third_party/stb',
		--'third_party/openal-soft/include',
		--'third_party/openal-soft/src',
		--'third_party/openal-soft/src/common'
	}

	files {
		'include/%{prj.name}/**.h',
		'src/%{prj.name}/**.cpp',
		'src/%{prj.name}/**.h',
	}

	filter 'system:linux'
		linkoptions { '-pthread -Wl,-rpath=\\$$ORIGIN' }
		links {
			'dl'
		}

	filter 'system:ios'
		files { 'src/%{prj.name}/Resources/Info.plist', 'src/%{prj.name}/Assets' }

	filter { 'system:macosx or ios', 'files:**.cpp' }
		compileas 'Objective-C++'

	filter 'system:macosx'
		links {'Cocoa.framework', 'IOKit.framework', 'CoreFoundation.framework', 'OpenGL.framework'}

	filter 'configurations:Debug'
		kind 'ConsoleApp'

	filter 'configurations:Release'
		kind 'WindowedApp'

	filter { }

	table.insert( apps, name )
end
