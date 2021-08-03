return function()
	warnings 'Off'

	includedirs {
		'third_party/glad/include'
	}

	files {
		'third_party/glad/include/glad/glad.h',
		'third_party/glad/include/KHR/khrplatform.h',
		'third_party/glad/src/glad.c'
	}
end
