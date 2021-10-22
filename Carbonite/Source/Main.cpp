#include <cstdlib>

int main(int argc, char** argv)
{
}

#if _WIN32
#undef APIENTRY
#include <Windows.h>

int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	return main(__argc, __argv);
}
#endif