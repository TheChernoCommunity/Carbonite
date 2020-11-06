return function()
	warnings 'Off'

	includedirs {
		'third_party/glm'
	}

	files {
		'third_party/glm/glm/**.h',
		'third_party/glm/glm/**.inl',
		'third_party/glm/glm/**.hpp',
		'third_party/glm/glm/**.cpp'
	}
end
