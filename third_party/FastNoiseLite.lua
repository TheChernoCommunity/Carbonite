return function()
	warnings 'Off'

	includedirs {
		'third_party/FastNoiseLite/Cpp'
	}

	files {
		'third_party/FastNoiseLite/Cpp/FastNoiseLite.h',
		'third_party/FastNoiseLite.cpp'
	}
end
