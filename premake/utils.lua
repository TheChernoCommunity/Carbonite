
require 'customizations'

utils = { }

-- The list of platforms differ depending on he specified action
function utils.get_platforms()
	if _ACTION == 'android-studio' then
		return { 'armeabi-v7a', 'arm64-v8a', 'x86', 'x86_64' }
	end

	if os.ishost( 'windows' ) then
		return { 'x64' }
	end

	local arch = os.outputof( 'uname -m' )
	return { arch }
end

-- Return an iterator for the allowed systems
function utils.each_system()
	local field = premake.field.get( 'system' )
	local i

	return function()
		i = next( field.allowed, i )
		return field.allowed[ i ]
	end
end
