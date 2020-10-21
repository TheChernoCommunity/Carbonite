
libraries = { }

function library( name )
	group 'Libraries'
	project( name )

	kind 'StaticLib'
	links( libraries )
	location 'build/%{_ACTION}'

	sysincludedirs {
		'third_party/glfw/include',
		'third_party/glad/include',
	}

	files {
		'include/%{prj.name}/**.h',
		'src/%{prj.name}/**.cpp',
		'src/%{prj.name}/**.h',
	}

	filter 'system:macosx or ios'
		files { 'src/%{prj.name}/**.mm' }

	filter { 'system:macosx or ios', 'files:**.cpp' }
		compileas 'Objective-C++'

	filter { }

	table.insert( libraries, name )
end
