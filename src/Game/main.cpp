#include "Engine/Utility/Log.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main( int /*argc*/, char* /*argv*/[] )
{
	if (!glfwInit())
	{
		gp1::log(gp1::Severity::Error, "Failed to initialise GLFW.");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(960, 540, "GameProject-1", nullptr, nullptr);

	if (!window)
	{
		gp1::log(gp1::Severity::Error, "Failed to create window.");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL())
	{
		gp1::log(gp1::Severity::Error, "Failed to load OpenGL functions.");
		glfwTerminate();
		return 1;
	}

	float red = 0.0f;
	float redInc = 0.001f;
	float green = 1.0f;
	float greenInc = -0.001f;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(red, green, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		red += redInc;
		green += greenInc;

		if (red <= 0.0f)
		{
			redInc *= -1;
			red = 0.0f;
		}

		if (red >= 1.0f)
		{
			redInc *= -1;
			red = 1.0f;
		}

		if (green <= 0.0f)
		{
			greenInc *= -1;
			green = 0.0f;
		}

		if (green >= 1.0f)
		{
			greenInc *= -1;
			green = 1.0f;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

#if defined( _WIN32 )

#include <Windows.h>

int WINAPI WinMain( _In_ HINSTANCE /*instance*/, _In_opt_ HINSTANCE /*prev_instance*/, _In_ LPSTR /*cmd_line*/, _In_ int /*cmd_show*/ )
{
	return main( __argc, __argv );
}

#endif // _WIN32
