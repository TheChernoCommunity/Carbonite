//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Renderer/Apis/OpenGL/OpenGLDebugRenderer.h"
#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Renderer/Shader/Material.h"
#include "Engine/Renderer/Shader/Uniform.h"
#include "Engine/Renderer/Mesh/Generators/Icosphere.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <gtx/transform.hpp>

namespace gp1 {

	OpenGLDebugObject::OpenGLDebugObject(const glm::fvec4& color, float lifetime, StaticMesh* mesh)
		: m_Lifetime(lifetime), m_Mesh(mesh), m_Material(new Material()) {
		this->m_SpawnTime = (float)glfwGetTime();

		this->m_Material->SetShader(Shader::GetShader("debugShader"));
		this->m_Material->GetUniform<glm::fvec4>("color")->m_Value = color;

		this->m_Material->m_PolygonMode.m_Enabled = true;
		this->m_Material->m_CullMode.m_Enabled = false;
		this->m_Material->m_PolygonMode.m_Face = TriangleFace::FRONT_AND_BACK;
		this->m_Material->m_PolygonMode.m_Mode = PolygonMode::LINE;
	}

	Mesh* OpenGLDebugObject::GetMesh() const {
		return this->m_Mesh;
	}

	Material* OpenGLDebugObject::GetMaterial() const {
		return this->m_Material;
	}

	StaticMesh* OpenGLDebugPoint::m_PointMesh = nullptr;

	OpenGLDebugPoint::OpenGLDebugPoint(const glm::fvec3& point, const glm::fvec4& color, float lifetime)
		: OpenGLDebugObject(color, lifetime, OpenGLDebugPoint::m_PointMesh) {
		this->m_Position = point;
	}

	StaticMesh* OpenGLDebugSphere::m_SphereMesh = nullptr;

	OpenGLDebugSphere::OpenGLDebugSphere(const glm::fvec3& origin, float radius, const glm::fvec4& color, float lifetime)
		: OpenGLDebugObject(color, lifetime, OpenGLDebugSphere::m_SphereMesh) {
		this->m_Position = origin;
		this->m_Scale = { radius, radius, radius };
	}

	StaticMesh* OpenGLDebugBox::m_BoxMesh = nullptr;

	OpenGLDebugBox::OpenGLDebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, const glm::fvec4& color, float lifetime)
		: OpenGLDebugObject(color, lifetime, OpenGLDebugBox::m_BoxMesh) {
		this->m_Position = origin;
		this->m_Rotation = rotation;
		this->m_Scale = extents;
	}

	StaticMesh* OpenGLDebugLine::m_LineMesh = nullptr;

	OpenGLDebugLine::OpenGLDebugLine(const glm::fvec3& start, const glm::fvec3& end, const glm::fvec4& color, float lifetime)
		: OpenGLDebugObject(color, lifetime, OpenGLDebugLine::m_LineMesh) {
		this->m_Position = start;
		this->m_Scale = end - start;
	}

	OpenGLDebugRenderer::OpenGLDebugRenderer(Renderer* renderer)
		: DebugRenderer(renderer) {}

	RendererType OpenGLDebugRenderer::GetRendererType() {
		return RendererType::OPENGL;
	}

	void OpenGLDebugRenderer::DebugPoint(const glm::fvec3& point, float duration, const glm::fvec4& color) {
		m_Entities.push_back(new OpenGLDebugPoint(point, color, duration));
	}

	void OpenGLDebugRenderer::DebugSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color) {
		m_Entities.push_back(new OpenGLDebugSphere(origin, radius, color, duration));
	}

	void OpenGLDebugRenderer::DebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color) {
		m_Entities.push_back(new OpenGLDebugBox(origin, extents, rotation, color, duration));
	}

	void OpenGLDebugRenderer::DebugLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color) {
		m_Entities.push_back(new OpenGLDebugLine(start, end, color, duration));
	}

	void OpenGLDebugRenderer::Init() {
		OpenGLDebugPoint::m_PointMesh = new StaticMesh();
		OpenGLDebugPoint::m_PointMesh->m_RenderMode = RenderMode::POINTS;
		OpenGLDebugPoint::m_PointMesh->m_Vertices.push_back({ { 0.0f, 0.0f, 0.0f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugPoint::m_PointMesh->m_Indices.push_back(0);
		OpenGLDebugPoint::m_PointMesh->m_LineWidth = 3.0f;

		OpenGLDebugSphere::m_SphereMesh = new StaticMesh();
		meshGenerators::GenerateIcosphere(*OpenGLDebugSphere::m_SphereMesh, 3);

		OpenGLDebugBox::m_BoxMesh = new StaticMesh();
		OpenGLDebugBox::m_BoxMesh->m_RenderMode = RenderMode::LINES;
		OpenGLDebugBox::m_BoxMesh->m_Vertices.push_back({ { -0.5f, -0.5f, -0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::m_BoxMesh->m_Vertices.push_back({ { 0.5f, -0.5f, -0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::m_BoxMesh->m_Vertices.push_back({ { 0.5f, -0.5f, 0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::m_BoxMesh->m_Vertices.push_back({ { -0.5f, -0.5f, 0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::m_BoxMesh->m_Vertices.push_back({ { -0.5f, 0.5f, -0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::m_BoxMesh->m_Vertices.push_back({ { 0.5f, 0.5f, -0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::m_BoxMesh->m_Vertices.push_back({ { 0.5f, 0.5f, 0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::m_BoxMesh->m_Vertices.push_back({ { -0.5f, 0.5f, 0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(0);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(1);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(1);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(2);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(2);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(3);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(3);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(0);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(4);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(5);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(5);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(6);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(6);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(7);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(7);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(4);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(0);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(4);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(1);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(5);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(2);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(6);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(3);
		OpenGLDebugBox::m_BoxMesh->m_Indices.push_back(7);
		OpenGLDebugBox::m_BoxMesh->m_LineWidth = 3.0f;

		OpenGLDebugLine::m_LineMesh = new StaticMesh();
		OpenGLDebugLine::m_LineMesh->m_RenderMode = RenderMode::LINES;
		OpenGLDebugLine::m_LineMesh->m_Vertices.push_back({ { 0, 0, 0 }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugLine::m_LineMesh->m_Vertices.push_back({ { 1, 1, 1 }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugLine::m_LineMesh->m_Indices.push_back(0);
		OpenGLDebugLine::m_LineMesh->m_Indices.push_back(1);
		OpenGLDebugLine::m_LineMesh->m_LineWidth = 3.0f;
	}

	void OpenGLDebugRenderer::DeInit() {
		for (Entity* entity : this->m_Entities) {
			delete entity;
		}
		this->m_Entities.clear();

		if (OpenGLDebugPoint::m_PointMesh) {
			delete OpenGLDebugPoint::m_PointMesh;
			OpenGLDebugPoint::m_PointMesh = nullptr;
		}

		if (OpenGLDebugSphere::m_SphereMesh) {
			delete OpenGLDebugSphere::m_SphereMesh;
			OpenGLDebugSphere::m_SphereMesh = nullptr;
		}

		if (OpenGLDebugBox::m_BoxMesh) {
			delete OpenGLDebugBox::m_BoxMesh;
			OpenGLDebugBox::m_BoxMesh = nullptr;
		}

		if (OpenGLDebugLine::m_LineMesh) {
			delete OpenGLDebugLine::m_LineMesh;
			OpenGLDebugLine::m_LineMesh = nullptr;
		}
	}

} // namespace gp1
