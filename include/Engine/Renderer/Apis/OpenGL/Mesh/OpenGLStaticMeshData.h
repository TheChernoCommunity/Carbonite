//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Mesh/StaticMesh.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLMeshData.h"

namespace gp1 {

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
