#include "Carbonite.h"
#include "CSharp/Runtime.h"
#include "Renderer/RTRenderer.h"
#include "Renderer/RasterRenderer.h"
#include "Renderer/Renderer.h"
#include "Scene/ECS.h"
#include "Utils/FileIO.h"
#include "Utils/Log.h"

Carbonite& Carbonite::Get()
{
	static Carbonite* s_Instance = new Carbonite();
	return *s_Instance;
}

void Carbonite::Destroy()
{
	delete &Get();
}

void Carbonite::init()
{
	Log::trace("Carbonite init");

	[[maybe_unused]] auto& ecs = ECS::Get();

	// TODO(MarcasRealAccount): Add a way to enable raytracing.
	m_Renderer = new RasterRenderer();
	m_Renderer->init();
}

void Carbonite::run()
{
	Log::trace("Carbonite run");

	while (!glfwWindowShouldClose(m_Window.getHandle()))
	{
		glfwPollEvents();

		m_Renderer->render();
	}
}

void Carbonite::deinit()
{
	m_Renderer->deinit();
	delete m_Renderer;
	m_Renderer = nullptr;

	ECS::Destroy();

	Log::trace("Carbonite deinit");
}

Carbonite::Carbonite()
    : m_Window("Carbonite")
{
}

Carbonite::~Carbonite()
{
}

void Carbonite::loadModAPI()
{
	auto& runtime = CSharp::Runtime::Get();
	m_ModAPI      = runtime.loadAssembly(FileIO::getExecutableDir() / "ModAPI.dll");
}

void Carbonite::loadAvailableMods()
{
	for (auto& itr : std::filesystem::directory_iterator(FileIO::getGameDir() / "Mods/"))
	{
		if (!itr.is_directory())
			continue;

		auto& path     = itr.path();
		auto  infoFile = path / "Info.ini";
		if (!std::filesystem::exists(infoFile))
			continue;

		// TODO(MarcasRealAccount): Implement
	}
}