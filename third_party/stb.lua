return function()
	warnings 'Off'

	includedirs {
		'third_party/stb/stb'
	}

	files {
		'third_party/stb/stb/**.h',
		'third_party/stb/stb/**.c'
	}
end