//
//	Created by MarcasRealAccount on 19. May. 2021.
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Material/UniformBuffer.h"

#include <vector>

namespace gp1::renderer::opengl
{
	struct OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		virtual ~OpenGLUniformBuffer();

		void Bind();
		void CleanUp();

		void SetBinding(uint32_t newBinding);
		void SetOffsets(std::vector<std::pair<std::string, uint32_t>> offsets);

	private:
		uint32_t m_Ubo     = 0;
		uint32_t m_UboSize = 0;
		uint32_t m_Binding = 0;
	};
} // namespace gp1::renderer::opengl
#endif