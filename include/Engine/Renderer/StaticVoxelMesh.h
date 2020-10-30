//	
//	Created by MarcasRealAccount on 30. Oct. 2020
//	

#include "Engine/Renderer/Mesh.h"

namespace gp1 {

	struct StaticVoxelMeshVertex {
		struct { float x, y, z; } position{ 0.0f, 0.0f, 0.0f };
		struct { float x, y, z; } normal{ 0.0f, 0.0f, 0.0f };
		struct { float x, y; } uv{ 0.0f, 0.0f };
		uint32_t SSBOIndex = 0;
	};

	struct StaticVoxelMesh : public Mesh {
	private:
		virtual MeshData* CreateCustomMeshData(Renderer* renderer) override;

	public:
		std::vector<StaticVoxelMeshVertex> m_Vertices;	// This mesh's vertices.
	};

	struct OpenGLStaticVoxelMeshData : public OpenGLMeshData {
	public:
		OpenGLStaticVoxelMeshData(Mesh* mesh);

	private:
		bool HasVertices() override;
		uint32_t GetCustomDataSize() override;
		void InitCustomGLData() override;
		void ClearCustomData() override;
	};

} // namespace gp1
