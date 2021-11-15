#pragma once

#include "Renderer/Renderer.h"

class Carbonite
{
public:
	static Carbonite& Get();
	static void       Destroy();

public:
	void init();
	void run();
	void deinit();

	auto& getRenderer()
	{
		return m_Renderer;
	}
	auto& getRenderer() const
	{
		return m_Renderer;
	}

protected:
	Carbonite();
	~Carbonite();

private:
	Renderer m_Renderer;
};