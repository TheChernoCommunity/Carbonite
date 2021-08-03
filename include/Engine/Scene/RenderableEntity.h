//
//	Created by MarcasRealAccount on 16. May. 2021
//

#pragma once

#include "Engine/Renderer/Material/Material.h"
#include "Engine/Renderer/Mesh/Mesh.h"
#include "Engine/Scene/Entity.h"

#include <memory>

namespace gp1::scene
{
	class RenderableEntity : public Entity
	{
	public:
		virtual bool IsRenderable() const override
		{
			return true;
		}

		virtual renderer::Mesh*     GetMesh() const     = 0;
		virtual renderer::Material* GetMaterial() const = 0;
	};
} // namespace gp1::scene