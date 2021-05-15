//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#pragma once

#include <vector>

namespace gp1::scene
{
	class Entity;
	class Camera;

	class Scene
	{
	public:
		// Attach an entity to this scene.
		void AttachEntity(Entity* entity);
		// Detach an entity from this scene.
		void DetachEntity(Entity* entity);

		// Set the main camera of this scene.
		void SetMainCamera(Camera* camera);
		// Get the main camera of this scene.
		Camera* GetMainCamera();

		// Get all entities this scene holds.
		const std::vector<Entity*>& GetEntities();

	private:
		std::vector<Entity*> m_Entities;             // The entities this scene holds.
		Camera*              m_MainCamera = nullptr; // The main camera of this scene.
	};

} // namespace gp1::scene
