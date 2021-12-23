#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

struct CameraComponent
{
public:
	friend struct TransformComponent;

public:
	CameraComponent()                           = default;
	CameraComponent(const CameraComponent&)     = default;
	CameraComponent(CameraComponent&&) noexcept = default;
	CameraComponent(float fov, float near, float far);
	CameraComponent(float fov, float near);

	CameraComponent& operator=(const CameraComponent&) = default;
	CameraComponent& operator=(CameraComponent&&) noexcept = default;

	/* INFO(MarcasRealAccount): These getters and setters will be converted into C# like properties in the future ;) */
	float getFov() const { return m_Fov; }
	float getNear() const { return m_Near; }
	float getFar() const { return m_Far; }
	float getAspect() const { return m_Aspect; }
	bool  getHasChanged() const { return m_HasChanged; }

	const auto& getViewMatrix()
	{
		if (m_RecalculateViewMatrix)
		{
			recalculateViewMatrix();
			m_RecalculateViewMatrix = false;
		}
		return m_CachedViewMatrix;
	}

	const auto& getProjectionMatrix()
	{
		if (m_RecalculateProjectionMatrix)
		{
			recalculateProjectionMatrix();
			m_RecalculateProjectionMatrix = false;
		}
		return m_CachedProjectionMatrix;
	}

	const auto& getProjectionViewMatrix()
	{
		if (m_RecalculateProjectionViewMatrix)
		{
			recalculateProjectionViewMatrix();
			m_RecalculateProjectionViewMatrix = false;
		}
		return m_CachedProjectionViewMatrix;
	}

	void setFov(float value)
	{
		if (m_Fov != value)
		{
			m_RecalculateProjectionMatrix     = true;
			m_RecalculateProjectionViewMatrix = true;
			m_HasChanged                      = true;
		}
		m_Fov = value;
	}

	void setNear(float value)
	{
		if (m_Near != value)
		{
			m_RecalculateProjectionMatrix     = true;
			m_RecalculateProjectionViewMatrix = true;
			m_HasChanged                      = true;
		}
		m_Near = value;
	}

	void setFar(float value)
	{
		if (m_Far != value)
		{
			m_RecalculateProjectionMatrix     = true;
			m_RecalculateProjectionViewMatrix = true;
			m_HasChanged                      = true;
		}
		m_Far = value;
	}

	void setAspect(float value)
	{
		if (m_Aspect != value)
		{
			m_RecalculateProjectionMatrix     = true;
			m_RecalculateProjectionViewMatrix = true;
			m_HasChanged                      = true;
		}
		m_Aspect = value;
	}

private:
	void recalculateViewMatrix();
	void recalculateProjectionMatrix();
	void recalculateProjectionViewMatrix();

private:
	float      m_Fov                             = 90.0f;
	float      m_Near                            = 0.01f;
	float      m_Far                             = -1.0f; // m_Far < 0.0f => Infinite projection matrix
	float      m_Aspect                          = 1.0f;
	bool       m_RecalculateViewMatrix           = true;
	bool       m_RecalculateProjectionMatrix     = true;
	bool       m_RecalculateProjectionViewMatrix = true;
	bool       m_HasChanged                      = false;
	glm::fmat4 m_CachedViewMatrix                = glm::fmat4 { 1.0f };
	glm::fmat4 m_CachedProjectionMatrix          = glm::fmat4 { 1.0f };
	glm::fmat4 m_CachedProjectionViewMatrix      = glm::fmat4 { 1.0f };
};
