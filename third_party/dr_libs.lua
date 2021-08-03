return function()
	warnings 'Off'

	includedirs {
		'third_party/dr_libs'
	}

	files {
		'third_party/dr_libs/dr_flac.h',
		'third_party/dr_libs/dr_wav.h',
		'third_party/dr_libs.cpp'
	}
end