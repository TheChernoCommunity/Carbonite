//
//	Created by MarcasRealAccount on 16. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLReservedUniformBuffers.h"
#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLUniformBuffer.h"

namespace gp1::renderer::opengl
{
	OpenGLReservedUniformBuffers::OpenGLReservedUniformBuffers()
	{
		// INFO(MarcasRealAccount): Set the offsets based on the std140 layout.
		uint32_t i = 0;
		for (auto& uniformBuffer : m_UniformBuffers)
		{
			if (uniformBuffer.m_UniformBuffer)
			{
				OpenGLUniformBuffer* buffer = reinterpret_cast<OpenGLUniformBuffer*>(uniformBuffer.m_UniformBuffer.get());
				buffer->SetBinding(i++);
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
				OpenGLUniformBuffer* buffer = reinterpret_cast<OpenGLUniformBuffer*>(uniformBuffer.m_UniformBuffer.get());
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
				OpenGLUniformBuffer* buffer = reinterpret_cast<OpenGLUniformBuffer*>(uniformBuffer.m_UniformBuffer.get());
				buffer->CleanUp();
			}
		}
	}
} // namespace gp1::renderer::opengl

#endif