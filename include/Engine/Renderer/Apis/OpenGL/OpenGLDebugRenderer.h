//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#pragma once

#include "Engine/Renderer/DebugRenderer.h"
#include "Engine/Scene/Entity.h"

#include <vector>

namespace gp1 {

	class OpenGLRenderer;
	class OpenGLDebugRenderer;

	struct StaticMesh;

	struct OpenGLDebugObject : public Entity {
	public:
		OpenGLDebugObject(const glm::fvec4& color, float lifetime, StaticMesh* mesh);

		virtual Mesh* GetMesh() const override;
		virtual Material* GetMaterial() const override;

		friend OpenGLRenderer;

	public:
		float m_SpawnTime;
		float m_Lifetime;

		StaticMesh* m_Mesh;
		Material* m_Material;
	};

	struct OpenGLDebugPoint : public OpenGLDebugObject {
	public:
		OpenGLDebugPoint(const glm::fvec3& point, const glm::fvec4& color, float lifetime);

		friend OpenGLDebugRenderer;

	private:
		static StaticMesh* m_PointMesh;
	};

	struct OpenGLDebugSphere : public OpenGLDebugObject {
	public:
		OpenGLDebugSphere(const glm::fvec3& origin, float radius, const glm::fvec4& color, float lifetime);

		friend OpenGLDebugRenderer;

	private:
		static StaticMesh* m_SphereMesh;
	};

	struct OpenGLDebugBox : public OpenGLDebugObject {
	public:
		OpenGLDebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, const glm::fvec4& color, float lifetime);

		friend OpenGLDebugRenderer;

	private:
		static StaticMesh* m_BoxMesh;
	};

	struct OpenGLDebugLine : public OpenGLDebugObject {
	public:
		OpenGLDebugLine(const glm::fvec3& start, const glm::fvec3& end, const glm::fvec4& color, float lifetime);

		friend OpenGLDebugRenderer;

	private:
		static StaticMesh* m_LineMesh;
	};

	class OpenGLDebugRenderer : public DebugRenderer {
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
		std::vector<OpenGLDebugObject*> m_Entities;
	};

} // namespace gp1
