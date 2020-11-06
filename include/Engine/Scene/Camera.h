//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#pragma once

#include "Engine/Scene/Entity.h"

namespace gp1 {

	class Renderer;

	class Camera : public Entity {
	public:
		Camera(float fov = 70.0f, float near = 0.01f, float far = 100000.0f);

		void SetAsMainCamera();

		const glm::fmat4& GetProjectionMatrix();
		const glm::fmat4& GetProjectionViewMatrix();

		friend Renderer;

	public:
		float m_Fov;
		float m_Aspect = 0.0f;
		float m_Near;
		float m_Far;

		glm::fvec4 m_ClearColor{ 0.1f, 0.1f, 0.1f, 1.0f };

	protected:
		float m_PFov = 0.0f;
		float m_PAspect = 0.0f;
		float m_PNear = 0.0f;
		float m_PFar = 0.0f;

		glm::fmat4 m_CachedProjectionMatrix = glm::fmat4(1.0f);
		glm::fmat4 m_CachedProjectionViewMatrix = glm::fmat4(1.0f);
	};

} // namespace gp1
