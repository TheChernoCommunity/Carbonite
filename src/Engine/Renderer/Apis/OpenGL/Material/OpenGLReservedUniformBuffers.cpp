//
//	Created by MarcasRealAccount on 16. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLReservedUniformBuffers.h"

namespace gp1::renderer::opengl
{
	OpenGLReservedUniformBuffers::OpenGLReservedUniformBuffers()
	{
		uint32_t i = 0;
		m_UniformBufferInfos.reserve(m_UniformBuffers.size());
		for (auto& uniformBuffer : m_UniformBuffers)
		{
			OpenGLUniformBufferInfo info = OpenGLUniformBufferInfo(uniformBuffer.GetName(), &uniformBuffer);
			info.m_Binding               = i++;
			m_UniformBufferInfos.push_back(info);
		}
	}

	void OpenGLReservedUniformBuffers::Bind()
	{
		for (auto& uniformBufferInfo : m_UniformBufferInfos)
			uniformBufferInfo.Bind();
	}

	void OpenGLReservedUniformBuffers::CleanUp()
	{
		for (auto& uniformBufferInfo : m_UniformBufferInfos)
			uniformBufferInfo.CleanUp();
	}
} // namespace gp1::renderer::opengl

#endif