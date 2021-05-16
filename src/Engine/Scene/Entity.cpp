//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include <gtx/transform.hpp>

namespace gp1::scene
{
	Entity::~Entity()
	{
		if (m_Scene)
		{
			m_Scene->DetachEntity(this);
		}
	}

	void Entity::Update([[maybe_unused]] float deltaTime)
	{
	}

	const glm::fmat4& Entity::GetTransformationMatrix(bool negativeTranslation)
	{
		if (m_Position != m_PPosition || m_Rotation != m_PRotation || m_Scale != m_PScale)
		{
			m_PPosition = m_Position;
			m_PRotation = m_Rotation;
			m_PScale    = m_Scale;
			if (negativeTranslation)
			{
				m_CachedTransformationMatrix = glm::rotate(glm::radians(m_Rotation.x), glm::fvec3 { 1.0f, 0.0f, 0.0f });
				m_CachedTransformationMatrix = glm::rotate(m_CachedTransformationMatrix, glm::radians(m_Rotation.y), { 0.0f, 1.0f, 0.0f });
				m_CachedTransformationMatrix = glm::rotate(m_CachedTransformationMatrix, glm::radians(m_Rotation.z), { 0.0f, 0.0f, 1.0f });
				m_CachedTransformationMatrix = glm::scale(m_CachedTransformationMatrix, m_Scale);
				m_CachedTransformationMatrix = glm::translate(m_CachedTransformationMatrix, -m_Position);
			}
			else
			{
				m_CachedTransformationMatrix = glm::translate(m_Position);
				m_CachedTransformationMatrix = glm::rotate(m_CachedTransformationMatrix, glm::radians(m_Rotation.x), { 1.0f, 0.0f, 0.0f });
				m_CachedTransformationMatrix = glm::rotate(m_CachedTransformationMatrix, glm::radians(m_Rotation.y), { 0.0f, 1.0f, 0.0f });
				m_CachedTransformationMatrix = glm::rotate(m_CachedTransformationMatrix, glm::radians(m_Rotation.z), { 0.0f, 0.0f, 1.0f });
				m_CachedTransformationMatrix = glm::scale(m_CachedTransformationMatrix, m_Scale);
			}
		}
		return m_CachedTransformationMatrix;
	}
} // namespace gp1::scene
