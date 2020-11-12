//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Scene/Camera.h"
#include "Engine/Scene/Scene.h"

#include <gtx/transform.hpp>

namespace gp1 {

	Camera::Camera(float fov, float near, float far)
		: m_Fov(fov), m_Near(near), m_Far(far) {}

	void Camera::SetAsMainCamera() {
		if (this->m_Scene)
			this->m_Scene->SetMainCamera(this);
	}

	const glm::fmat4& Camera::GetProjectionMatrix() {
		if (this->m_Fov != this->m_PFov || this->m_Aspect != this->m_PAspect || this->m_Near != this->m_PNear || this->m_Far != this->m_PFar) {
			this->m_PFov = this->m_Fov;
			this->m_PAspect = this->m_Aspect;
			this->m_PNear = this->m_Near;
			this->m_PFar = this->m_Far;
			this->m_CachedProjectionMatrix = glm::perspective(this->m_Fov, this->m_Aspect, this->m_Near, this->m_Far);
		}
		return this->m_CachedProjectionMatrix;
	}

	const glm::fmat4& Camera::GetProjectionViewMatrix() {
		if (this->m_Fov != this->m_PFov || this->m_Aspect != this->m_PAspect || this->m_Position != this->m_PPosition || this->m_Rotation != this->m_PRotation || this->m_Scale != this->m_PScale) {
			this->m_CachedProjectionViewMatrix = GetProjectionMatrix() * GetTransformationMatrix();
		}
		return this->m_CachedProjectionViewMatrix;
	}

} // namespace gp1
