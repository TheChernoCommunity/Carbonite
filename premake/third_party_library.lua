
third_party_libraries = { }

function third_party_library( name )
	local module_path = path.join( 'third_party', name..'.lua' )
	local dofunc      = dofile(  module_path )

	group 'ThirdParty'
	project( name )

	kind 'StaticLib'
	location 'build/%{_ACTION}'

	pcall( dofunc )

	table.insert( third_party_libraries, name )
end
