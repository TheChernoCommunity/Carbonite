//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#pragma once

#include <vector>

namespace gp1 {

	class Entity;
	class Camera;

	class Scene {
	public:
		void AttachEntity(Entity* entity);
		void DetachEntity(Entity* entity);

		void SetMainCamera(Camera* camera);
		Camera* GetMainCamera();

		const std::vector<Entity*>& GetEntities();

	private:
		std::vector<Entity*> m_Entities;
		Camera* m_MainCamera = nullptr;
	};

} // namespace gp1
