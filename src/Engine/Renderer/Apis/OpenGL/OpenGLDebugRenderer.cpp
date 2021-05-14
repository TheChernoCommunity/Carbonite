//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Renderer/Apis/OpenGL/OpenGLDebugRenderer.h"
#include "Engine/Renderer/Mesh/Generators/Icosphere.h"
#include "Engine/Renderer/Shader/Material.h"
#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Renderer/Shader/Uniform.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <gtx/transform.hpp>

namespace gp1::renderer::apis::opengl::debug
{
	OpenGLDebugObject::OpenGLDebugObject(const glm::fvec4& color, float lifetime, renderer::mesh::StaticMesh* mesh)
	    : m_Lifetime(lifetime), m_Mesh(mesh), m_Material(new renderer::shader::Material())
	{
		this->m_SpawnTime = (float) glfwGetTime();

		this->m_Material->SetShader(renderer::shader::Shader::GetShader("debugShader"));
        shader::Uniform<glm::fvec4>* colorUniform = this->m_Material->GetUniform<glm::fvec4>("color");
        if (colorUniform)
            colorUniform->m_Value = color;

		this->m_Material->m_PolygonMode.m_Enabled = true;
		this->m_Material->m_CullMode.m_Enabled    = false;
		this->m_Material->m_PolygonMode.m_Face    = renderer::shader::TriangleFace::FRONT_AND_BACK;
		this->m_Material->m_PolygonMode.m_Mode    = renderer::shader::PolygonMode::LINE;
	}

	renderer::mesh::Mesh* OpenGLDebugObject::GetMesh() const
	{
		return this->m_Mesh;
	}

	renderer::shader::Material* OpenGLDebugObject::GetMaterial() const
	{
		return this->m_Material;
	}

	renderer::mesh::StaticMesh* OpenGLDebugPoint::s_PointMesh = nullptr;

	OpenGLDebugPoint::OpenGLDebugPoint(const glm::fvec3& point, const glm::fvec4& color, float lifetime)
	    : OpenGLDebugObject(color, lifetime, OpenGLDebugPoint::s_PointMesh)
	{
		this->m_Position = point;
	}

	renderer::mesh::StaticMesh* OpenGLDebugSphere::s_SphereMesh = nullptr;

	OpenGLDebugSphere::OpenGLDebugSphere(const glm::fvec3& origin, float radius, const glm::fvec4& color, float lifetime)
	    : OpenGLDebugObject(color, lifetime, OpenGLDebugSphere::s_SphereMesh)
	{
		this->m_Position = origin;
		this->m_Scale    = { radius, radius, radius };
	}

	renderer::mesh::StaticMesh* OpenGLDebugBox::s_BoxMesh = nullptr;

	OpenGLDebugBox::OpenGLDebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, const glm::fvec4& color, float lifetime)
	    : OpenGLDebugObject(color, lifetime, OpenGLDebugBox::s_BoxMesh)
	{
		this->m_Position = origin;
		this->m_Rotation = rotation;
		this->m_Scale    = extents;
	}

	renderer::mesh::StaticMesh* OpenGLDebugLine::s_LineMesh = nullptr;

	OpenGLDebugLine::OpenGLDebugLine(const glm::fvec3& start, const glm::fvec3& end, const glm::fvec4& color, float lifetime)
	    : OpenGLDebugObject(color, lifetime, OpenGLDebugLine::s_LineMesh)
	{
		this->m_Position = start;
		this->m_Scale    = end - start;
	}

	OpenGLDebugRenderer::OpenGLDebugRenderer(Renderer* renderer)
	    : DebugRenderer(renderer) {}

	RendererType OpenGLDebugRenderer::GetRendererType()
	{
		return RendererType::OPENGL;
	}

	void OpenGLDebugRenderer::DebugPoint(const glm::fvec3& point, float duration, const glm::fvec4& color)
	{
		m_Entities.push_back(new OpenGLDebugPoint(point, color, duration));
	}

	void OpenGLDebugRenderer::DebugSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color)
	{
		m_Entities.push_back(new OpenGLDebugSphere(origin, radius, color, duration));
	}

	void OpenGLDebugRenderer::DebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color)
	{
		m_Entities.push_back(new OpenGLDebugBox(origin, extents, rotation, color, duration));
	}

	void OpenGLDebugRenderer::DebugLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color)
	{
		m_Entities.push_back(new OpenGLDebugLine(start, end, color, duration));
	}

	void OpenGLDebugRenderer::Init()
	{
		OpenGLDebugPoint::s_PointMesh               = new renderer::mesh::StaticMesh();
		OpenGLDebugPoint::s_PointMesh->m_RenderMode = renderer::mesh::RenderMode::POINTS;
		OpenGLDebugPoint::s_PointMesh->m_Vertices.push_back({ { 0.0f, 0.0f, 0.0f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugPoint::s_PointMesh->m_Indices.push_back(0);
		OpenGLDebugPoint::s_PointMesh->m_LineWidth = 3.0f;

		OpenGLDebugSphere::s_SphereMesh = new renderer::mesh::StaticMesh();
		renderer::meshGenerators::GenerateIcosphere(*OpenGLDebugSphere::s_SphereMesh, 3);

		OpenGLDebugBox::s_BoxMesh               = new renderer::mesh::StaticMesh();
		OpenGLDebugBox::s_BoxMesh->m_RenderMode = renderer::mesh::RenderMode::LINES;
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { -0.5f, -0.5f, -0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { 0.5f, -0.5f, -0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { 0.5f, -0.5f, 0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { -0.5f, -0.5f, 0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { -0.5f, 0.5f, -0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { 0.5f, 0.5f, -0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { 0.5f, 0.5f, 0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { -0.5f, 0.5f, 0.5f }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(0);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(1);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(1);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(2);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(2);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(3);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(3);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(0);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(4);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(5);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(5);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(6);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(6);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(7);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(7);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(4);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(0);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(4);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(1);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(5);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(2);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(6);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(3);
		OpenGLDebugBox::s_BoxMesh->m_Indices.push_back(7);
		OpenGLDebugBox::s_BoxMesh->m_LineWidth = 3.0f;

		OpenGLDebugLine::s_LineMesh               = new renderer::mesh::StaticMesh();
		OpenGLDebugLine::s_LineMesh->m_RenderMode = renderer::mesh::RenderMode::LINES;
		OpenGLDebugLine::s_LineMesh->m_Vertices.push_back({ { 0, 0, 0 }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugLine::s_LineMesh->m_Vertices.push_back({ { 1, 1, 1 }, { 0, 1, 0 }, { 0, 0 } });
		OpenGLDebugLine::s_LineMesh->m_Indices.push_back(0);
		OpenGLDebugLine::s_LineMesh->m_Indices.push_back(1);
		OpenGLDebugLine::s_LineMesh->m_LineWidth = 3.0f;
	}

	void OpenGLDebugRenderer::DeInit()
	{
		for (scene::Entity* entity : this->m_Entities)
		{
			delete entity;
		}
		this->m_Entities.clear();

		if (OpenGLDebugPoint::s_PointMesh)
		{
			delete OpenGLDebugPoint::s_PointMesh;
			OpenGLDebugPoint::s_PointMesh = nullptr;
		}

		if (OpenGLDebugSphere::s_SphereMesh)
		{
			delete OpenGLDebugSphere::s_SphereMesh;
			OpenGLDebugSphere::s_SphereMesh = nullptr;
		}

		if (OpenGLDebugBox::s_BoxMesh)
		{
			delete OpenGLDebugBox::s_BoxMesh;
			OpenGLDebugBox::s_BoxMesh = nullptr;
		}

		if (OpenGLDebugLine::s_LineMesh)
		{
			delete OpenGLDebugLine::s_LineMesh;
			OpenGLDebugLine::s_LineMesh = nullptr;
		}
	}

} // namespace gp1::renderer::apis::opengl::debug
