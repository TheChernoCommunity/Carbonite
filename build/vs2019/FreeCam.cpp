#include "FreeCam.h"

void gp1::FreeCam::LookUp(input::AxisCallbackData data)
{
	double ydiff = lastY - data.m_Value;
	lastY = data.m_Value;

	Pitch += ydiff * Sensitivity;
	if (Pitch > 89.0f) Pitch = 89.0f;
	if (Pitch < -89.0f) Pitch = -89.0f;

	UpdateDir();
}

void gp1::FreeCam::LookRight(input::AxisCallbackData data)
{
	double xdiff = data.m_Value - lastX;
	lastX = data.m_Value;
	Yaw += xdiff;

	UpdateDir();
}

void gp1::FreeCam::UpdateDir()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	direction.y = sin(glm::radians(Pitch));
	direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	FrontDir = glm::normalize(direction);
}

void gp1::FreeCam::MoveForward(input::ButtonCallbackData /*data*/)
{
	
	CameraPos += FrontDir * CameraSpeed;
	UpdateView();
}
void gp1::FreeCam::MoveBackward(input::ButtonCallbackData /*data*/)
{
	CameraPos -= FrontDir * CameraSpeed;
	UpdateView();
}

void gp1::FreeCam::MoveLeft(input::ButtonCallbackData /*data*/)
{
	CameraPos -= glm::normalize(glm::cross(FrontDir,UpDir)) * CameraSpeed;
	UpdateView();
}

void gp1::FreeCam::MoveRight(input::ButtonCallbackData /*data*/)
{
	CameraPos += glm::normalize(glm::cross(FrontDir,UpDir)) * CameraSpeed;
	UpdateView();
}



void gp1::FreeCam::UpdateView()
{
	ViewMatrix = glm::lookAt(CameraPos, CameraPos + FrontDir, UpDir);
}





