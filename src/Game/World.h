#pragma once
#include <iostream>
#include "Engine/Application.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Renderer/DebugRenderer.h"
#include "Engine/Utility/Locale/LocaleManager.h"

/*
	Block IDs:
	0 -> Air,
	1 -> Grass
	...
*/

class World
{
public:
	int blocks[16][16][16];
	//Renders the world.
	void RenderWorld() {
		for (int x = 0; x < 16; x++)
		{
			for (int y = 0; y < 16; y++)
			{
				for (int z = 0; z < 16; z++)
				{
					if (blocks[x][y][z] != 0)
					{
						gp1::renderer::DebugRenderer::DebugDrawBox({ x, y, z }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, 9999999999.0f);
					}
				}
			}
		}
	}
	//Initalizes the world and sets all of the blocks to air.
	World() {
		for (int x = 0; x < 16; x++)
		{
			for (int y = 0; y < 16; y++)
			{
				for (int z = 0; z < 16; z++)
				{
					blocks[x][y][z] = 0;
				}
			}
		}
	}
};

