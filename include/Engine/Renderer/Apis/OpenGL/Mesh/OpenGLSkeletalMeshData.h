//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Mesh/SkeletalMesh.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLMeshData.h"

namespace gp1 {

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
