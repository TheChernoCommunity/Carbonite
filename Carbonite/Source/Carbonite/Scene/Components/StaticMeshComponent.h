#pragma once

#include "Carbonite/Renderer/Mesh/Mesh.h"

struct StaticMeshComponent
{
public:
	StaticMeshComponent()                               = default;
	StaticMeshComponent(const StaticMeshComponent&)     = default;
	StaticMeshComponent(StaticMeshComponent&&) noexcept = default;
	StaticMeshComponent(Mesh* mesh);

	StaticMeshComponent& operator=(const StaticMeshComponent&) = default;
	StaticMeshComponent& operator=(StaticMeshComponent&&) noexcept = default;

public:
	Mesh* m_Mesh = nullptr;
};