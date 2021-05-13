#pragma once

#include "Engine/Renderer/RendererData.h"

#include <cstdint>

namespace gp1::renderer
{
	enum class RenderMode : uint32_t
	{
		POINTS,
		LINE_STRIP,
		LINE_LOOP,
		LINES,
		LINE_STRIP_ADJACENCY,
		LINES_ADJACENCY,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		TRIANGLES,
		TRIANGLE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY,
		PATCHES
	};

	struct Mesh : public RendererData
	{
	public:
		virtual ~Mesh() = default;

	public:
		RenderMode m_RenderMode = RenderMode::TRIANGLES;
		float      m_LineWidth  = 1.0f;
	};
} // namespace gp1::renderer