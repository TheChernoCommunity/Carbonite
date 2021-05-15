//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#pragma once

#include <glm.hpp>

namespace gp1
{
	namespace renderer::mesh
	{
		struct Mesh;
	}

	namespace renderer::shader
	{
		struct Material;
	}

	namespace scene
	{
		class Scene;

		class Entity
		{
		public:
			~Entity();

			// Update this entity.
			virtual void Update(float deltaTime);

			// Get the transformation matrix of this entity.
			const glm::fmat4& GetTransformationMatrix(bool negativeTranslation = false);
			// Gets a mesh if this entity has one else returns nullptr.
			virtual renderer::mesh::Mesh* GetMesh() const;
			// Gets a material if this entity has one else returns nullptr.
			virtual renderer::shader::Material* GetMaterial() const;

			// Get the scene this entity is part of.
			Scene* GetScene() const;

			friend Scene;

		public:
			glm::fvec3 m_Position { 0.0f, 0.0f, 0.0f }; // The position of this entity.
			glm::fvec3 m_Rotation { 0.0f, 0.0f, 0.0f }; // The rotation of this entity.
			glm::fvec3 m_Scale { 1.0f, 1.0f, 1.0f };    // The scale of this entity.

		protected:
			glm::fvec3 m_PPosition { 0.0f, 0.0f, 0.0f };                // The previous position of this entity.
			glm::fvec3 m_PRotation { 0.0f, 0.0f, 0.0f };                // The previous rotation of this entity.
			glm::fvec3 m_PScale { 1.0f, 1.0f, 1.0f };                   // The previous scale of this entity.
			glm::fmat4 m_CachedTransformationMatrix = glm::fmat4(1.0f); // The cached transformation matrix of this entity.

			Scene* m_Scene = nullptr; // The scene this entity is part of.
		};

	} // namespace scene

} // namespace gp1
