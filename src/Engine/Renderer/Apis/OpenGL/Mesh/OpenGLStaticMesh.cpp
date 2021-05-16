//
//	Created by MarcasRealAccount on 13. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLStaticMesh.h"

#include <glad/glad.h>

namespace gp1::renderer::opengl
{
	OpenGLStaticMesh::~OpenGLStaticMesh()
	{
		if (m_Vao)
			CleanUp();
	}

	void OpenGLStaticMesh::Render()
	{
		if (m_Dirty)
		{
			if (m_Vao)
				CleanUp();

			GenGLData();
			m_Dirty = false;
		}

		if (m_RenderMode == RenderMode::Points)
			glPointSize(m_LineWidth);
		else
			glLineWidth(m_LineWidth);

		glBindVertexArray(m_Vao);

		if (m_HasIndices)
			glDrawElements(GetGLRenderMode(m_RenderMode), m_BufferSize, GL_UNSIGNED_INT, nullptr);
		else
			glDrawArrays(GetGLRenderMode(m_RenderMode), 0, m_BufferSize);

		glBindVertexArray(0);

		glPointSize(1.0f);
		glLineWidth(1.0f);
	}

	void OpenGLStaticMesh::GenGLData()
	{
		glGenVertexArrays(1, &m_Vao);
		glBindVertexArray(m_Vao);

		m_HasIndices = m_Indices.size() > 0;

		glGenBuffers(m_HasIndices ? 2 : 1, m_Vbos);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(StaticMeshVertex) * m_Vertices.size(), m_Vertices.data(), m_Dynamic && m_Editable ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(StaticMeshVertex), reinterpret_cast<const void*>(offsetof(StaticMeshVertex, m_Position)));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(StaticMeshVertex), reinterpret_cast<const void*>(offsetof(StaticMeshVertex, m_Normal)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(StaticMeshVertex), reinterpret_cast<const void*>(offsetof(StaticMeshVertex, m_Uv)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (m_HasIndices)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Vbos[1]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_Indices.size(), m_Indices.data(), m_Dynamic && m_Editable ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

			m_BufferSize = static_cast<uint32_t>(m_Indices.size());
		}
		else
		{
			m_BufferSize = static_cast<uint32_t>(m_Vertices.size());
		}
		glBindVertexArray(0);

		if (!m_Editable || !m_Dynamic)
		{
			m_Vertices.clear();
			m_Indices.clear();
		}
	}

	void OpenGLStaticMesh::CleanUp()
	{
		glDeleteVertexArrays(1, &m_Vao);
		glDeleteBuffers(m_HasIndices ? 2 : 1, m_Vbos);
		m_Vao        = 0;
		m_Vbos[0]    = 0;
		m_Vbos[1]    = 0;
		m_BufferSize = 0;
		m_HasIndices = false;
	}
} // namespace gp1::renderer::opengl

#endif