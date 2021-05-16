//
//	Created by MarcasRealAccount on 16. May. 2021
//

#include "Engine/Renderer/Material/ReservedUniformBuffers.h"

namespace gp1::renderer
{
	ReservedUniformBuffers::ReservedUniformBuffers()
	{
		// TODO(MarcasRealAccount): Maybe move this code somewhere else.
		m_UniformBuffers.reserve(MaxUniformBufferCount);
		m_UniformBuffers.push_back(UniformBuffer("camera", { { "projectionViewMatrix", UniformBuffer::UniformInfo(EUniformType::FMat4) } }));
		m_UniformBuffers.push_back(UniformBuffer("reserved2", {}));
		m_UniformBuffers.push_back(UniformBuffer("reserved3", {}));
		m_UniformBuffers.push_back(UniformBuffer("reserved4", {}));
		m_UniformBuffers.push_back(UniformBuffer("reserved5", {}));
		m_UniformBuffers.push_back(UniformBuffer("reserved6", {}));
		m_UniformBuffers.push_back(UniformBuffer("reserved7", {}));
		m_UniformBuffers.push_back(UniformBuffer("reserved8", {}));
	}

	UniformBuffer* ReservedUniformBuffers::GetUniformBuffer(const std::string& name)
	{
		for (auto& uniformBuffer : m_UniformBuffers)
			if (uniformBuffer.GetName() == name)
				return &uniformBuffer;
		return nullptr;
	}

	const UniformBuffer* ReservedUniformBuffers::GetUniformBuffer(const std::string& name) const
	{
		for (auto& uniformBuffer : m_UniformBuffers)
			if (uniformBuffer.GetName() == name)
				return &uniformBuffer;
		return nullptr;
	}

	std::shared_ptr<Uniform> ReservedUniformBuffers::GetUniform(const std::string& bufferName, const std::string& uniformName) const
	{
		const UniformBuffer* uniformBuffer = GetUniformBuffer(bufferName);
		if (uniformBuffer)
			return uniformBuffer->GetUniform(uniformName);
		return nullptr;
	}
} // namespace gp1::renderer