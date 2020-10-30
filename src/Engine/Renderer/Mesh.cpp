//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Mesh.h"

namespace gp1 {

	Mesh::~Mesh() {
		if (this->m_MeshData) {
			this->m_MeshData->CleanUp();
			delete this->m_MeshData;
		}
	}

	void Mesh::MarkDirty() {
		this->m_Dirty = this->m_Editable;
	}

	void Mesh::ClearDirty() {
		this->m_Dirty = false;
	}

	bool Mesh::IsDirty() {
		return this->m_Dirty;
	}

	bool Mesh::IsEditable() {
		return this->m_Editable;
	}

	bool Mesh::IsDynamic() {
		return this->m_IsDynamic;
	}

	MeshData* Mesh::GetMeshData(Renderer* renderer) {
		if (!this->m_MeshData || !renderer->IsMeshDataUsable(this->m_MeshData)) {
			if (this->m_MeshData) {
				this->m_MeshData->CleanUp();
				delete this->m_MeshData;
			}
			this->m_MeshData = CreateCustomMeshData(renderer);
		}
		return this->m_MeshData;
	}

	MeshData::MeshData(Mesh* mesh)
		: m_Mesh(mesh) {}

	MeshData::~MeshData() {
		this->m_Mesh->m_MeshData = nullptr;
	}

	Mesh* MeshData::GetMesh() const {
		return this->m_Mesh;
	}

	OpenGLMeshData::OpenGLMeshData(Mesh* mesh)
		: MeshData(mesh) {}

	RendererType OpenGLMeshData::GetRendererType() const {
		return RendererType::OPENGL;
	}

	bool OpenGLMeshData::HasIndices() {
		return this->m_HasIndices;
	}

	uint32_t OpenGLMeshData::GetVAO() {
		if (GetMesh()->IsDirty())
			InitGLData();
		return this->m_VAO;
	}

	void OpenGLMeshData::InitGLData() {
		if (this->m_VAO)
			CleanUp();

		if (!HasVertices())
			return;

		this->m_HasIndices = GetMesh()->m_Indices.size() > 0;

		glGenVertexArrays(1, &this->m_VAO);
		glBindVertexArray(this->m_VAO);

		this->m_NumVBOs = static_cast<uint32_t>(this->m_HasIndices);

		InitCustomGLData();

		if (this->m_HasIndices) {
			BindNextVBO(GL_ELEMENT_ARRAY_BUFFER);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetMesh()->m_Indices.size() * sizeof(uint32_t), GetMesh()->m_Indices.data(), GL_STATIC_DRAW);
			this->m_BufferSize = static_cast<uint32_t>(GetMesh()->m_Indices.size());
		} else {
			this->m_BufferSize = GetCustomDataSize();
		}

		glBindVertexArray(0);

		if (!GetMesh()->IsEditable() || !GetMesh()->IsDynamic()) {
			ClearCustomData();
			GetMesh()->m_Indices.clear();
		}
		GetMesh()->ClearDirty();
	}

	void OpenGLMeshData::CleanUp() {
		if (this->m_VAO) {
			glDeleteVertexArrays(1, &this->m_VAO);
			this->m_VAO = 0;
		}
		if (this->m_VBOs) {
			glDeleteBuffers(this->m_NumVBOs, this->m_VBOs);
			delete[] this->m_VBOs;
			this->m_VBOs = nullptr;
			this->m_NumVBOs = 0;
			this->m_CurrentVBO = 0;
		}
		if (this->m_EnabledAttribs) {
			delete[] this->m_EnabledAttribs;
			this->m_EnabledAttribs = nullptr;
			this->m_NumAttribs = 0;
			this->m_CurrentAttrib = 0;
		}
		this->m_BufferSize = 0;
		this->m_HasIndices = false;
	}

	void OpenGLMeshData::CreateVBOs(uint8_t count) {
		if (this->m_VBOs) {
			glDeleteBuffers(this->m_NumVBOs, this->m_VBOs);
			delete[] this->m_VBOs;
			this->m_VBOs = nullptr;
			this->m_NumVBOs = 0;
			this->m_CurrentVBO = 0;
		}
		this->m_NumVBOs = count;
		this->m_VBOs = new uint32_t[count];
		glGenBuffers(this->m_NumVBOs, this->m_VBOs);
	}

	void OpenGLMeshData::CreateVertexAttribArrays(uint8_t count) {
		if (this->m_EnabledAttribs) {
			delete[] this->m_EnabledAttribs;
		}
		this->m_NumAttribs = count;
		this->m_EnabledAttribs = new uint32_t[count];
	}

	void OpenGLMeshData::BindNextVBO(GLenum bufferType) {
		glBindBuffer(bufferType, this->m_VBOs[this->m_CurrentVBO]);
		this->m_CurrentVBO++;
	}

	void OpenGLMeshData::UnbindVBO(GLenum bufferType) {
		glBindBuffer(bufferType, 0);
	}

	void OpenGLMeshData::SetVertexAttribPointer(uint32_t index, uint32_t size, GLenum type, bool normalized, uint64_t stride, uint64_t offset) {
		if (this->m_CurrentAttrib > this->m_NumAttribs)
			return;

		glVertexAttribPointer(static_cast<GLuint>(index), static_cast<GLint>(size), type, static_cast<GLboolean>(normalized), static_cast<GLsizei>(stride), reinterpret_cast<void*>(offset));
		this->m_EnabledAttribs[this->m_CurrentAttrib] = index;
		this->m_CurrentAttrib++;
	}

	void OpenGLMeshData::SetVertexAttribIPointer(uint32_t index, uint32_t size, GLenum type, uint64_t stride, uint64_t offset) {
		if (this->m_CurrentAttrib > this->m_NumAttribs)
			return;

		glVertexAttribIPointer(static_cast<GLuint>(index), static_cast<GLint>(size), type, static_cast<GLsizei>(stride), reinterpret_cast<void*>(offset));
		this->m_EnabledAttribs[this->m_CurrentAttrib] = index;
		this->m_CurrentAttrib++;
	}

	void OpenGLMeshData::SetVertexAttribLPointer(uint32_t index, uint32_t size, GLenum type, uint64_t stride, uint64_t offset) {
		if (this->m_CurrentAttrib > this->m_NumAttribs)
			return;

		glVertexAttribLPointer(static_cast<GLuint>(index), static_cast<GLint>(size), type, static_cast<GLsizei>(stride), reinterpret_cast<void*>(offset));
		this->m_EnabledAttribs[this->m_CurrentAttrib] = index;
		this->m_CurrentAttrib++;
	}

} // namespace gp1
