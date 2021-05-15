//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//
//	Freecam by matty2048 on 4. Nov. 2020.
//		With some changes by MarcasRealAcocunt on 6. Dec. 2020.
//

#pragma once

#include "Engine/Scene/Entity.h"

#include "Engine/Input/AxisInputBinding.h"
#include "Engine/Input/ButtonInputBinding.h"

namespace gp1
{
	namespace renderer
	{
		class Renderer;
	}

	namespace scene
	{
		enum class CameraMode
		{
			NORMAL,
			FREECAM
		};

		class Camera : public Entity
		{
		public:
			Camera(float fov = 70.0f, float near = 0.01f, float far = 100000.0f);

			virtual void Update(float deltaTime) override;

			// Set this camera as the main camera.
			void SetAsMainCamera();

			// Get the projection matrix of this camera.
			const glm::fmat4& GetProjectionMatrix();
			// Get the projection view matrix of this camera.
			const glm::fmat4& GetProjectionViewMatrix();

			// Set the mode of this camera.
			void SetCameraMode(CameraMode mode);
			// Get the mode of this camera.
			CameraMode GetCameraMode() const;

			friend renderer::Renderer;

		private:
			// Move's the camera around.
			void Move(input::ButtonCallbackData data);
			// Turn's the camera around.
			void Turn(input::AxisCallbackData data);
			// Change the speed of the freecam.
			void SpeedChange(input::AxisCallbackData data);

		public:
			float m_Fov;           // The field of view of this camera.
			float m_Aspect = 0.0f; // The aspect ratio of this camera.
			float m_Near;          // The near plane of this camera.
			float m_Far;           // The far plane of this camera.

			glm::fvec4 m_ClearColor { 0.1f, 0.1f, 0.1f, 1.0f }; // The clear color of this camera.

		protected:
			float m_PFov    = 0.0f; // The previous field of view of this camera.
			float m_PAspect = 0.0f; // The previous aspect ratio of this camera.
			float m_PNear   = 0.0f; // The previous near plane of this camera.
			float m_PFar    = 0.0f; // The previous far plane of this camera.

			glm::fmat4 m_CachedProjectionMatrix     = glm::fmat4(1.0f); // The cached projection matrix.
			glm::fmat4 m_CachedProjectionViewMatrix = glm::fmat4(1.0f); // The cached projection view matrix.

			CameraMode m_Mode = CameraMode::FREECAM; // TODO: Change this to NORMAL in the future once a player character has been created.

		protected:                                // Freecam data:
			float      m_FreecamSpeed = 4.0f;     // The speed of the freecam.
			glm::ivec4 m_LocalFreecamVelocity {}; // The local freecam velocity.
		};

	} // namespace scene

} // namespace gp1
