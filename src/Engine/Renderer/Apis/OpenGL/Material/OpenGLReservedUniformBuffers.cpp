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
		OpenGLUniformBuffer* cameraBuffer = reinterpret_cast<OpenGLUniformBuffer*>(m_UniformBuffers[0].m_UniformBuffer.get());
		cameraBuffer->SetBinding(0);
		cameraBuffer->SetOffsets({ { "projectionViewMatrix", 0 }, { "projectionMatrix", 64 }, { "viewMatrix", 128 } });
		/*OpenGLUniformBuffer* camera2DBuffer = reinterpret_cast<OpenGLUniformBuffer*>(m_UniformBuffers[1].m_UniformBuffer.get());
		cameraBuffer->SetBinding(1);
		camera2DBuffer->SetOffsets({ { "projectionMatrix", 0 }, { "windowSize", 64 } });*/
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

	bool OpenGLReservedUniformBuffers::GetBinding(std::string name, size_t& binding) const
	{
		for (size_t i = 0; i < ReservedUniformBuffers::MaxUniformBufferCount; i++)
		{
			auto& uniformBuffer = m_UniformBuffers[i];
			if (uniformBuffer.m_Name == name)
			{
				binding = i;
				return true;
			}
		}
		binding = 0;
		return false;
	}
} // namespace gp1::renderer::opengl

#endif