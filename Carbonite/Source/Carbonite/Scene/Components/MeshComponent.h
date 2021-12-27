#pragma once

#include "Carbonite/Renderer/Mesh/Mesh.h"

struct MeshComponent
{
public:
	MeshComponent()                         = default;
	MeshComponent(const MeshComponent&)     = default;
	MeshComponent(MeshComponent&&) noexcept = default;
	MeshComponent(Mesh* mesh);

	MeshComponent& operator=(const MeshComponent&) = default;
	MeshComponent& operator=(MeshComponent&&) noexcept = default;

public:
	Mesh* m_Mesh = nullptr;
};