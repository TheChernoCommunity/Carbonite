//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Renderer/Mesh/Generators/Icosphere.h"

#include <array>
#include <map>
#include <vector>

namespace gp1::renderer::meshGenerators
{
	const float X = 0.525731112119133606f;
	const float Z = 0.850650808352039932f;
	const float N = 0.0f;

	using Lookup = std::map<std::pair<uint32_t, uint32_t>, uint32_t>;

	uint32_t VertexForEdge(Lookup& lookup, mesh::StaticMesh& mesh, uint32_t first, uint32_t second)
	{
		std::pair<uint32_t, uint32_t> key(first, second);
		if (key.first > key.second)
			std::swap(key.first, key.second);

		auto inserted = lookup.insert({ key, (uint32_t) mesh.m_Vertices.size() });
		if (inserted.second)
		{
			auto& edge0 = mesh.m_Vertices[first];
			auto& edge1 = mesh.m_Vertices[second];
			auto  point = glm::normalize(edge0.position + edge1.position);
			mesh.m_Vertices.push_back({ point });
		}

		return inserted.first->second;
	}

	void subdivide(mesh::StaticMesh& mesh)
	{
		Lookup                lookup;
		std::vector<uint32_t> result;

		for (uint32_t i = 0; i < mesh.m_Indices.size() - 2; i += 3)
		{
			uint32_t                each[3] = { mesh.m_Indices[i], mesh.m_Indices[i + 1ULL], mesh.m_Indices[i + 2ULL] };
			std::array<uint32_t, 3> mid;
			for (uint32_t edge = 0; edge < 3; edge++)
			{
				mid[edge] = VertexForEdge(lookup, mesh, each[edge], each[(edge + 1) % 3]);
			}

			result.push_back(each[0]);
			result.push_back(mid[0]);
			result.push_back(mid[2]);
			result.push_back(each[1]);
			result.push_back(mid[1]);
			result.push_back(mid[0]);
			result.push_back(each[2]);
			result.push_back(mid[2]);
			result.push_back(mid[1]);
			result.push_back(mid[0]);
			result.push_back(mid[1]);
			result.push_back(mid[2]);
		}

		mesh.m_Indices = result;
	}

	void GenerateIcosphere(mesh::StaticMesh& mesh, uint32_t subdivisions)
	{
		mesh.m_Vertices.clear();
		mesh.m_Indices.clear();

		// Start with precoded mesh.
		mesh.m_Vertices.push_back({ { -X, N, Z } });
		mesh.m_Vertices.push_back({ { X, N, Z } });
		mesh.m_Vertices.push_back({ { -X, N, -Z } });
		mesh.m_Vertices.push_back({ { X, N, -Z } });
		mesh.m_Vertices.push_back({ { N, Z, X } });
		mesh.m_Vertices.push_back({ { N, Z, -X } });
		mesh.m_Vertices.push_back({ { N, -Z, X } });
		mesh.m_Vertices.push_back({ { N, -Z, -X } });
		mesh.m_Vertices.push_back({ { Z, X, N } });
		mesh.m_Vertices.push_back({ { -Z, X, N } });
		mesh.m_Vertices.push_back({ { Z, -X, N } });
		mesh.m_Vertices.push_back({ { -Z, -X, N } });

		mesh.m_Indices.push_back(0);
		mesh.m_Indices.push_back(4);
		mesh.m_Indices.push_back(1);
		mesh.m_Indices.push_back(0);
		mesh.m_Indices.push_back(9);
		mesh.m_Indices.push_back(4);
		mesh.m_Indices.push_back(9);
		mesh.m_Indices.push_back(5);
		mesh.m_Indices.push_back(4);
		mesh.m_Indices.push_back(4);
		mesh.m_Indices.push_back(5);
		mesh.m_Indices.push_back(8);
		mesh.m_Indices.push_back(4);
		mesh.m_Indices.push_back(8);
		mesh.m_Indices.push_back(1);
		mesh.m_Indices.push_back(8);
		mesh.m_Indices.push_back(10);
		mesh.m_Indices.push_back(1);
		mesh.m_Indices.push_back(8);
		mesh.m_Indices.push_back(3);
		mesh.m_Indices.push_back(10);
		mesh.m_Indices.push_back(5);
		mesh.m_Indices.push_back(3);
		mesh.m_Indices.push_back(8);
		mesh.m_Indices.push_back(5);
		mesh.m_Indices.push_back(2);
		mesh.m_Indices.push_back(3);
		mesh.m_Indices.push_back(2);
		mesh.m_Indices.push_back(7);
		mesh.m_Indices.push_back(3);
		mesh.m_Indices.push_back(7);
		mesh.m_Indices.push_back(10);
		mesh.m_Indices.push_back(3);
		mesh.m_Indices.push_back(7);
		mesh.m_Indices.push_back(6);
		mesh.m_Indices.push_back(10);
		mesh.m_Indices.push_back(7);
		mesh.m_Indices.push_back(11);
		mesh.m_Indices.push_back(6);
		mesh.m_Indices.push_back(11);
		mesh.m_Indices.push_back(0);
		mesh.m_Indices.push_back(6);
		mesh.m_Indices.push_back(0);
		mesh.m_Indices.push_back(1);
		mesh.m_Indices.push_back(6);
		mesh.m_Indices.push_back(6);
		mesh.m_Indices.push_back(1);
		mesh.m_Indices.push_back(10);
		mesh.m_Indices.push_back(9);
		mesh.m_Indices.push_back(0);
		mesh.m_Indices.push_back(11);
		mesh.m_Indices.push_back(9);
		mesh.m_Indices.push_back(11);
		mesh.m_Indices.push_back(2);
		mesh.m_Indices.push_back(9);
		mesh.m_Indices.push_back(2);
		mesh.m_Indices.push_back(5);
		mesh.m_Indices.push_back(7);
		mesh.m_Indices.push_back(2);
		mesh.m_Indices.push_back(11);

		for (uint32_t i = 0; i < subdivisions; i++)
		{
			subdivide(mesh);
		}
	}

} // namespace gp1::renderer::meshGenerators
