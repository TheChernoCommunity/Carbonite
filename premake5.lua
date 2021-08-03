require 'premake/app'
require 'premake/customizations'
require 'premake/defaults'
require 'premake/library'
require 'premake/options'
require 'premake/settings'
require 'premake/target'
require 'premake/utils'

workspace( settings.workspace_name )
platforms( utils.get_platforms() )
configurations { 'Debug', 'Release' }

third_party_library 'glad'
third_party_library 'glfw'
third_party_library 'glm'
third_party_library 'stb'
--third_party_library 'openal-soft'
--third_party_library 'dr_libs'
--third_party_library 'minimp3_s'
library 'Engine'
app 'Game'

-- Set last app as startup
workspace( settings.workspace_name )
startproject( apps[ #apps ] )
