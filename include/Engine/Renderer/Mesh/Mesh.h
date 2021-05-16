//
//	Created by MarcasRealAccount on 13. May. 2021
//

#pragma once

#include "Engine/Renderer/RendererData.h"

#include <cstdint>

namespace gp1::renderer
{
	enum class ERenderMode : uint32_t
	{
		Points,
		LineStrip,
		LineLoop,
		Lines,
		LineStripAdjacency,
		LinesAdjacency,
		TriangleStrip,
		TriangleFan,
		Triangles,
		TriangleStripAdjacency,
		TrianglesAdjacency,
		Patches
	};

	struct Mesh : public RendererData
	{
	public:
		virtual ~Mesh() = default;

	public:
		ERenderMode m_RenderMode = ERenderMode::Triangles;
		float      m_LineWidth  = 1.0f;
	};
} // namespace gp1::renderer