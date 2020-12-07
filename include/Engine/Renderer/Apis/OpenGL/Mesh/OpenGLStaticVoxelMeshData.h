//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#pragma once
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLMeshData.h"
#include "Engine/Renderer/Mesh/StaticVoxelMesh.h"

namespace gp1::renderer::apis::opengl::mesh
{
	struct OpenGLStaticVoxelMeshData : public OpenGLMeshData
	{
	public:
		OpenGLStaticVoxelMeshData(renderer::mesh::StaticVoxelMesh* staticVoxelMesh);

	private:
		bool     HasVertices() override;
		uint32_t GetCustomDataSize() override;
		void     InitCustomGLData() override;
		void     ClearCustomData() override;
	};

} // namespace gp1::renderer::apis::opengl::mesh
