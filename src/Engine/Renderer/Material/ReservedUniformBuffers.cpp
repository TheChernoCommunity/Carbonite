//
//	Created by MarcasRealAccount on 16. May. 2021
//

#include "Engine/Renderer/Material/ReservedUniformBuffers.h"

namespace gp1::renderer
{
	ReservedUniformBuffers::ReservedUniformBuffers()
	{
		// TODO(MarcasRealAccount): Maybe move this code somewhere else.
		m_UniformBuffers[0] = { "Camera", UniformBuffer::Create() };
		m_UniformBuffers[0].m_UniformBuffer->UpdateUniforms({ { "projectionViewMatrix", EUniformType::FMat4 }, { "projectionMatrix", EUniformType::FMat4 }, { "viewMatrix", EUniformType::FMat4 } });
		m_UniformBuffers[1] = { "Reserved2", nullptr };
		m_UniformBuffers[2] = { "Reserved3", nullptr };
		m_UniformBuffers[3] = { "Reserved4", nullptr };
		m_UniformBuffers[4] = { "Reserved5", nullptr };
		m_UniformBuffers[5] = { "Reserved6", nullptr };
		m_UniformBuffers[6] = { "Reserved7", nullptr };
		m_UniformBuffers[7] = { "Reserved8", nullptr };
	}

	std::shared_ptr<UniformBuffer> ReservedUniformBuffers::GetUniformBuffer(const std::string& name) const
	{
		for (auto& uniformBuffer : m_UniformBuffers)
			if (uniformBuffer.m_Name == name)
				return uniformBuffer.m_UniformBuffer;
		return nullptr;
	}

	std::shared_ptr<Uniform> ReservedUniformBuffers::GetUniform(const std::string& bufferName, const std::string& uniformName) const
	{
		std::shared_ptr<UniformBuffer> uniformBuffer = GetUniformBuffer(bufferName);
		if (uniformBuffer)
			return uniformBuffer->GetUniform(uniformName);
		return nullptr;
	}
} // namespace gp1::renderer