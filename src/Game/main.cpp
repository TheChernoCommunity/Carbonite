#include "Game.h"

#include <cstring>
#include <stdexcept>

int main(int /*argc*/, char* /*argv*/[])
{
	try
	{
		gp1::Application* game = gp1::Application::GetInstance();
		game->Run();
		delete game;
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		Logger("ExceptionHandler").LogError("Exception was thrown: %s", e.what());
		return EXIT_FAILURE;
	}
}

#if defined(_WIN32)

#ifdef APIENTRY
#undef APIENTRY
#endif
#include <Windows.h>

int WINAPI WinMain(_In_ HINSTANCE /*instance*/, _In_opt_ HINSTANCE /*prev_instance*/, _In_ LPSTR /*cmd_line*/, _In_ int /*cmd_show*/)
{
	return main(__argc, __argv);
}

#endif // _WIN32
