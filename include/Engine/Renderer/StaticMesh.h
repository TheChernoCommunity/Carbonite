//	
//	Created by MarcasRealAccount on 30. Oct. 2020
//	

#include "Engine/Renderer/Mesh.h"

namespace gp1 {

	struct StaticMeshVertex {
		struct { float x, y, z; } position{ 0.0f, 0.0f, 0.0f };
		struct { float x, y, z; } normal{ 0.0f, 0.0f, 0.0f };
		struct { float x, y; } uv{ 0.0f, 0.0f };
	};

	struct StaticMesh : public Mesh {
	private:
		virtual MeshData* CreateCustomMeshData(Renderer* renderer) override;

	public:
		std::vector<StaticMeshVertex> m_Vertices;	// This mesh's vertices.
	};

	struct OpenGLStaticMeshData : public OpenGLMeshData {
	public:
		OpenGLStaticMeshData(Mesh* mesh);

	private:
		bool HasVertices() override;
		uint32_t GetCustomDataSize() override;
		void InitCustomGLData() override;
		void ClearCustomData() override;
	};

} // namespace gp1
