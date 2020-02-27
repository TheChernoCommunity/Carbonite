
require 'customizations'
require 'options'

-- Set system to android if the "android-studio" action was specified
if _ACTION == 'android-studio' then
	_TARGET_OS = 'android'
	system 'android'
end

-- Set system to iOS if the "ios" option was specified
if _OPTIONS[ 'ios' ] then
	_TARGET_OS = 'ios'
end
