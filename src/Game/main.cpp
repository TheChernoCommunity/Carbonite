#include "Engine/Utility/Log.h"

int main(int /*argc*/, char* /*argv*/[]) {
	gp1::Game game;
	game.Start();
	game.Stop();
	return 0;
}

#if defined( _WIN32 )

#include <Windows.h>

int WINAPI WinMain(_In_ HINSTANCE /*instance*/, _In_opt_ HINSTANCE /*prev_instance*/, _In_ LPSTR /*cmd_line*/, _In_ int /*cmd_show*/) {
	return main(__argc, __argv);
}

#endif // _WIN32
