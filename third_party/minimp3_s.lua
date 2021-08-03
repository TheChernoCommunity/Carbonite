return function()
	warnings 'Off'

	includedirs {
		'third_party/minimp3_s'
	}

	files {
		'third_party/minimp3_s/minimp3.h',
		'third_party/minimp3_s/minimp3_ex.h',
		'third_party/minimp3_s.cpp'
	}
end