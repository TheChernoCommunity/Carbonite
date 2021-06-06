//
//	Created by MarcasRealAccount on 14. May. 2021
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Material/Material.h"

#include <cstdint>

namespace gp1::renderer::opengl
{
	struct OpenGLMaterial : public Material
	{
	public:
		virtual ~OpenGLMaterial();

		void Bind();
		void Unbind();
		void UpdateGLData();

	private:
		void CleanUp();

		uint32_t GetGLFace(ETriangleFace face);
		uint32_t GetGLBlendFunc(EBlendFunc blendFunc);
		uint32_t GetGLPolygonMode(EPolygonMode polygonMode);
	};
} // namespace gp1::renderer::opengl

#endif