#pragma once

#include "Graphics/Window.h"

class Renderer;

class Carbonite
{
public:
	static Carbonite& Get();
	static void       Destroy();

public:
	void init();
	void run();
	void deinit();

	auto& getWindow()
	{
		return m_Window;
	}
	auto& getWindow() const
	{
		return m_Window;
	}

	auto getRenderer() const
	{
		return m_Renderer;
	}

protected:
	Carbonite();
	~Carbonite();

private:
	Graphics::Window m_Window;
	Renderer*        m_Renderer;
};