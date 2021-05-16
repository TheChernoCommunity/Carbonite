//
//	Created by MarcasRealAccount on 14. May. 2021
//

#include "Engine/Renderer/Material/Uniform.h"

namespace gp1::renderer
{
	std::shared_ptr<Uniform> Uniform::CreateUniform(EUniformType type)
	{
		switch (type)
		{
		case EUniformType::Float: return std::make_shared<UniformFloat>();
		case EUniformType::FVec2: return std::make_shared<UniformFVec2>();
		case EUniformType::FVec3: return std::make_shared<UniformFVec3>();
		case EUniformType::FVec4: return std::make_shared<UniformFVec4>();
		case EUniformType::Int: return std::make_shared<UniformInt>();
		case EUniformType::IVec2: return std::make_shared<UniformIVec2>();
		case EUniformType::IVec3: return std::make_shared<UniformIVec3>();
		case EUniformType::IVec4: return std::make_shared<UniformIVec4>();
		case EUniformType::UInt: return std::make_shared<UniformUInt>();
		case EUniformType::UVec2: return std::make_shared<UniformUVec2>();
		case EUniformType::UVec3: return std::make_shared<UniformUVec3>();
		case EUniformType::UVec4: return std::make_shared<UniformUVec4>();
		case EUniformType::FMat2: return std::make_shared<UniformFMat2>();
		case EUniformType::FMat3: return std::make_shared<UniformFMat3>();
		case EUniformType::FMat4: return std::make_shared<UniformFMat4>();
		default: return nullptr;
		}
	}

	bool Uniform::IsOfSameType(const std::shared_ptr<Uniform>& other) const
	{
		return other && GetType() == other->GetType();
	}

	UniformBuffer::UniformInfo::UniformInfo(EUniformType type)
	    : m_Uniform(Uniform::CreateUniform(type)) {}

	UniformBuffer::UniformBuffer(const std::string& name, const std::vector<std::pair<std::string, UniformInfo>>& uniforms)
	    : m_Name(name)
	{
		for (auto& uniform : uniforms)
			m_Uniforms.insert(uniform);
	}

	bool UniformBuffer::IsDirty() const
	{
		for (auto& uniform : m_Uniforms)
			if (uniform.second.m_Uniform->IsDirty())
				return true;
		return false;
	}

	void UniformBuffer::ClearDirty()
	{
		for (auto& uniform : m_Uniforms)
			uniform.second.m_Uniform->ClearDirty();
	}

	std::shared_ptr<Uniform> UniformBuffer::GetUniform(const std::string& name) const
	{
		auto itr = m_Uniforms.find(name);
		if (itr != m_Uniforms.end())
			return itr->second.m_Uniform;
		return nullptr;
	}

	void UniformBuffer::GetUniformData(std::vector<uint8_t>& data) const
	{
		size_t size = 0;
		for (auto& uniform : m_Uniforms)
		{
			const UniformInfo& info = uniform.second;
			size_t             end  = info.m_Offset + info.m_Uniform->GetDataSize();
			if (end > size)
				size = end;
		}
		data.resize(size);
		for (auto& uniform : m_Uniforms)
			uniform.second.m_Uniform->PutData(data, uniform.second.m_Offset);
	}

	size_t UniformFloat::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformFloat::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformFVec2::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformFVec2::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformFVec3::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformFVec3::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformFVec4::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformFVec4::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformInt::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformInt::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformIVec2::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformIVec2::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformIVec3::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformIVec3::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformIVec4::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformIVec4::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformUInt::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformUInt::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformUVec2::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformUVec2::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformUVec3::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformUVec3::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformUVec4::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformUVec4::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformFMat2::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformFMat2::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformFMat3::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformFMat3::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}

	size_t UniformFMat4::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void UniformFMat4::PutData(std::vector<uint8_t>& data, size_t offset) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[offset + i] = pValue[i];
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
		m_Value = value;
		m_Dirty = true;
	}
} // namespace gp1::renderer