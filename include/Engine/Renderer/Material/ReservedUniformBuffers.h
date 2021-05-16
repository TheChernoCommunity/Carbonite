//
//	Created by MarcasRealAccount on 16. May. 2021
//

#pragma once

#include "Engine/Renderer/Material/Uniform.h"

namespace gp1::renderer
{
	struct ReservedUniformBuffers
	{
	public:
		ReservedUniformBuffers();
		virtual ~ReservedUniformBuffers() = default;

		inline uint32_t GetCount() const
		{
			return static_cast<uint32_t>(m_UniformBuffers.size());
		}

		UniformBuffer*           GetUniformBuffer(const std::string& name);
		const UniformBuffer*     GetUniformBuffer(const std::string& name) const;
		std::shared_ptr<Uniform> GetUniform(const std::string& bufferName, const std::string& uniformName) const;

	public:
		static constexpr const uint32_t MaxUniformBufferCount = 8;

	protected:
		std::vector<UniformBuffer> m_UniformBuffers;
	};
} // namespace gp1::renderer