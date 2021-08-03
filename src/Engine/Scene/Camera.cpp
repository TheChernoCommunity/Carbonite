//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//
//	Freecam by matty2048 on 4. Nov. 2020.
//		With some changes by MarcasRealAcocunt on 6. Dec. 2020.
//

#include "Engine/Scene/Camera.h"
#include "Engine/Scene/Scene.h"

#include "Engine/Input/InputHandler.h"

#include <cmath>

#include <gtx/transform.hpp>

namespace gp1::scene
{
	float lerp(float a, float b, float t)
	{
		return b * t + a * (1 - t);
	}

	Camera::Camera(float fov, float near, float far)
	    : m_Fov(fov), m_Near(near), m_Far(far)
	{
		input::InputGroup* mainMenu = input::InputHandler::GetOrCreateInputGroup("mainMenu");
		mainMenu->CreateButtonInputBinding("mousePress", input::buttons::mouseLeft, input::ButtonInputType::PRESS, input::InputLocation::MOUSE)->BindCallback([&]([[maybe_unused]] input::ButtonCallbackData data) {
			input::InputHandler::SetCurrentActiveInputGroup("freecam");
		});

		input::InputGroup* freecamInputs = input::InputHandler::GetOrCreateInputGroup("freecam");
		freecamInputs->SetCaptureMouse(true);
		freecamInputs->CreateButtonInputBinding("openMainMenu", input::buttons::keyEscape)->BindCallback([&]([[maybe_unused]] input::ButtonCallbackData data) {
			input::InputHandler::SetCurrentActiveInputGroup("mainMenu");
		});

		freecamInputs->CreateButtonInputBinding("moveForward", input::buttons::keyW, input::ButtonInputType::PRESS_AND_RELEASE)->BindCallback(std::bind(&Camera::Move, this, std::placeholders::_1));
		freecamInputs->CreateButtonInputBinding("moveBackward", input::buttons::keyS, input::ButtonInputType::PRESS_AND_RELEASE)->BindCallback(std::bind(&Camera::Move, this, std::placeholders::_1));
		freecamInputs->CreateButtonInputBinding("moveLeft", input::buttons::keyA, input::ButtonInputType::PRESS_AND_RELEASE)->BindCallback(std::bind(&Camera::Move, this, std::placeholders::_1));
		freecamInputs->CreateButtonInputBinding("moveRight", input::buttons::keyD, input::ButtonInputType::PRESS_AND_RELEASE)->BindCallback(std::bind(&Camera::Move, this, std::placeholders::_1));
		freecamInputs->CreateButtonInputBinding("moveUp", input::buttons::keySpace, input::ButtonInputType::PRESS_AND_RELEASE)->BindCallback(std::bind(&Camera::Move, this, std::placeholders::_1));
		freecamInputs->CreateButtonInputBinding("moveDown", input::buttons::keyLeftShift, input::ButtonInputType::PRESS_AND_RELEASE)->BindCallback(std::bind(&Camera::Move, this, std::placeholders::_1));
		freecamInputs->CreateButtonInputBinding("sprint", input::buttons::keyLeftControl, input::ButtonInputType::PRESS_AND_RELEASE)->BindCallback(std::bind(&Camera::Move, this, std::placeholders::_1));
		freecamInputs->CreateAxisInputBinding("turnRight", input::axises::mouseX)->BindCallback(std::bind(&Camera::Turn, this, std::placeholders::_1));
		freecamInputs->CreateAxisInputBinding("turnUp", input::axises::mouseY)->BindCallback(std::bind(&Camera::Turn, this, std::placeholders::_1));
		freecamInputs->CreateAxisInputBinding("speedChange", input::axises::mouseWheelY)->BindCallback(std::bind(&Camera::SpeedChange, this, std::placeholders::_1));
	}

	void Camera::Update(float deltaTime)
	{
		switch (m_Mode)
		{
		case ECameraMode::Normal:
			break;
		case ECameraMode::Freecam:
			if (this->m_Aspect != 0.0f)
			{
				GetProjectionViewMatrix();
				glm::fmat4 view     = glm::scale(glm::inverse(GetTransformationMatrix(true)), glm::fvec3(m_LocalFreecamVelocity));
				glm::fvec3 velocity = glm::fvec3(view[0] + view[1] + view[2]) * m_FreecamSpeed;
				if (m_LocalFreecamVelocity.w) velocity *= 3.0f;
				m_Position += velocity * deltaTime;
			}
			break;
		}
	}

	const glm::fmat4& Camera::GetProjectionMatrix()
	{
		if (m_Fov != m_PFov || m_Aspect != m_PAspect || m_Near != m_PNear || m_Far != m_PFar)
		{
			m_PFov                   = m_Fov;
			m_PAspect                = m_Aspect;
			m_PNear                  = m_Near;
			m_PFar                   = m_Far;
			m_CachedProjectionMatrix = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
		}
		return m_CachedProjectionMatrix;
	}

	const glm::fmat4& Camera::GetProjectionViewMatrix()
	{
		if (m_Fov != m_PFov || m_Aspect != m_PAspect || m_Position != m_PPosition || m_Rotation != m_PRotation || m_Scale != m_PScale)
		{
			m_CachedProjectionViewMatrix = GetProjectionMatrix() * GetTransformationMatrix(true);
		}
		return m_CachedProjectionViewMatrix;
	}

	void Camera::Move(input::ButtonCallbackData data)
	{
		switch (m_Mode)
		{
		case ECameraMode::Normal:
			break;
		case ECameraMode::Freecam:
			if (data.m_Id == "moveForward")
			{
				if (data.m_InputType == input::ButtonInputType::PRESS)
					m_LocalFreecamVelocity.z--;
				else
					m_LocalFreecamVelocity.z++;
			}
			else if (data.m_Id == "moveBackward")
			{
				if (data.m_InputType == input::ButtonInputType::PRESS)
					m_LocalFreecamVelocity.z++;
				else
					m_LocalFreecamVelocity.z--;
			}
			else if (data.m_Id == "moveRight")
			{
				if (data.m_InputType == input::ButtonInputType::PRESS)
					m_LocalFreecamVelocity.x++;
				else
					m_LocalFreecamVelocity.x--;
			}
			else if (data.m_Id == "moveLeft")
			{
				if (data.m_InputType == input::ButtonInputType::PRESS)
					m_LocalFreecamVelocity.x--;
				else
					m_LocalFreecamVelocity.x++;
			}
			else if (data.m_Id == "moveUp")
			{
				if (data.m_InputType == input::ButtonInputType::PRESS)
					m_LocalFreecamVelocity.y++;
				else
					m_LocalFreecamVelocity.y--;
			}
			else if (data.m_Id == "moveDown")
			{
				if (data.m_InputType == input::ButtonInputType::PRESS)
					m_LocalFreecamVelocity.y--;
				else
					m_LocalFreecamVelocity.y++;
			}
			else if (data.m_Id == "sprint")
			{
				if (data.m_InputType == input::ButtonInputType::PRESS)
					m_LocalFreecamVelocity.w++;
				else
					m_LocalFreecamVelocity.w--;
			}
			break;
		}
	}

	void Camera::Turn(input::AxisCallbackData data)
	{
		if (data.m_Id == "turnRight")
		{
			m_Rotation.y += static_cast<float>(data.GetDeltaValue()) * 0.1f;
			m_Rotation.y = fmodf(m_Rotation.y, 360.0f);
		}
		else if (data.m_Id == "turnUp")
		{
			m_Rotation.x += static_cast<float>(data.GetDeltaValue()) * 0.1f;
			if (m_Rotation.x < -90.0f)
				m_Rotation.x = -90.0f;
			else if (m_Rotation.x > 90.0f)
				m_Rotation.x = 90.0f;
		}
	}

	void Camera::SpeedChange(input::AxisCallbackData data)
	{
		if (data.m_Value > 0)
		{
			this->m_FreecamSpeed *= 1.2f;
		}
		else if (data.m_Value < 0)
		{
			this->m_FreecamSpeed *= 0.83333333333333333333333333333333f;
		}
	}

} // namespace gp1::scene
