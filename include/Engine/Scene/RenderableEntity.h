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
		inline virtual bool IsRenderable() const override
		{
			return true;
		}

		inline virtual std::shared_ptr<renderer::Mesh>     GetMesh() const     = 0;
		inline virtual std::shared_ptr<renderer::Material> GetMaterial() const = 0;
	};
} // namespace gp1::scene