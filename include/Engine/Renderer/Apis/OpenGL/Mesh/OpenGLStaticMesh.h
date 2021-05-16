//
//	Created by MarcasRealAccount on 13. May. 2021
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLMesh.h"
#include "Engine/Renderer/Mesh/StaticMesh.h"

namespace gp1::renderer::opengl
{
	struct OpenGLStaticMesh : public StaticMesh, public OpenGLMesh
	{
	public:
		OpenGLStaticMesh();
		virtual ~OpenGLStaticMesh();

		virtual void Render() override;

	private:
		void GenGLData();
		void CleanUp();

	protected:
		uint32_t m_Vao = 0;
		uint32_t m_Vbos[2] { 0, 0 };
		uint32_t m_BufferSize = 0;
		bool     m_HasIndices = false;
	};
} // namespace gp1::renderer::opengl

#endif