#pragma once

#include "Graphics/Memory/Buffer.h"

#include <cstdint>

#include <vector>

#include <glm/glm.hpp>

struct Vertex
{
public:
	glm::fvec4 m_Position;
	glm::fvec4 m_Normal;
	glm::fvec2 m_UV;
};

struct Mesh
{
public:
	Mesh(Graphics::Memory::VMA& vma);

	void updateMeshData();

	auto& getMeshData()
	{
		return m_MeshData;
	}
	auto& getMeshData() const
	{
		return m_MeshData;
	}

	auto getVertexCount() const
	{
		return m_VertexCount;
	}
	auto getIndexCount() const
	{
		return m_IndexCount;
	}

public:
	std::vector<Vertex>        m_Vertices;
	std::vector<std::uint32_t> m_Indices;

private:
	Graphics::Memory::Buffer m_MeshData;

	std::size_t m_VertexCount = 0;
	std::size_t m_IndexCount  = 0;
};