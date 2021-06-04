//
//	Created by MarcasRealAccount on 14. May. 2021
//

#include "Engine/Renderer/Material/Uniform.h"
#include "Engine/Application.h"

#include <cstring>

namespace gp1::renderer
{
	template <int C, int R, typename T, glm::qualifier Q>
	static bool FastMatNEQ(const glm::mat<C, R, T, Q>& a, const glm::mat<C, R, T, Q>& b)
	{
		return memcmp(&a, &b, sizeof(a));
	}

	std::unique_ptr<Uniform> Uniform::Create(EUniformType type)
	{
		return Application::GetInstance()->GetRenderer()->CreateUniform(type);
	}

	bool Uniform::IsOfSameType(const Uniform* other) const
	{
		return other && GetType() == other->GetType();
	}

	void UniformFloat::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformFloat* otherV = static_cast<const UniformFloat*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFloat::SetValue(float value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformFVec2::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformFVec2* otherV = static_cast<const UniformFVec2*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFVec2::SetValue(const glm::fvec2& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformFVec3::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformFVec3* otherV = static_cast<const UniformFVec3*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFVec3::SetValue(const glm::fvec3& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformFVec4::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformFVec4* otherV = static_cast<const UniformFVec4*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFVec4::SetValue(const glm::fvec4& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformInt::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformInt* otherV = static_cast<const UniformInt*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformInt::SetValue(int32_t value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformIVec2::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformIVec2* otherV = static_cast<const UniformIVec2*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformIVec2::SetValue(const glm::ivec2& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformIVec3::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformIVec3* otherV = static_cast<const UniformIVec3*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformIVec3::SetValue(const glm::ivec3& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformIVec4::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformIVec4* otherV = static_cast<const UniformIVec4*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformIVec4::SetValue(const glm::ivec4& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformUInt::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformUInt* otherV = static_cast<const UniformUInt*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformUInt::SetValue(uint32_t value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformUVec2::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformUVec2* otherV = static_cast<const UniformUVec2*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformUVec2::SetValue(const glm::uvec2& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformUVec3::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformUVec3* otherV = static_cast<const UniformUVec3*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformUVec3::SetValue(const glm::uvec3& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformUVec4::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformUVec4* otherV = static_cast<const UniformUVec4*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformUVec4::SetValue(const glm::uvec4& value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformFMat2::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformFMat2* otherV = static_cast<const UniformFMat2*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFMat2::SetValue(const glm::fmat2& value)
	{
		m_Dirty = FastMatNEQ(m_Value, value);
		m_Value = value;
	}

	void UniformFMat3::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformFMat3* otherV = static_cast<const UniformFMat3*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFMat3::SetValue(const glm::fmat3& value)
	{
		m_Dirty = FastMatNEQ(m_Value, value);
		m_Value = value;
	}

	void UniformFMat4::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformFMat4* otherV = static_cast<const UniformFMat4*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformFMat4::SetValue(const glm::fmat4& value)
	{
		m_Dirty = FastMatNEQ(m_Value, value);
		m_Value = value;
	}

	void UniformTexture2D::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformTexture2D* otherV = static_cast<const UniformTexture2D*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformTexture2D::SetValue(Texture2D* value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformTexture2DArray::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformTexture2DArray* otherV = static_cast<const UniformTexture2DArray*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformTexture2DArray::SetValue(Texture2DArray* value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformTexture3D::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformTexture3D* otherV = static_cast<const UniformTexture3D*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformTexture3D::SetValue(Texture3D* value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}

	void UniformTextureCubeMap::CopyFrom(const Uniform* other)
	{
		if (!IsOfSameType(other))
			return;

		const UniformTextureCubeMap* otherV = static_cast<const UniformTextureCubeMap*>(other);
		SetValue(otherV->GetValue());
	}

	void UniformTextureCubeMap::SetValue(TextureCubeMap* value)
	{
		m_Dirty = m_Value != value;
		m_Value = value;
	}
} // namespace gp1::renderer