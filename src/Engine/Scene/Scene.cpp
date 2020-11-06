//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Entity.h"

namespace gp1 {

	void Scene::AttachEntity(Entity* entity) {
		if (entity->m_Scene)
			entity->m_Scene->DetachEntity(entity);
		this->m_Entities.push_back(entity);
		entity->m_Scene = this;
	}

	void Scene::DetachEntity(Entity* entity) {
		if (entity->m_Scene != this)
			return;

		auto itr = this->m_Entities.begin();
		while (itr != this->m_Entities.end()) {
			if (*itr == entity) {
				this->m_Entities.erase(itr);
				entity->m_Scene = nullptr;
				break;
			}
			itr++;
		}
	}

	void Scene::SetMainCamera(Camera* camera) {
		if (reinterpret_cast<Entity*>(camera)->m_Scene == this) {
			this->m_MainCamera = camera;
		}
	}

	Camera* Scene::GetMainCamera() {
		return this->m_MainCamera;
	}

	const std::vector<Entity*>& Scene::GetEntities() {
		return this->m_Entities;
	}

} // namespace gp1
