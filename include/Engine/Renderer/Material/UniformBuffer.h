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
			std::unique_ptr<Uniform> m_Uniform;
		};

		static std::unique_ptr<UniformBuffer> Create();

	public:
		void UpdateUniforms(std::vector<std::pair<std::string, EUniformType>> uniformTypes);

		bool IsDirty() const;
		void ClearDirty();

		Uniform* GetUniform(std::string_view name) const;
		template <typename T, std::enable_if_t<std::is_base_of_v<Uniform, T>, bool> = true>
		T* GetUniform(std::string_view name) const
		{
			return reinterpret_cast<T*>(GetUniform(name));
		}

	protected:
		UniformBuffer() = default;

	protected:
		std::vector<UniformInfo> m_Uniforms;
	};
} // namespace gp1::renderer