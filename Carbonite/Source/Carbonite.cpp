#include "PCH.h"

#include "Carbonite.h"
#include "Log.h"
#include "Renderer/RTRenderer.h"
#include "Renderer/RasterRenderer.h"
#include "Renderer/Renderer.h"

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

	Log::trace("Carbonite deinit");
}

Carbonite::Carbonite()
    : m_Window("Carbonite")
{
}

Carbonite::~Carbonite()
{
}
