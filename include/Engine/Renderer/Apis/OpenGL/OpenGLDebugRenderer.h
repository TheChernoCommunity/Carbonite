//
//	Created by MarcasRealAccount on 16. May. 2021
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/DebugRenderer.h"
#include "Engine/Renderer/Material/Material.h"
#include "Engine/Renderer/Mesh/Mesh.h"
#include "Engine/Renderer/Mesh/StaticMesh.h"
#include "Engine/Scene/RenderableEntity.h"

#include <memory>

#include <glm.hpp>

namespace gp1::renderer::opengl
{
	struct OpenGLDebugObject : public scene::RenderableEntity
	{
	public:
		friend class OpenGLDebugRenderer;

	private:
		static std::shared_ptr<ShaderProgram> s_DebugShaderProgram;

	public:
		inline virtual std::shared_ptr<Mesh> GetMesh() const override
		{
			return m_Mesh;
		}

		inline virtual std::shared_ptr<Material> GetMaterial() const override
		{
			return m_Material;
		}

	protected:
		OpenGLDebugObject(float duration, const glm::fvec4& color, std::shared_ptr<Mesh> mesh);

	protected:
		float m_SpawnTime;
		float m_Duration;

		std::shared_ptr<Mesh>     m_Mesh;
		std::shared_ptr<Material> m_Material;
	};

	struct OpenGLDebugPoint : public OpenGLDebugObject
	{
	public:
		friend class OpenGLDebugRenderer;

	private:
		static std::shared_ptr<StaticMesh> s_PointMesh;

	public:
		OpenGLDebugPoint(const glm::fvec3& position, float duration, const glm::fvec4& color);
	};

	struct OpenGLDebugSphere : public OpenGLDebugObject
	{
	public:
		friend class OpenGLDebugRenderer;

	private:
		static std::shared_ptr<StaticMesh> s_SphereMesh;

	public:
		OpenGLDebugSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color);
	};

	struct OpenGLDebugBox : public OpenGLDebugObject
	{
	public:
		friend class OpenGLDebugRenderer;

	private:
		static std::shared_ptr<StaticMesh> s_BoxMesh;

	public:
		OpenGLDebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color);
	};

	struct OpenGLDebugLine : public OpenGLDebugObject
	{
	public:
		friend class OpenGLDebugRenderer;

	private:
		static std::shared_ptr<StaticMesh> s_LineMesh;

	public:
		OpenGLDebugLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color);
	};

	class OpenGLDebugRenderer : public DebugRenderer
	{
	public:
		virtual void DrawPoint(const glm::fvec3& position, float duration, const glm::fvec4& color) override;
		virtual void DrawSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color) override;
		virtual void DrawBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color) override;
		virtual void DrawLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color) override;

		virtual void Init() override;
		virtual void DeInit() override;

		void Render();

	private:
		std::vector<std::shared_ptr<OpenGLDebugObject>> m_Entities;
	};
} // namespace gp1::renderer::opengl
#endif