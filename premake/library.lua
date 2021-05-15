
libraries = { }

function library( name )
	group 'Libraries'
	project( name )

	kind 'StaticLib'
	links( libraries )
	location ''

	sysincludedirs {
		'third_party/glfw/include',
		'third_party/glad/include',
		'third_party/glm/glm',
		'third_party/stb',
		'third_party/openal-soft/include',
		'third_party/openal-soft/src',
		'third_party/openal-soft/src/common',
		'third_party/dr_libs',
		'third_party/minimp3_s',
	}

	files {
		'include/%{prj.name}/**.h',
		'src/%{prj.name}/**.cpp',
		'src/%{prj.name}/**.h',
	}

	vpaths {
		-- For some reason, the token '%{prj.name}' doesn't work with vpaths
		[ 'Header Files/*' ] = 'include/' .. name .. '/*',
		[ 'Source Files/*' ] = 'src/' .. name .. '/*',
	}

	defines {
		"AL_LIBTYPE_STATIC",
	}

	filter 'system:macosx or ios'
		files { 'src/%{prj.name}/**.mm' }

	filter { 'system:macosx or ios', 'files:**.cpp' }
		compileas 'Objective-C++'

	filter { }

	table.insert( libraries, name )
end
