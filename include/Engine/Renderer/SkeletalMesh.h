//	
//	Created by MarcasRealAccount on 30. Oct. 2020
//	

#include "Engine/Renderer/Mesh.h"

namespace gp1 {

	struct SkeletalMeshVertex {
		struct { float x, y, z; } position{ 0.0f, 0.0f, 0.0f };
		struct { float x, y, z; } normal{ 0.0f, 0.0f, 0.0f };
		struct { float x, y; } uv{ 0.0f, 0.0f };
		struct { uint32_t x, y, z; } jointIndices{ 0, 0, 0 };
		struct { float x, y, z; } jointWeights{ 0.0f, 0.0f, 0.0f };
	};

	struct SkeletalMesh : public Mesh {
	private:
		virtual MeshData* CreateCustomMeshData(Renderer* renderer) override;

	public:
		std::vector<SkeletalMeshVertex> m_Vertices;	// This mesh's vertices.
	};

	struct OpenGLSkeletalMeshData : public OpenGLMeshData {
	public:
		OpenGLSkeletalMeshData(Mesh* mesh);

	private:
		bool HasVertices() override;
		uint32_t GetCustomDataSize() override;
		void InitCustomGLData() override;
		void ClearCustomData() override;
	};

} // namespace gp1
