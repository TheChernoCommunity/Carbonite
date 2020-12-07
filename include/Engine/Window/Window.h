//
//	Created by rtryan98 on 21. Oct. 2020
//	Edited by MarcasRealAccount on 29. Oct. 2020
//

#pragma once

#define GLFW_INCLUDE_NONE
#include "Engine/Utility/Logger.h"
#include <glfw/glfw3.h>
#include <string>

namespace gp1
{
	namespace renderer
	{
		class Renderer;
	}

	namespace window
	{
		enum class WindowMode : int8_t
		{
			WINDOWED = 0,
			FULLSCREEN,
			BORDERLESS
		};

		struct WindowData
		{
			unsigned int FramebufferWidth;
			unsigned int FramebufferHeight;
			unsigned int Width;
			unsigned int Height;
			std::string  Title;
			WindowMode   Mode;
			bool         VSync;
		};

		class Window
		{
		public:
			Window(const WindowData& p_WindowData);
			Window(const Window& other)  = delete;
			Window(const Window&& other) = delete;
			~Window()                    = default;

			Window& operator=(const Window& other) = delete;
			Window& operator=(const Window&& other) = delete;

			// Initialize the window.
			void Init();
			// Deinitialize the window.
			void DeInit();
			// Update the window.
			void OnUpdate();

			// Sets the window's VSync.
			void SetVSync(const bool p_VSync);
			// Sets the window's width.
			void SetWidth(const int p_Width);
			// Sets the window's height.
			void SetHeight(const int p_Height);
			// Sets the window's size.
			void SetSize(const int p_Width, const int p_Height);
			// Sets the window's title.
			void SetTitle(const std::string& p_Title);

			// Get the value of the given input mode.
			int GetInputMode(int mode);
			// Set the value of the given input mode.
			void SetInputMode(int mode, int value);

			// Get the window data.
			const WindowData& GetWindowData() const;

			// Should this window close.
			const bool IsCloseRequested() const;

			friend renderer::Renderer;

		private:
			WindowData  m_WindowData;               // The window data.
			Logger      m_Logger;                   // The logger this window uses to report errors.
			GLFWwindow* m_NativeHandle { nullptr }; // The native GLFW window.
		};

	} // namespace window

} // namespace gp1
