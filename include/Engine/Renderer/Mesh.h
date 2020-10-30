//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Renderer.h"

#include <stdint.h>
#include <vector>

#include <glad/glad.h>

namespace gp1 {

	class Renderer;
	class OpenGLRenderer;

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
		Mesh* GetMesh() const;

	private:
		Mesh* m_Mesh;
	};

	struct OpenGLMeshData : public MeshData {
	public:
		OpenGLMeshData(Mesh* mesh);

		virtual RendererType GetRendererType() const override;

		// Does this mesh have vertices.
		virtual bool HasVertices() = 0;
		// Get the custom data size.
		virtual uint32_t GetCustomDataSize() = 0;
		// Initialize custom gl data.
		virtual void InitCustomGLData() = 0;
		// Clear custom gl data.
		virtual void ClearCustomData() = 0;

		// Does this mesh have indices.
		bool HasIndices();
		// Get this mesh's vao.
		uint32_t GetVAO();
		// Initialize gl data.
		void InitGLData();
		virtual void CleanUp() override;

		friend OpenGLRenderer;

	protected:
		// Create vbos.
		void CreateVBOs(uint8_t count);
		// Create attribs.
		void CreateVertexAttribArrays(uint8_t count);

		// Bind next vbo.
		void BindNextVBO(GLenum bufferType);
		// Unbind vbo.
		void UnbindVBO(GLenum bufferType);

		// Set and enable attrib pointer.
		void SetVertexAttribPointer(uint32_t index, uint32_t size, GLenum type, bool normalized, uint64_t stride, uint64_t offset);
		// Set and enable attrib pointer.
		void SetVertexAttribIPointer(uint32_t index, uint32_t size, GLenum type, uint64_t stride, uint64_t offset);
		// Set and enable attrib pointer.
		void SetVertexAttribLPointer(uint32_t index, uint32_t size, GLenum type, uint64_t stride, uint64_t offset);

	protected:
		uint32_t m_VAO = 0;						// This mesh's VAO.
		uint8_t m_NumVBOs = 0;					// The number of VBOs that this mesh has.
		uint8_t m_CurrentVBO = 0;				// The current VBO.
		uint32_t* m_VBOs = nullptr;				// This mesh's VBOs.
		uint8_t m_NumAttribs = 0;				// The number of enabled vertex attribs this mesh has.
		uint8_t m_CurrentAttrib = 0;			// The current vertex attrib.
		uint32_t* m_EnabledAttribs = nullptr;	// The vertex attribs that have been enabled for this mesh.
		uint32_t m_BufferSize = 0;				// This mesh's Buffer Size. (i.e. the number of vertices/indices)
		bool m_HasIndices = false;				// Does this mesh have indices.
	};

} // namespace gp1
