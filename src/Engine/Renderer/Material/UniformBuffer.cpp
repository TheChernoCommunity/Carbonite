#include "Engine/Renderer/Material/UniformBuffer.h"

#include "Engine/Application.h"

namespace gp1::renderer
{
	std::unique_ptr<UniformBuffer> UniformBuffer::Create()
	{
		return Application::GetInstance()->GetRenderer()->CreateUniformBuffer();
	}

	void UniformBuffer::UpdateUniforms(std::vector<std::pair<std::string, EUniformType>> uniformTypes)
	{
		{
			std::vector<std::string> seenUniformNames;
			for (auto itr = uniformTypes.begin(); itr != uniformTypes.end();)
			{
				bool found = false;
				for (auto seenItr = seenUniformNames.begin(), end = seenUniformNames.end(); seenItr != end; seenItr++)
				{
					if (*seenItr == itr->first)
					{
						found = true;
						break;
					}
				}

				if (found)
				{
					itr = uniformTypes.erase(itr);
				}
				else
				{
					seenUniformNames.push_back(itr->first);
					itr++;
				}
			}
		}

		for (auto itr = m_Uniforms.begin(); itr != m_Uniforms.end();)
		{
			bool found = false;
			for (auto typeItr = uniformTypes.begin(), end = uniformTypes.end(); typeItr != end; typeItr++)
			{
				if (typeItr->first == itr->m_Name)
				{
					auto& uniform = itr->m_Uniform;
					if (uniform->GetType() != typeItr->second)
						itr->m_Uniform = Uniform::Create(typeItr->second);
					uniformTypes.erase(typeItr);
					found = true;
					break;
				}
			}

			if (found)
				itr++;
			else
				itr = m_Uniforms.erase(itr);
		}

		for (auto& uniformType : uniformTypes)
			m_Uniforms.push_back({ uniformType.first, Uniform::Create(uniformType.second) });
	}

	bool UniformBuffer::IsDirty() const
	{
		for (auto& uniform : m_Uniforms)
			if (uniform.m_Uniform->m_Dirty)
				return true;
		return false;
	}

	void UniformBuffer::ClearDirty()
	{
		for (auto& uniform : m_Uniforms)
			uniform.m_Uniform->m_Dirty = false;
	}

	Uniform* UniformBuffer::GetUniform(std::string_view name) const
	{
		for (auto& uniform : m_Uniforms)
			if (uniform.m_Name == name)
				return uniform.m_Uniform.get();
		return nullptr;
	}
} // namespace gp1::renderer