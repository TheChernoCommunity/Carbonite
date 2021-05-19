//
//	Created by MarcasRealAccount on 19. May. 2021
//

#pragma once

#include "Engine/Renderer/Material/Uniform.h"
#include "Engine/Renderer/RendererData.h"

#include <memory>
#include <string>
#include <vector>

namespace gp1::renderer
{
	struct UniformBuffer : RendererData
	{
	public:
		struct UniformInfo
		{
		public:
			std::string              m_Name;
			std::shared_ptr<Uniform> m_Uniform;
		};

		static std::shared_ptr<UniformBuffer> Create();

	public:
		void UpdateUniforms(std::vector<std::pair<std::string, EUniformType>> uniformTypes);

		bool IsDirty() const;
		void ClearDirty();

		std::shared_ptr<Uniform> GetUniform(std::string_view name) const;
		template <typename T, std::enable_if_t<std::is_base_of_v<Uniform, T>, bool> = true>
		std::shared_ptr<T> GetUniform(std::string_view name) const
		{
			return std::reinterpret_pointer_cast<T>(GetUniform(name));
		}

	protected:
		UniformBuffer() = default;

	protected:
		std::vector<UniformInfo> m_Uniforms;
	};
} // namespace gp1::renderer