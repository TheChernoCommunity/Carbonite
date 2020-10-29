//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Window/Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace gp1 {

	Renderer::Renderer(Window* window)
		: m_Window(window) {}

	void Renderer::Init() {
		int32_t fw, fh;
		glfwGetFramebufferSize(this->m_Window->m_NativeHandle, &fw, &fh);
		glViewport(0, 0, fw, fh);

		glfwSetFramebufferSizeCallback(this->m_Window->m_NativeHandle, [](GLFWwindow* window, int32_t width, int32_t height) {
			_CRT_UNUSED(window);
			glViewport(0, 0, width, height);
			});

		m_Mesh.m_Vertices.push_back({ { -0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } });
		m_Mesh.m_Vertices.push_back({ { 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } });
		m_Mesh.m_Vertices.push_back({ { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } });
		m_Mesh.m_Vertices.push_back({ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } });

		m_Mesh.m_Indices.push_back(3);
		m_Mesh.m_Indices.push_back(1);
		m_Mesh.m_Indices.push_back(0);
		m_Mesh.m_Indices.push_back(3);
		m_Mesh.m_Indices.push_back(2);
		m_Mesh.m_Indices.push_back(1);

		m_Material.SetShader(Shader::GetShader("shader"));
	}

	void Renderer::DeInit() {
		this->m_Mesh.CleanUpGLData();

		Shader::CleanUpShaders();
	}

	void Renderer::Render() {
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderMeshWithMaterial(this->m_Mesh, this->m_Material);
	}

	void Renderer::RenderMeshWithMaterial(Mesh& mesh, Material& material) {
		PreRenderMesh(mesh);
		PreMaterial(material);
		MidRenderMesh(mesh);
		PostMaterial(material);
		PostRenderMesh(mesh);
	}

	void Renderer::RenderMesh(Mesh& mesh) {
		PreRenderMesh(mesh);
		MidRenderMesh(mesh);
		PostRenderMesh(mesh);
	}

	void Renderer::PreRenderMesh(Mesh& mesh) {
		if (mesh.m_CullMode.m_Enabled) {
			glEnable(GL_CULL_FACE);
			glCullFace((GLenum)mesh.m_CullMode.m_Face);
		}

		if (mesh.m_DepthTest)
			glEnable(GL_DEPTH_TEST);

		if (mesh.m_BlendFunc.m_Enabled) {
			glEnable(GL_BLEND);
			glBlendFunc((GLenum)mesh.m_BlendFunc.m_SrcFunc, (GLenum)mesh.m_BlendFunc.m_DstFunc);
		}

		glPolygonMode((GLenum)mesh.m_PolygonMode.m_Face, (GLenum)mesh.m_PolygonMode.m_Mode);

		glBindVertexArray(mesh.GetVAO());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}

	void Renderer::MidRenderMesh(Mesh& mesh) {
		if (mesh.m_HasIndices)
			glDrawElements(GL_TRIANGLES, mesh.m_BufferSize, GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, mesh.m_BufferSize);
	}

	void Renderer::PostRenderMesh(Mesh& mesh) {
		_CRT_UNUSED(mesh);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void Renderer::PreMaterial(Material& material) {
		Shader* shader = material.GetShader();
		if (shader) {
			shader->Start();
			material.SetAllUniforms();
		}
	}

	void Renderer::PostMaterial(Material& material) {
		Shader* shader = material.GetShader();
		if (shader) {
			shader->Stop();
		}
	}

} // namespace gp1
