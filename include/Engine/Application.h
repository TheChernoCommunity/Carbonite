//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#pragma once

#include "Engine/Utility/Core.h"
#include "Engine/Window/Window.h"
#include "Engine/Renderer/Renderer.h"

namespace gp1 {

	class Application {
	public:
		~Application();
		static Application* CreateApplication();

		void Run();
	protected:
		Application();

	private:
		static Application* s_Instance;
		Window m_Window{ { 1280, 720, "Cherno Community Game Project 1", WindowMode::WINDOWED, false } };	// TODO: create init function for application using WindowData
		Renderer m_Renderer{ &m_Window };
	};

} // namespace gp1
