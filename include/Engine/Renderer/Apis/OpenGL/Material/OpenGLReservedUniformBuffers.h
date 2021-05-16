//
//	Created by MarcasRealAccount on 16. May. 2021
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLMaterial.h"
#include "Engine/Renderer/Material/ReservedUniformBuffers.h"

namespace gp1::renderer::opengl
{
	struct OpenGLReservedUniformBuffers : public ReservedUniformBuffers
	{
	public:
		OpenGLReservedUniformBuffers();

		void Bind();

		void CleanUp();

	private:
		std::vector<OpenGLUniformBufferInfo> m_UniformBufferInfos;
	};
} // namespace gp1::renderer::opengl

#endif