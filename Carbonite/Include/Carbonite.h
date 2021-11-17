#pragma once

#include "Block/Block.h"
#include "Graphics/Window.h"
#include "Utils/Registry.h"
#include "World/Dimension.h"

#include <vector>

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

	auto& getLoadedDimensions()
	{
		return m_LoadedDimensions;
	}
	auto& getLoadedDimensions() const
	{
		return m_LoadedDimensions;
	}

	auto& getBlockRegistry()
	{
		return m_BlockRegistry;
	}
	auto& getBlockRegistry() const
	{
		return m_BlockRegistry;
	}

protected:
	Carbonite();
	~Carbonite();

private:
	Graphics::Window m_Window;
	Renderer*        m_Renderer;

	std::vector<Dimension> m_LoadedDimensions;

	Registry<Block> m_BlockRegistry;
};
