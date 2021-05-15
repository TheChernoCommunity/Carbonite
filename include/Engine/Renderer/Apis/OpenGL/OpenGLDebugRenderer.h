//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#pragma once

#include "Engine/Renderer/DebugRenderer.h"
#include "Engine/Scene/Entity.h"

#include <vector>

namespace gp1::renderer
{
	namespace mesh
	{
		struct StaticMesh;
	}

	namespace apis::opengl
	{
		class OpenGLRenderer;

		namespace debug
		{
			class OpenGLDebugRenderer;

			struct OpenGLDebugObject : public scene::Entity
			{
			public:
				OpenGLDebugObject(const glm::fvec4& color, float lifetime, renderer::mesh::StaticMesh* mesh);

				virtual renderer::mesh::Mesh*       GetMesh() const override;
				virtual renderer::shader::Material* GetMaterial() const override;

				friend OpenGLRenderer;

			public:
				float m_SpawnTime;
				float m_Lifetime;

				renderer::mesh::StaticMesh* m_Mesh;
				renderer::shader::Material* m_Material;
			};

			struct OpenGLDebugPoint : public OpenGLDebugObject
			{
			public:
				OpenGLDebugPoint(const glm::fvec3& point, const glm::fvec4& color, float lifetime);

				friend OpenGLDebugRenderer;

			private:
				static renderer::mesh::StaticMesh* s_PointMesh;
			};

			struct OpenGLDebugSphere : public OpenGLDebugObject
			{
			public:
				OpenGLDebugSphere(const glm::fvec3& origin, float radius, const glm::fvec4& color, float lifetime);

				friend OpenGLDebugRenderer;

			private:
				static renderer::mesh::StaticMesh* s_SphereMesh;
			};

			struct OpenGLDebugBox : public OpenGLDebugObject
			{
			public:
				OpenGLDebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, const glm::fvec4& color, float lifetime);

				friend OpenGLDebugRenderer;

			private:
				static renderer::mesh::StaticMesh* s_BoxMesh;
			};

			struct OpenGLDebugLine : public OpenGLDebugObject
			{
			public:
				OpenGLDebugLine(const glm::fvec3& start, const glm::fvec3& end, const glm::fvec4& color, float lifetime);

				friend OpenGLDebugRenderer;

			private:
				static renderer::mesh::StaticMesh* s_LineMesh;
			};

			class OpenGLDebugRenderer : public renderer::debug::DebugRenderer
			{
			public:
				OpenGLDebugRenderer(Renderer* renderer);

				virtual RendererType GetRendererType() override;

				friend OpenGLRenderer;

			private:
				virtual void DebugPoint(const glm::fvec3& point, float duration, const glm::fvec4& color) override;
				virtual void DebugSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color) override;
				virtual void DebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color) override;
				virtual void DebugLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color) override;

				virtual void Init() override;
				virtual void DeInit() override;

			private:
				std::vector<OpenGLDebugObject*> m_Entities; // The entities this debug renderer has.
			};

		} // namespace debug

	} // namespace apis::opengl

} // namespace gp1::renderer
