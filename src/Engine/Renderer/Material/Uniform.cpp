//
//	Created by MarcasRealAccount on 14. May. 2021
//

#include "Engine/Renderer/Material/Uniform.h"
#include "Engine/Application.h"

#include <cstring>

namespace gp1::renderer
{
	template <int C, int R, typename T, glm::qualifier Q>
	inline static bool FastMatNEQ(const glm::mat<C, R, T, Q>& a, const glm::mat<C, R, T, Q>& b)
	{
		return memcmp(&a, &b, sizeof(a));
	}

	std::shared_ptr<Uniform> Uniform::Create(EUniformType type)
	{
		return Application::GetInstance()->GetRenderer()->CreateUniform(type);
	}

	bool Uniform::IsOfSameType(const std::shared_ptr<Uniform>& other) const
	{
		return other && GetType() == other->GetType();
	}

	std::shared_ptr<UniformBuffer> UniformBuffer::Create()
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
					std::shared_ptr<Uniform> uniform = itr->m_Uniform;
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

	std::shared_ptr<Uniform> UniformBuffer::GetUniform(std::string_view name) const
	{
		for (auto& uniform : m_Uniforms)
			if (uniform.m_Name == name)
				return uniform.m_Uniform;
		return nullptr;
	}

	void UniformFloat::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformFloat> otherV = std::static_pointer_cast<UniformFloat>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFloat::SetValue(float value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformFVec2::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformFVec2> otherV = std::static_pointer_cast<UniformFVec2>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFVec2::SetValue(const glm::fvec2& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformFVec3::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformFVec3> otherV = std::static_pointer_cast<UniformFVec3>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFVec3::SetValue(const glm::fvec3& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformFVec4::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformFVec4> otherV = std::static_pointer_cast<UniformFVec4>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFVec4::SetValue(const glm::fvec4& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformInt::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformInt> otherV = std::static_pointer_cast<UniformInt>(other);
		SetValue(otherV->GetValue());
	}

	void UniformInt::SetValue(int32_t value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformIVec2::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformIVec2> otherV = std::static_pointer_cast<UniformIVec2>(other);
		SetValue(otherV->GetValue());
	}

	void UniformIVec2::SetValue(const glm::ivec2& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformIVec3::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformIVec3> otherV = std::static_pointer_cast<UniformIVec3>(other);
		SetValue(otherV->GetValue());
	}

	void UniformIVec3::SetValue(const glm::ivec3& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformIVec4::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformIVec4> otherV = std::static_pointer_cast<UniformIVec4>(other);
		SetValue(otherV->GetValue());
	}

	void UniformIVec4::SetValue(const glm::ivec4& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformUInt::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformUInt> otherV = std::static_pointer_cast<UniformUInt>(other);
		SetValue(otherV->GetValue());
	}

	void UniformUInt::SetValue(uint32_t value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformUVec2::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformUVec2> otherV = std::static_pointer_cast<UniformUVec2>(other);
		SetValue(otherV->GetValue());
	}

	void UniformUVec2::SetValue(const glm::uvec2& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformUVec3::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformUVec3> otherV = std::static_pointer_cast<UniformUVec3>(other);
		SetValue(otherV->GetValue());
	}

	void UniformUVec3::SetValue(const glm::uvec3& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformUVec4::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformUVec4> otherV = std::static_pointer_cast<UniformUVec4>(other);
		SetValue(otherV->GetValue());
	}

	void UniformUVec4::SetValue(const glm::uvec4& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformFMat2::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformFMat2> otherV = std::static_pointer_cast<UniformFMat2>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFMat2::SetValue(const glm::fmat2& value)
	{
		m_Dirty = FastMatNEQ(m_Value, value);
		m_Value = value;
	}

	void UniformFMat3::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformFMat3> otherV = std::static_pointer_cast<UniformFMat3>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFMat3::SetValue(const glm::fmat3& value)
	{
		m_Dirty = FastMatNEQ(m_Value, value);
		m_Value = value;
	}

	void UniformFMat4::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformFMat4> otherV = std::static_pointer_cast<UniformFMat4>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFMat4::SetValue(const glm::fmat4& value)
	{
		m_Dirty = FastMatNEQ(m_Value, value);
		m_Value = value;
	}

	void UniformTexture2D::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformTexture2D> otherV = std::static_pointer_cast<UniformTexture2D>(other);
		SetValue(otherV->GetValue());
	}

	void UniformTexture2D::SetValue(std::shared_ptr<Texture2D> value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformTexture2DArray::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformTexture2DArray> otherV = std::static_pointer_cast<UniformTexture2DArray>(other);
		SetValue(otherV->GetValue());
	}

	void UniformTexture2DArray::SetValue(std::shared_ptr<Texture2DArray> value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformTexture3D::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformTexture3D> otherV = std::static_pointer_cast<UniformTexture3D>(other);
		SetValue(otherV->GetValue());
	}

	void UniformTexture3D::SetValue(std::shared_ptr<Texture3D> value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformTextureCubeMap::CopyFrom(const std::shared_ptr<Uniform>& other)
	{
		if (!IsOfSameType(other))
			return;

		std::shared_ptr<UniformTextureCubeMap> otherV = std::static_pointer_cast<UniformTextureCubeMap>(other);
		SetValue(otherV->GetValue());
	}

	void UniformTextureCubeMap::SetValue(std::shared_ptr<TextureCubeMap> value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}
} // namespace gp1::renderer