#include "PCH.h"

#include "ECS.h"

ECS& ECS::Get()
{
	static ECS* s_Instance = new ECS();
	return *s_Instance;
}

void ECS::Destroy()
{
	delete &Get();
}

ECS::ECS() {}

ECS::~ECS() {}