//
//	Created by MarcasRealAccount on 16. May. 2021
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Material/ReservedUniformBuffers.h"

namespace gp1::renderer::opengl
{
	struct OpenGLReservedUniformBuffers : public ReservedUniformBuffers
	{
	public:
		OpenGLReservedUniformBuffers();
		virtual ~OpenGLReservedUniformBuffers();

		void Bind();
		void CleanUp();

		bool GetBinding(std::string name, size_t& binding) const;
	};
} // namespace gp1::renderer::opengl

#endif