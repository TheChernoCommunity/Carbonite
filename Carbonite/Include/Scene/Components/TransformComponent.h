#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <entt/entt.hpp>

struct TransformComponent
{
public:
	TransformComponent()                              = default;
	TransformComponent(const TransformComponent&)     = default;
	TransformComponent(TransformComponent&&) noexcept = default;
	TransformComponent(const glm::fvec3& translation, const glm::fquat& rotation, const glm::fvec3& scale);
	TransformComponent(const glm::fvec3& translation);

	TransformComponent& operator=(const TransformComponent&) = default;
	TransformComponent& operator=(TransformComponent&&) noexcept = default;

	/* INFO(MarcasRealAccount): These getters and setters will be converted into C# like properties in the future ;) */

	auto  getParent() const { return m_Parent; }
	auto& getTranslation() const { return m_Translation; }
	auto& getRotation() const { return m_Rotation; }
	auto& getScale() const { return m_Scale; }
	bool  getHasChanged() const { return m_HasChanged; }

	const auto& getMatrix()
	{
		if (m_RecalculateMatrix)
		{
			recalculateMatrix();
			m_RecalculateMatrix = false;
		}
		return m_CachedMatrix;
	}

	void setParent(TransformComponent* parent)
	{
		if (m_Parent != parent)
		{
		}
		m_Parent = parent;
	}

	void setTranslation(glm::fvec3 value)
	{
		if (m_Translation != value)
		{
			m_RecalculateMatrix = true;
			m_HasChanged        = true;
			signalCamera();
		}
		m_Translation = value;
	}

	void setRotation(glm::fquat value)
	{
		if (m_Rotation != value)
		{
			m_RecalculateMatrix = true;
			m_HasChanged        = true;
			signalCamera();
		}
		m_Rotation = value;
	}

	void setScale(glm::fvec3 value)
	{
		if (m_Scale != value)
		{
			m_RecalculateMatrix = true;
			m_HasChanged        = true;
			signalCamera();
		}
		m_Scale = value;
	}

private:
	void recalculateMatrix();
	void signalCamera();

private:
	TransformComponent* m_Parent = nullptr;

	glm::fvec3 m_Translation       = { 0.0f, 0.0f, 0.0f };
	glm::fquat m_Rotation          = { 0.0f, 0.0f, 0.0f, 1.0f };
	glm::fvec3 m_Scale             = { 1.0f, 1.0f, 1.0f };
	bool       m_RecalculateMatrix = false;
	bool       m_HasChanged        = false;
	glm::fmat4 m_CachedMatrix      = { 1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 1.0f };
};

/*template <>
struct entt::component_traits<TransformComponent> : basic_component_traits
{
	using in_place_delete = std::true_type;
};*/