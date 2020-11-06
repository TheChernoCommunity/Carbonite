//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#pragma once

#include <glm.hpp>

namespace gp1 {

	struct Mesh;
	class Material;
	class Scene;

	class Entity {
	public:
		~Entity();

		const glm::fmat4& GetTransformationMatrix();
		virtual Mesh* GetMesh() const;
		virtual Material* GetMaterial() const;

		Scene* GetScene() const;

		friend Scene;

	public:
		glm::fvec3 m_Position{ 0.0f, 0.0f, 0.0f };
		glm::fvec3 m_Rotation{ 0.0f, 0.0f, 0.0f };
		glm::fvec3 m_Scale{ 1.0f, 1.0f, 1.0f };

	protected:
		glm::fvec3 m_PPosition{ 0.0f, 0.0f, 0.0f };
		glm::fvec3 m_PRotation{ 0.0f, 0.0f, 0.0f };
		glm::fvec3 m_PScale{ 1.0f, 1.0f, 1.0f };
		glm::fmat4 m_CachedTransformationMatrix = glm::fmat4(1.0f);

		Scene* m_Scene = nullptr;
	};

} // namespace gp1
