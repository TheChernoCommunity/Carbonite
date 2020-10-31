//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Renderer.h"

#include <stdint.h>
#include <vector>

namespace gp1 {

	enum class VertexAttribIndex : uint32_t {
		POSITION = 0,
		NORMAL = 1,
		UV = 2,
		SSBO_INDEX = 3,
		JOINT_INDICES = 3,
		JOINT_WEIGHTS = 4
	};

	struct MeshData;

	struct Mesh {
	public:
		virtual ~Mesh();

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

		// Get this mesh's data.
		MeshData* GetMeshData(Renderer* renderer);

		friend MeshData;

	private:
		// Create the custom mesh data.
		virtual MeshData* CreateCustomMeshData(Renderer* renderer) = 0;

	public:
		std::vector<uint32_t> m_Indices;	// This mesh's indices.

	protected:
		bool m_Dirty = true;		// Should this mesh be recreated.
		bool m_Editable = true;		// Is this mesh editable.
		bool m_IsDynamic = false;	// Is this mesh dynamic. (i.e. should the vertices and indices be kept after initialization of GL data)

	private:
		MeshData* m_MeshData = nullptr;	// The renderer specific meshdata.
	};

	struct MeshData {
	public:
		MeshData(Mesh* mesh);
		virtual ~MeshData();

		// Get the renderer type for this mesh data.
		virtual RendererType GetRendererType() const = 0;
		// Clean up this mesh data.
		virtual void CleanUp() = 0;

	protected:
		// Get the mesh this mesh data is part of.
		template <typename T>
		T* GetMesh() const {
			return reinterpret_cast<T*>(this->m_Mesh);
		}

	private:
		Mesh* m_Mesh;
	};

} // namespace gp1
