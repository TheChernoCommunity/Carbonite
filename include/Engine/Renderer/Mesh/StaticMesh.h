#pragma once

#include "Engine/Renderer/Mesh/Mesh.h"

#include <glm.hpp>
#include <vector>

namespace gp1
{
	struct StaticMeshVertex
	{
	public:
		glm::fvec4 m_Position {};
		glm::fvec4 m_Normal {};
		glm::fvec2 m_Uv {};
	};

	struct StaticMesh : public Mesh
	{
	public:
		std::vector<StaticMeshVertex> m_Vertices;
		std::vector<uint32_t>         m_Indices;
	};
} // namespace gp1