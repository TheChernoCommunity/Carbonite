#pragma once


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <GLFW/glfw3.h>
#include "Engine/Input/InputHandler.h"

namespace gp1 {
	class FreeCam {
	public:
		FreeCam();
		glm::mat4 GetView() { return m_ViewMatrix; };
		void LookUp(input::AxisCallbackData data);
		void LookRight(input::AxisCallbackData data);
		void MoveForward(input::ButtonCallbackData data);
		void MoveBackward(input::ButtonCallbackData data);
		void MoveLeft(input::ButtonCallbackData data);
		void MoveRight(input::ButtonCallbackData data);
	private:
		void UpdateDir();
		void UpdateView();

		double m_lastX = 400, m_lastY = 300;
		float m_Pitch = 0, m_Yaw = 0;
		glm::vec3 m_UpDir = glm::vec3(0,1,0); //direction of up for the camera
		glm::vec3 m_FrontDir = glm::vec3(0,0,1); //direction the camera is pointing
		glm::vec3 m_CameraPos = glm::vec3(0,0,-3); //position of the camera in the world
		float m_CameraSpeed = 1; //speed of the camera
		float m_Sensitivity = 0.1f; //sensitivity of the look
		glm::mat4 m_ViewMatrix; //the view matrix of the camera 
	};
}

