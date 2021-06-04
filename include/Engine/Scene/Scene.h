//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#pragma once

#include "Engine/Scene/Entity.h"
#include "Engine/Scene/RenderableEntity.h"

#include <memory>
#include <vector>

namespace gp1::scene
{
	class Scene
	{
	public:
		void AttachEntity(Entity* entity);
		void DetachEntity(Entity* entity);

		void Update(float deltaTime);

		const std::vector<Entity*>& GetEntities()
		{
			return m_Entities;
		}

		const std::vector<Entity*>& GetUpdatableEntities()
		{
			return m_UpdatableEntities;
		}

		const std::vector<RenderableEntity*>& GetRenderableEntities()
		{
			return m_RenderableEntities;
		}

	private:
		std::vector<Entity*>           m_Entities;           // The entities this scene holds.
		std::vector<Entity*>           m_UpdatableEntities;  // The entities that can update.
		std::vector<RenderableEntity*> m_RenderableEntities; // The entities that can be rendered.
	};
} // namespace gp1::scene
