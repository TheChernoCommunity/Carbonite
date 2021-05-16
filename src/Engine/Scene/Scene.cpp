//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Scene/Scene.h"

namespace gp1::scene
{
	void Scene::AttachEntity(std::shared_ptr<Entity> entity)
	{
		if (entity->m_Scene)
			entity->m_Scene->DetachEntity(entity);
		this->m_Entities.push_back(entity);
		entity->m_Scene = this;
	}

	void Scene::DetachEntity(std::shared_ptr<Entity> entity)
	{
		if (entity->m_Scene != this)
			return;

		for (auto itr = m_Entities.begin(); itr != m_Entities.end();)
		{
			if (itr->expired())
			{
				itr = m_Entities.erase(itr);
			}
			else
			{
				if (itr->lock() == entity)
				{
					m_Entities.erase(itr);
					entity->m_Scene = nullptr;
					break;
				}
				itr++;
			}
		}
	}

	void Scene::Update(float deltaTime)
	{
		for (auto itr = m_Entities.begin(); itr != m_Entities.end();)
		{
			if (itr->expired())
			{
				itr = m_Entities.erase(itr);
			}
			else
			{
				std::shared_ptr<Entity> entity = itr->lock();
				entity->Update(deltaTime);
				itr++;
			}
		}
	}
} // namespace gp1::scene
