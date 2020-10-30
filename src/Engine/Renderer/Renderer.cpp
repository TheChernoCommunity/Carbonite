//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Renderer/Shader/Uniform.h"
#include "Engine/Renderer/StaticMesh.h"
#include "Engine/Renderer/SkeletalMesh.h"
#include "Engine/Renderer/StaticVoxelMesh.h"
#include "Engine/Renderer/Shader/Material.h"
#include "Engine/Window/Window.h"

#include <glad/glad.h>

namespace gp1 {

	Renderer::Renderer(Window* window)
		: m_Window(window) {}

	GLFWwindow* Renderer::GetNativeWindowHandle() const {
		return this->m_Window->m_NativeHandle;
	}

	Renderer* Renderer::GetRenderer(RendererType rendererType, Window* window) {
		switch (rendererType) {
		case RendererType::OPENGL:
			return new OpenGLRenderer(window);
		}
		return nullptr;
	}

	OpenGLRenderer::OpenGLRenderer(Window* window)
		: Renderer(window) {}

	RendererType OpenGLRenderer::GetRendererType() const {
		return RendererType::OPENGL;
	}

	void OpenGLRenderer::Init() {
		int32_t fw, fh;
		glfwGetFramebufferSize(GetNativeWindowHandle(), &fw, &fh);
		glViewport(0, 0, fw, fh);

		glfwSetFramebufferSizeCallback(GetNativeWindowHandle(), [](GLFWwindow* window, int32_t width, int32_t height) {
			_CRT_UNUSED(window);
			glViewport(0, 0, width, height);
			});

		m_Mesh = new StaticMesh();
		m_Material = new Material();

		m_Mesh->m_Vertices.push_back({ { -0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } });
		m_Mesh->m_Vertices.push_back({ { 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } });
		m_Mesh->m_Vertices.push_back({ { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } });
		m_Mesh->m_Vertices.push_back({ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } });

		m_Mesh->m_Indices.push_back(3);
		m_Mesh->m_Indices.push_back(1);
		m_Mesh->m_Indices.push_back(0);
		m_Mesh->m_Indices.push_back(3);
		m_Mesh->m_Indices.push_back(2);
		m_Mesh->m_Indices.push_back(1);

		m_Material->SetShader(Shader::GetShader("shader"));
		Uniform<Mat4f>* transformationMatrix = m_Material->GetUniform<Mat4f>("transformationMatrix");
		if (transformationMatrix) {
			transformationMatrix->m_Value.m30 = 0.5f;
		}
	}

	void OpenGLRenderer::DeInit() {
		delete m_Mesh;
		delete m_Material;

		Shader::CleanUpShaders();
	}

	void OpenGLRenderer::Render() {
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderMeshWithMaterial(reinterpret_cast<OpenGLMeshData*>(this->m_Mesh->GetMeshData(this)), reinterpret_cast<OpenGLMaterialData*>(this->m_Material->GetMaterialData(this)));
	}

	bool OpenGLRenderer::IsMeshDataUsable(MeshData* meshData) {
		return meshData->GetRendererType() == GetRendererType();
	}

	bool OpenGLRenderer::IsShaderDataUsable(ShaderData* shaderData) {
		return shaderData->GetRendererType() == GetRendererType();
	}

	bool OpenGLRenderer::IsMaterialDataUsable(MaterialData* materialData) {
		return materialData->GetRendererType() == GetRendererType();
	}

	MeshData* OpenGLRenderer::CreateStaticMeshData(Mesh* mesh) {
		return new OpenGLStaticMeshData(mesh);
	}

	MeshData* OpenGLRenderer::CreateSkeletalMeshData(Mesh* mesh) {
		return new OpenGLSkeletalMeshData(mesh);
	}

	MeshData* OpenGLRenderer::CreateStaticVoxelMeshData(Mesh* mesh) {
		return new OpenGLStaticVoxelMeshData(mesh);
	}

	ShaderData* OpenGLRenderer::CreateShaderData(Shader* shader) {
		return new OpenGLShaderData(shader);
	}

	MaterialData* OpenGLRenderer::CreateMaterialData(Material* material) {
		return new OpenGLMaterialData(material);
	}

	void OpenGLRenderer::RenderMeshWithMaterial(OpenGLMeshData* mesh, OpenGLMaterialData* material) {
		PreMaterial(material);
		RenderMesh(mesh);
		PostMaterial(material);
	}

	void OpenGLRenderer::RenderMesh(OpenGLMeshData* mesh) {
		glBindVertexArray(mesh->GetVAO());
		for (uint8_t i = 0; i < mesh->m_NumAttribs; i++)
			glEnableVertexAttribArray(mesh->m_EnabledAttribs[i]);

		if (mesh->HasIndices())
			glDrawElements(GL_TRIANGLES, mesh->m_BufferSize, GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, mesh->m_BufferSize);

		for (uint8_t i = mesh->m_NumAttribs; i > 0; i--)
			glDisableVertexAttribArray(mesh->m_EnabledAttribs[i - 1]);
		glBindVertexArray(0);
	}

	void OpenGLRenderer::PreMaterial(OpenGLMaterialData* material) {
		if (material->GetMaterial()->m_CullMode.m_Enabled) {
			glEnable(GL_CULL_FACE);
			glCullFace(material->GetCullFace());
		}

		if (material->GetMaterial()->m_DepthTest) {
			glEnable(GL_DEPTH_TEST);
		}

		if (material->GetMaterial()->m_BlendFunc.m_Enabled) {
			glEnable(GL_BLEND);
			glBlendFunc(material->GetSrcBlendFunc(), material->GetDstBlendFunc());
		}

		glPolygonMode(material->GetPolygonModeFace(), material->GetPolygonMode());

		OpenGLShaderData* shader = reinterpret_cast<OpenGLShaderData*>(material->GetMaterial()->GetShader()->GetShaderData(this));
		if (shader) {
			shader->Start();
			material->SetAllUniforms();
		}
	}

	void OpenGLRenderer::PostMaterial(OpenGLMaterialData* material) {
		OpenGLShaderData* shader = reinterpret_cast<OpenGLShaderData*>(material->GetMaterial()->GetShader()->GetShaderData(this));
		if (shader) {
			shader->Stop();
		}

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

} // namespace gp1
