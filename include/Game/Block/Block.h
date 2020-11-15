#pragma once

#include <string>
#include <Engine/Renderer/Mesh/StaticVoxelMesh.h>

namespace gp1
{
	class Block
	{
	public:
		Block(const std::string& blockID);
	private:
		std::string m_ID;
		
	};
}
