return function()
	warnings 'Off'

	includedirs {
		'third_party/FastNoiseLite/include'
	}

	files {
		'third_party/FastNoiseLite/include/FastNoiseLite.h',
		'third_party/FastNoiseLite/src/FastNoiseLite.cpp'
	}
end
