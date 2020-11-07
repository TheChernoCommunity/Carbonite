#include "FreeCam.h"

gp1::FreeCam::FreeCam()
{
		input::InputGroup* freecamGroup = input::InputHandler::GetOrCreateInputGroup("freecam");
		freecamGroup->CreateAxisInputBinding("lookUp", input::axises::mouseY)->BindCallback(std::bind(&FreeCam::LookUp, this, std::placeholders::_1));
		freecamGroup->CreateAxisInputBinding("lookRight", input::axises::mouseX)->BindCallback(std::bind(&FreeCam::LookRight, this, std::placeholders::_1));
		freecamGroup->CreateButtonInputBinding("forward", input::buttons::keyW)->BindCallback(std::bind(&FreeCam::MoveForward, this, std::placeholders::_1));
		freecamGroup->CreateButtonInputBinding("backward", input::buttons::keyS)->BindCallback(std::bind(&FreeCam::MoveBackward, this, std::placeholders::_1));
		freecamGroup->CreateButtonInputBinding("left", input::buttons::keyA)->BindCallback(std::bind(&FreeCam::MoveLeft, this, std::placeholders::_1));
		freecamGroup->CreateButtonInputBinding("right", input::buttons::keyD)->BindCallback(std::bind(&FreeCam::MoveRight, this, std::placeholders::_1));
}

void gp1::FreeCam::LookUp(input::AxisCallbackData data)
{
	double ydiff = m_lastY - data.m_Value;
	m_lastY = data.m_Value;

	m_Pitch += ydiff * m_Sensitivity;
	if (m_Pitch > 89.0f) m_Pitch = 89.0f;
	if (m_Pitch < -89.0f) m_Pitch = -89.0f;

	UpdateDir();
}

void gp1::FreeCam::LookRight(input::AxisCallbackData data)
{
	double xdiff = data.m_Value - m_lastX;
	m_lastX = data.m_Value;
	m_Yaw += xdiff;

	UpdateDir();
}

void gp1::FreeCam::UpdateDir()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	direction.y = sin(glm::radians(m_Pitch));
	direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_FrontDir = glm::normalize(direction);
}

void gp1::FreeCam::MoveForward(input::ButtonCallbackData /*data*/)
{
	
	m_CameraPos += m_FrontDir * m_CameraSpeed;
	UpdateView();
}
void gp1::FreeCam::MoveBackward(input::ButtonCallbackData /*data*/)
{
	m_CameraPos -= m_FrontDir * m_CameraSpeed;
	UpdateView();
}

void gp1::FreeCam::MoveLeft(input::ButtonCallbackData /*data*/)
{
	m_CameraPos -= glm::normalize(glm::cross(m_FrontDir, m_UpDir)) * m_CameraSpeed;
	UpdateView();
}

void gp1::FreeCam::MoveRight(input::ButtonCallbackData /*data*/)
{
	m_CameraPos += glm::normalize(glm::cross(m_FrontDir, m_UpDir)) * m_CameraSpeed;
	UpdateView();
}



void gp1::FreeCam::UpdateView()
{
	m_ViewMatrix = glm::lookAt(m_CameraPos, m_CameraPos + m_FrontDir, m_UpDir);
}





