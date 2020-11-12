//
//	Created by rtryan98 on 21. Oct. 2020
//	Edited by MarcasRealAccount on 29. Oct. 2020
//

#pragma once
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>
#include <string>
#include "Engine/Utility/Logger.h"

namespace gp1
{
	class Renderer;

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
		std::string Title;
		WindowMode Mode;
		bool VSync;
	};

	class Window
	{
	public:
		Window(const WindowData& p_WindowData);
		Window(const Window& other) = delete;
		Window(const Window&& other) = delete;
		Window& operator=(const Window& other) = delete;
		Window& operator=(const Window&& other) = delete;
		~Window() = default;
		void Init();
		void DeInit();
		void OnUpdate();
		void SetVSync(const bool p_VSync);
		void SetWidth(const int p_Width);
		void SetHeight(const int p_Height);
		void SetSize(const int p_Width, const int p_Height);
		void SetTitle(const std::string& p_Title);
		int GetInputMode(int mode);
		void SetInputMode(int mode, int value);
		const WindowData& GetWindowData() const;
		const bool IsCloseRequested() const;
		friend Renderer;
	private:
		WindowData m_WindowData;
		Logger m_Logger;
		GLFWwindow* m_NativeHandle{ nullptr };
	};
} // namespace gp1
