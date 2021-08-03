return function()
	warnings 'Off'

	includedirs {
		'third_party/glfw/include'
	}

	files {
		'third_party/glfw/include/GLFW/glfw3.h',
		'third_party/glfw/include/GLFW/glfw3native.h',
		'third_party/glfw/src/glfw_config.h',
		'third_party/glfw/src/context.c',
		'third_party/glfw/src/init.c',
		'third_party/glfw/src/input.c',
		'third_party/glfw/src/monitor.c',
		'third_party/glfw/src/vulkan.c',
		'third_party/glfw/src/window.c'
	}

	filter 'system:windows'
		files {
			'third_party/glfw/src/win32_init.c',
			'third_party/glfw/src/win32_joystick.c',
			'third_party/glfw/src/win32_monitor.c',
			'third_party/glfw/src/win32_time.c',
			'third_party/glfw/src/win32_thread.c',
			'third_party/glfw/src/win32_window.c',
			'third_party/glfw/src/wgl_context.c',
			'third_party/glfw/src/egl_context.c',
			'third_party/glfw/src/osmesa_context.c'
		}

		defines { 
			'_GLFW_WIN32'
		}


		links('opengl32.lib')

	filter 'system:linux'
		files {
			'third_party/glfw/src/x11_init.c',
			'third_party/glfw/src/x11_monitor.c',
			'third_party/glfw/src/x11_window.c',
			'third_party/glfw/src/xkb_unicode.c',
			'third_party/glfw/src/posix_time.c',
			'third_party/glfw/src/posix_thread.c',
			'third_party/glfw/src/glx_context.c',
			'third_party/glfw/src/egl_context.c',
			'third_party/glfw/src/osmesa_context.c',
			'third_party/glfw/src/linux_joystick.c'
		}

		defines {
			'_GLFW_X11'
		}

	filter 'system:macosx'
		files {
			'third_party/glfw/src/cocoa_platform.h', 
			'third_party/glfw/src/cocoa_joystick.h', 
			'third_party/glfw/src/posix_thread.h',
            'third_party/glfw/src/nsgl_context.h', 
			'third_party/glfw/src/egl_context.h', 
			'third_party/glfw/src/osmesa_context.h',
            'third_party/glfw/src/cocoa_init.m', 
			'third_party/glfw/src/cocoa_joystick.m', 
			'third_party/glfw/src/cocoa_monitor.m',
            'third_party/glfw/src/cocoa_window.m', 
			'third_party/glfw/src/cocoa_time.c', 
			'third_party/glfw/src/posix_thread.c',
            'third_party/glfw/src/nsgl_context.m',
			'third_party/glfw/src/egl_context.c', 
			'third_party/glfw/src/osmesa_context.c'
		}

		defines {
			'_GLFW_COCOA'	
		}

		links {'Cocoa.framework', 'IOKit.framework', 'CoreFoundation.framework', 'OpenGL.framework'}

	filter { }
end
