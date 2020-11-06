//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include <gtx/transform.hpp>

namespace gp1 {

	Entity::~Entity() {
		if (this->m_Scene) {
			this->m_Scene->DetachEntity(this);
		}
	}

	const glm::fmat4& Entity::GetTransformationMatrix() {
		if (this->m_Position != this->m_PPosition || this->m_Rotation != this->m_PRotation || this->m_Scale != this->m_PScale) {
			this->m_PPosition = this->m_Position;
			this->m_PRotation = this->m_Rotation;
			this->m_PScale = this->m_Scale;
			this->m_CachedTransformationMatrix = glm::translate(this->m_Position);
			this->m_CachedTransformationMatrix = glm::rotate(this->m_CachedTransformationMatrix, this->m_Rotation.x, { 1.0f, 0.0f, 0.0f });
			this->m_CachedTransformationMatrix = glm::rotate(this->m_CachedTransformationMatrix, this->m_Rotation.y, { 0.0f, 1.0f, 0.0f });
			this->m_CachedTransformationMatrix = glm::rotate(this->m_CachedTransformationMatrix, this->m_Rotation.z, { 0.0f, 0.0f, 1.0f });
			this->m_CachedTransformationMatrix = glm::scale(this->m_CachedTransformationMatrix, this->m_Scale);
		}
		return m_CachedTransformationMatrix;
	}

	Mesh* Entity::GetMesh() const {
		return nullptr;
	}

	Material* Entity::GetMaterial() const {
		return nullptr;
	}

	Scene* Entity::GetScene() const {
		return this->m_Scene;
	}

} // namespace gp1
