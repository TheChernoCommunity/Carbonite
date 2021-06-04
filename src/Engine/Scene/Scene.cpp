//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Scene/Scene.h"

namespace gp1::scene
{
	void Scene::AttachEntity(Entity* entity)
	{
		if (entity->m_Scene)
			entity->m_Scene->DetachEntity(entity);
		this->m_Entities.push_back(entity);
		if (entity->IsUpdatable())
			this->m_UpdatableEntities.push_back(entity);
		if (entity->IsRenderable())
			this->m_RenderableEntities.push_back(reinterpret_cast<RenderableEntity*>(entity));
		entity->m_Scene = this;
	}

	void Scene::DetachEntity(Entity* entity)
	{
		if (entity->m_Scene != this)
			return;

		auto itr0 = std::find(m_Entities.begin(), m_Entities.end(), entity);
		if (itr0 != m_Entities.end())
			m_Entities.erase(itr0);
		auto itr1 = std::find(m_UpdatableEntities.begin(), m_UpdatableEntities.end(), entity);
		if (itr1 != m_UpdatableEntities.end())
			m_UpdatableEntities.erase(itr1);
		auto itr2 = std::find(m_RenderableEntities.begin(), m_RenderableEntities.end(), entity);
		if (itr2 != m_RenderableEntities.end())
			m_RenderableEntities.erase(itr2);
		entity->m_Scene = nullptr;
	}

	void Scene::Update(float deltaTime)
	{
		for (auto entity : m_UpdatableEntities)
			entity->Update(deltaTime);
	}
} // namespace gp1::scene
