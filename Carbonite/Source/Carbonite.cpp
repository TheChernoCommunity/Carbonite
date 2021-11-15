#include "PCH.h"

#include "Carbonite.h"
#include "Log.h"

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
}

void Carbonite::run()
{
	Log::trace("Carbonite run");
}

void Carbonite::deinit()
{
	Log::trace("Carbonite deinit");
}

Carbonite::Carbonite()
{
	init();
	m_Renderer.init();
}

Carbonite::~Carbonite()
{
	m_Renderer.deinit();
	deinit();
}