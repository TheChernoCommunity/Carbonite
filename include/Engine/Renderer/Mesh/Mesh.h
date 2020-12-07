//
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#pragma once

#include "Engine/Renderer/RendererData.h"

#include <stdint.h>
#include <type_traits>
#include <vector>

namespace gp1::renderer::mesh
{
	enum class VertexAttribIndex : uint32_t
	{
		POSITION      = 0,
		NORMAL        = 1,
		UV            = 2,
		SSBO_INDEX    = 3,
		JOINT_INDICES = 3,
		JOINT_WEIGHTS = 4
	};

	enum class RenderMode : uint32_t
	{
		POINTS,
		LINE_STRIP,
		LINE_LOOP,
		LINES,
		LINE_STRIP_ADJANCENCY,
		LINES_ADJACENCY,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		TRIANGLES,
		TRIANGLE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY,
		PATCHES
	};

	struct Mesh : public Data
	{
	public:
		template <typename T>
		Mesh(T* ptr)
		    : Data(ptr)
		{
		}

		// Mark this mesh dirty for recreation.
		void MarkDirty();
		// Clears this mesh's dirtiness.
		void ClearDirty();
		// Is this mesh dirty.
		bool IsDirty();

		// Is the mesh editable.
		bool IsEditable();
		// Is the mesh dynamic.
		bool IsDynamic();

	public:
		std::vector<uint32_t> m_Indices; // This mesh's indices.

		RenderMode m_RenderMode = RenderMode::TRIANGLES; // The render mode.
		float      m_LineWidth  = 1.0f;                  // The line width of this mesh if rendered with points or lines.

	protected:
		bool m_Dirty     = true;  // Should this mesh be recreated.
		bool m_Editable  = true;  // Is this mesh editable.
		bool m_IsDynamic = false; // Is this mesh dynamic. (i.e. should the vertices and indices be kept after initialization of the GL data)
	};

} // namespace gp1::renderer::mesh
