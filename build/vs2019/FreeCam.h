#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GLFW/glfw3.h>
#include "Engine/Input/InputHandler.h"

namespace gp1 {
	class FreeCam {
	public:
		FreeCam()
			:ViewMatrix(glm::mat4(1.0f))
		{
			input::InputGroup* freecamGroup = input::InputHandler::GetOrCreateInputGroup("freecam");

			freecamGroup->CreateAxisInputBinding("lookUp", 1)->BindCallback(std::bind(&FreeCam::LookUp, this, std::placeholders::_1));

			freecamGroup->CreateAxisInputBinding("lookRight", 0)->BindCallback(std::bind(&FreeCam::LookRight, this, std::placeholders::_1));

			freecamGroup->CreateButtonInputBinding("forward", GLFW_KEY_W)->BindCallback(std::bind(&FreeCam::MoveForward, this, std::placeholders::_1));

			freecamGroup->CreateButtonInputBinding("backward", GLFW_KEY_S)->BindCallback(std::bind(&FreeCam::MoveBackward, this, std::placeholders::_1));

			freecamGroup->CreateButtonInputBinding("left", GLFW_KEY_A)->BindCallback(std::bind(&FreeCam::MoveLeft, this, std::placeholders::_1));

			freecamGroup->CreateButtonInputBinding("right", GLFW_KEY_D)->BindCallback(std::bind(&FreeCam::MoveRight, this, std::placeholders::_1));
		}

		glm::mat4 GetView() { return ViewMatrix; };

		void LookUp(input::AxisCallbackData data);

		void LookRight(input::AxisCallbackData data);

		void MoveForward(input::ButtonCallbackData data);

		void MoveBackward(input::ButtonCallbackData data);

		void MoveLeft(input::ButtonCallbackData data);

		void MoveRight(input::ButtonCallbackData data);


	private:
		double lastX = 400, lastY = 300;
		float Pitch = 0, Yaw = 0;
		void UpdateDir();

		glm::vec3 UpDir = glm::vec3(0,1,0); //direction of up for the camera
		glm::vec3 FrontDir = glm::vec3(0,0,1); //direction the camera is pointing
		glm::vec3 CameraPos = glm::vec3(0,0,-3); //position of the camera in the world

		float CameraSpeed = 1; //speed of the camera
		float Sensitivity = 0.1f; //sensitivity of the look


		void UpdateView();
		glm::mat4 ViewMatrix; //the view matrix of the camera 
	};
}

