//
//	Created by MarcasRealAccount on 16. May. 2021
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Application.h"
#include "Engine/Renderer/Apis/OpenGL/OpenGLDebugRenderer.h"
#include "Engine/Renderer/Apis/OpenGL/OpenGLRenderer.h"
#include "Engine/Renderer/Mesh/Generators/Icosphere.h"
#include "Engine/Renderer/Shader/ShaderProgram.h"

#include <cstring>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace gp1::renderer::opengl
{
	std::unique_ptr<ShaderProgram> OpenGLDebugObject::s_DebugShaderProgram = nullptr;

	OpenGLDebugObject::OpenGLDebugObject(float duration, const glm::fvec4& color, Mesh* mesh)
	    : m_Duration(duration), m_Mesh(mesh), m_Material(Application::GetInstance()->GetRenderer()->CreateMaterial())
	{
		m_SpawnTime = static_cast<float>(glfwGetTime());

		m_Material->SetShaderProgram(s_DebugShaderProgram.get());
		UniformFVec4* colorUniform = m_Material->GetUniform<UniformFVec4>("Object", "color");
		if (colorUniform && colorUniform->GetType() == UniformFVec4::GetTypeS())
			colorUniform->SetValue(color);

		m_Material->m_CullMode.m_Enabled    = true;
		m_Material->m_PolygonMode.m_Enabled = true;
		m_Material->m_PolygonMode.m_Face    = ETriangleFace::FrontAndBack;
		m_Material->m_PolygonMode.m_Mode    = EPolygonMode::Line;
	}

	std::unique_ptr<StaticMesh> OpenGLDebugPoint::s_PointMesh = nullptr;

	OpenGLDebugPoint::OpenGLDebugPoint(const glm::fvec3& position, float duration, const glm::fvec4& color)
	    : OpenGLDebugObject(duration, color, s_PointMesh.get())
	{
		m_Position = position;
	}

	std::unique_ptr<StaticMesh> OpenGLDebugSphere::s_SphereMesh = nullptr;

	OpenGLDebugSphere::OpenGLDebugSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color)
	    : OpenGLDebugObject(duration, color, s_SphereMesh.get())
	{
		m_Position                    = origin;
		m_Scale                       = { radius, radius, radius };
		m_Material->m_CullMode.m_Face = ETriangleFace::Front; // HACK(MarcasRealAccount): The Icosahedron generator is generating the mesh with the wrong face orientation so flip the cull face.
	}

	std::unique_ptr<StaticMesh> OpenGLDebugBox::s_BoxMesh = nullptr;

	OpenGLDebugBox::OpenGLDebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color)
	    : OpenGLDebugObject(duration, color, s_BoxMesh.get())
	{
		m_Position = origin;
		m_Rotation = rotation;
		m_Scale    = extents;
	}

	std::unique_ptr<StaticMesh> OpenGLDebugLine::s_LineMesh = nullptr;

	OpenGLDebugLine::OpenGLDebugLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color)
	    : OpenGLDebugObject(duration, color, s_LineMesh.get())
	{
		m_Position = start;
		m_Scale    = end - start;
	}

	void OpenGLDebugRenderer::DrawPoint(const glm::fvec3& position, float duration, const glm::fvec4& color)
	{
		m_Entities.push_back(std::make_unique<OpenGLDebugPoint>(position, duration, color));
	}

	void OpenGLDebugRenderer::DrawSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color)
	{
		m_Entities.push_back(std::make_unique<OpenGLDebugSphere>(origin, radius, duration, color));
	}

	void OpenGLDebugRenderer::DrawBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color)
	{
		m_Entities.push_back(std::make_unique<OpenGLDebugBox>(origin, extents, rotation, duration, color));
	}

	void OpenGLDebugRenderer::DrawLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color)
	{
		m_Entities.push_back(std::make_unique<OpenGLDebugLine>(start, end, duration, color));
	}

	void OpenGLDebugRenderer::Init()
	{
		const char* pVertexShaderCode   = R"(
#version 430 core

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inNormal;
layout(location = 2) in vec2 inUV;

layout(std140, binding = 0) uniform Camera {
	mat4 Camera_projectionViewMatrix;
};

uniform Object {
	mat4 Object_transformationMatrix;
	vec4 Object_color;
};

void main(void) {
	gl_Position = Camera_projectionViewMatrix * Object_transformationMatrix * inPosition;
}
)";
		const char* pFragmentShaderCode = R"(
#version 430 core

layout(location = 0) out vec4 outColor;

uniform Object {
	mat4 Object_transformationMatrix;
	vec4 Object_color;
};

void main(void) {
	outColor = Object_color;
}
)";

		OpenGLDebugObject::s_DebugShaderProgram = ShaderProgram::Create();

		renderer::Shader* vertexShader = OpenGLDebugObject::s_DebugShaderProgram->AddShader(renderer::EShaderType::VertexShader);
		vertexShader->m_Data           = std::vector<uint8_t>(pVertexShaderCode, pVertexShaderCode + strlen(pVertexShaderCode));

		renderer::Shader* fragmentShader = OpenGLDebugObject::s_DebugShaderProgram->AddShader(renderer::EShaderType::FragmentShader);
		fragmentShader->m_Data           = std::vector<uint8_t>(pFragmentShaderCode, pFragmentShaderCode + strlen(pFragmentShaderCode));

		OpenGLDebugObject::s_DebugShaderProgram->AddUniformBuffer("Object");
		OpenGLDebugObject::s_DebugShaderProgram->AddUniformBufferElement("Object", "transformationMatrix", renderer::EUniformType::FMat4);
		OpenGLDebugObject::s_DebugShaderProgram->AddUniformBufferElement("Object", "color", renderer::EUniformType::FVec4);

		OpenGLDebugPoint::s_PointMesh               = StaticMesh::Create();
		OpenGLDebugPoint::s_PointMesh->m_RenderMode = ERenderMode::Points;
		OpenGLDebugPoint::s_PointMesh->m_Vertices.push_back({ { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
		OpenGLDebugPoint::s_PointMesh->m_Indices.push_back(0);
		OpenGLDebugPoint::s_PointMesh->m_LineWidth = 3.0f;

		OpenGLDebugSphere::s_SphereMesh = StaticMesh::Create();
		meshGenerators::GenerateIcosphere(OpenGLDebugSphere::s_SphereMesh.get(), 3);

		OpenGLDebugBox::s_BoxMesh               = StaticMesh::Create();
		OpenGLDebugBox::s_BoxMesh->m_RenderMode = ERenderMode::Lines;
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { -0.5f, -0.5f, -0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { 0.5f, -0.5f, -0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { 0.5f, -0.5f, 0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { -0.5f, -0.5f, 0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { -0.5f, 0.5f, -0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { 0.5f, 0.5f, -0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { 0.5f, 0.5f, 0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
		OpenGLDebugBox::s_BoxMesh->m_Vertices.push_back({ { -0.5f, 0.5f, 0.5f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
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

		OpenGLDebugLine::s_LineMesh               = StaticMesh::Create();
		OpenGLDebugLine::s_LineMesh->m_RenderMode = ERenderMode::Lines;
		OpenGLDebugLine::s_LineMesh->m_Vertices.push_back({ { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
		OpenGLDebugLine::s_LineMesh->m_Vertices.push_back({ { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
		OpenGLDebugLine::s_LineMesh->m_Indices.push_back(0);
		OpenGLDebugLine::s_LineMesh->m_Indices.push_back(1);
		OpenGLDebugLine::s_LineMesh->m_LineWidth = 3.0f;
	}

	void OpenGLDebugRenderer::DeInit()
	{
		m_Entities.clear();
		OpenGLDebugObject::s_DebugShaderProgram.reset();
		OpenGLDebugPoint::s_PointMesh.reset();
		OpenGLDebugSphere::s_SphereMesh.reset();
		OpenGLDebugBox::s_BoxMesh.reset();
		OpenGLDebugLine::s_LineMesh.reset();
	}

	void OpenGLDebugRenderer::Render()
	{
		OpenGLRenderer* renderer = reinterpret_cast<OpenGLRenderer*>(Application::GetInstance()->GetRenderer());

		for (auto itr = m_Entities.begin(); itr != m_Entities.end();)
		{
			auto& entity = *itr;
			renderer->RenderEntity(entity.get());

			if (entity->m_Duration <= 0.0f || glfwGetTime() - entity->m_SpawnTime > entity->m_Duration)
				itr = m_Entities.erase(itr);
			else
				itr++;
		}
	}
} // namespace gp1::renderer::opengl
#endif