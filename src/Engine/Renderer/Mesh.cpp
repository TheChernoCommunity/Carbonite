//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Mesh.h"

namespace gp1 {

	Mesh::~Mesh() {
		CleanUpGLData();
	}

	void Mesh::MarkDirty() {
		this->m_Dirty = true;
	}

	uint32_t Mesh::GetVAO() {
		if (this->m_Dirty)
			InitGLData();
		return this->m_VAO;
	}

	void Mesh::InitGLData() {
		if (this->m_VAO)
			CleanUpGLData();

		if (m_Vertices.size() == 0)
			return;

		this->m_HasIndices = m_Indices.size() > 0;

		glGenVertexArrays(1, &this->m_VAO);
		glBindVertexArray(this->m_VAO);
		glGenBuffers(1 + this->m_HasIndices, this->m_VBOs);

		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, this->m_Vertices.size() * sizeof(Vertex), this->m_Vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (this->m_HasIndices) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_VBOs[1]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_Indices.size() * sizeof(uint32_t), this->m_Indices.data(), GL_STATIC_DRAW);
			this->m_BufferSize = (uint32_t)this->m_Indices.size();
		} else {
			this->m_BufferSize = (uint32_t)this->m_Vertices.size();
		}

		glBindVertexArray(0);

		if (!this->m_IsDynamic) {
			this->m_Vertices.clear();
			this->m_Indices.clear();
		}
		this->m_Dirty = false;
	}

	void Mesh::CleanUpGLData() {
		if (this->m_VAO)
			glDeleteVertexArrays(1, &this->m_VAO);
		glDeleteBuffers(1 + this->m_HasIndices, this->m_VBOs);
		this->m_VAO = 0;
		this->m_VBOs[0] = 0;
		this->m_VBOs[1] = 0;
		this->m_BufferSize = 0;
		this->m_HasIndices = false;
	}

} // namespace gp1
