#pragma once

#include "Graphics/Window.h"
#include "Utils/Registry.h"
#include "Voxel/Voxel.h"
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

	auto& getVoxelRegistry()
	{
		return m_VoxelRegistry;
	}
	auto& getVoxelRegistry() const
	{
		return m_VoxelRegistry;
	}

protected:
	Carbonite();
	~Carbonite();

private:
	Graphics::Window m_Window;
	Renderer*        m_Renderer;

	std::vector<Dimension> m_LoadedDimensions;

	Registry<Voxel> m_VoxelRegistry;
};
