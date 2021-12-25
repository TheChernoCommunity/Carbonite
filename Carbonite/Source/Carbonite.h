#pragma once

#include "Block/Block.h"
#include "Block/BlockState.h"
#include "Graphics/Window.h"
#include "Mod/Mod.h"
#include "Utils/InternalRegistry.h"
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

protected:
	Carbonite();
	~Carbonite();

public:
	std::vector<ModInfo> m_AvailableMods;
	std::vector<Mod>     m_EnabledMods;

	std::vector<Dimension> m_LoadedDimensions;

	Registry<Block>      m_BlockRegistry;
	Registry<BlockState> m_BlockStateRegistry;

private:
	Graphics::Window m_Window;
	Renderer*        m_Renderer;
};
