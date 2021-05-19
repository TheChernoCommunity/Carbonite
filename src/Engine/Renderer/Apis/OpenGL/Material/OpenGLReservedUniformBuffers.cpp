//
//	Created by MarcasRealAccount on 16. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLReservedUniformBuffers.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLUniform.h"

namespace gp1::renderer::opengl
{
	OpenGLReservedUniformBuffers::OpenGLReservedUniformBuffers()
	{
		uint32_t i = 0;
		for (auto& uniformBuffer : m_UniformBuffers)
		{
			if (uniformBuffer.m_UniformBuffer)
			{
				std::shared_ptr<OpenGLUniformBuffer> buffer = std::reinterpret_pointer_cast<OpenGLUniformBuffer>(uniformBuffer.m_UniformBuffer);
				buffer->SetBinding(i++);
				// TODO(MarcasRealAccount): Set the offsets based on the std140 layout.
				buffer->SetOffsets({ { "projectionViewMatrix", 0 }, { "projectionMatrix", 64 }, { "viewMatrix", 128 } });
			}
		}
	}

	OpenGLReservedUniformBuffers::~OpenGLReservedUniformBuffers()
	{
		CleanUp();
	}

	void OpenGLReservedUniformBuffers::Bind()
	{
		for (auto& uniformBuffer : m_UniformBuffers)
		{
			if (uniformBuffer.m_UniformBuffer)
			{
				std::shared_ptr<OpenGLUniformBuffer> buffer = std::reinterpret_pointer_cast<OpenGLUniformBuffer>(uniformBuffer.m_UniformBuffer);
				buffer->Bind();
			}
		}
	}

	void OpenGLReservedUniformBuffers::CleanUp()
	{
		for (auto& uniformBuffer : m_UniformBuffers)
		{
			if (uniformBuffer.m_UniformBuffer)
			{
				std::shared_ptr<OpenGLUniformBuffer> buffer = std::reinterpret_pointer_cast<OpenGLUniformBuffer>(uniformBuffer.m_UniformBuffer);
				buffer->CleanUp();
			}
		}
	}
} // namespace gp1::renderer::opengl

#endif