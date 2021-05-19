//
//	Created by MarcasRealAccount on 19. May. 2021.
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLUniform.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLUniformBuffer.h"

#include <glad/glad.h>

namespace gp1::renderer::opengl
{
	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		CleanUp();
	}

	void OpenGLUniformBuffer::Bind()
	{
		if (IsDirty())
		{
			if (!m_Ubo)
			{
				glGenBuffers(1, &m_Ubo);
				m_UboSize = 0;
			}

			std::vector<uint8_t> uniformData;
			size_t               size = 0;
			for (size_t i = 0; i < m_Uniforms.size(); i++)
			{
				auto&          uniform    = m_Uniforms[i];
				OpenGLUniform* oglUniform = uniform.m_Uniform->GetNext<OpenGLUniform>();

				if (!oglUniform->IsTexture())
				{
					size_t end = oglUniform->m_Offset + oglUniform->GetDataSize();
					if (end > size)
						size = end;
				}
			}
			uniformData.resize(size);
			for (size_t i = 0; i < m_Uniforms.size(); i++)
			{
				auto&          uniform    = m_Uniforms[i];
				OpenGLUniform* oglUniform = uniform.m_Uniform->GetNext<OpenGLUniform>();
				if (!oglUniform->IsTexture())
					oglUniform->PutData(uniformData);
			}

			if (uniformData.size() != m_UboSize)
			{
				glBindBuffer(GL_UNIFORM_BUFFER, m_Ubo);
				glBufferData(GL_UNIFORM_BUFFER, uniformData.size(), uniformData.data(), GL_DYNAMIC_DRAW);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
				m_UboSize = static_cast<uint32_t>(uniformData.size());
			}
			else
			{
				glBindBuffer(GL_UNIFORM_BUFFER, m_Ubo);
				glBufferSubData(GL_UNIFORM_BUFFER, 0, uniformData.size(), uniformData.data());
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}
			ClearDirty();
		}

		glBindBufferBase(GL_UNIFORM_BUFFER, m_Binding, m_Ubo);

		for (auto& uniform : m_Uniforms)
		{
			OpenGLUniform* oglUniform = uniform.m_Uniform->GetNext<OpenGLUniform>();
			if (oglUniform->IsTexture())
			{
				OpenGLUniformTexture* textureUniform = oglUniform->GetNext<OpenGLUniformTexture>();
				textureUniform->Bind();
			}
		}
	}

	void OpenGLUniformBuffer::CleanUp()
	{
		glDeleteBuffers(1, &m_Ubo);
		m_Ubo     = 0;
		m_UboSize = 0;
	}

	void OpenGLUniformBuffer::SetBinding(uint32_t newBinding)
	{
		m_Binding = newBinding;
	}

	void OpenGLUniformBuffer::SetOffsets(std::vector<std::pair<std::string, uint32_t>> offsets)
	{
		for (size_t i = 0; i < m_Uniforms.size(); i++)
		{
			auto& uniform = m_Uniforms[i];
			for (auto itr = offsets.begin(), end = offsets.end(); itr != end;)
			{
				if (itr->first == uniform.m_Name)
				{
					uniform.m_Uniform->GetNext<OpenGLUniform>()->m_Offset = itr->second;
					offsets.erase(itr);
					break;
				}
				itr++;
			}
		}
	}
} // namespace gp1::renderer::opengl
#endif