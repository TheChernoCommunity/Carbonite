//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#include "Engine/Renderer/Apis/OpenGL/OpenGLRenderer.h"
#include "Engine/Renderer/Apis/OpenGL/OpenGLDebugRenderer.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLMeshData.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLSkeletalMeshData.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLStaticMeshData.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLStaticVoxelMeshData.h"
#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLMaterialData.h"
#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLShaderData.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Camera.h"

#include <stdint.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace gp1 {

	OpenGLRenderer::OpenGLRenderer(Window* window)
		: Renderer(window) {}

	RendererType OpenGLRenderer::GetRendererType() const {
		return RendererType::OPENGL;
	}

	DebugRenderer* OpenGLRenderer::CreateDebugRenderer() {
		return new OpenGLDebugRenderer(this);
	}

	MeshData* OpenGLRenderer::CreateSkeletalMeshData(Mesh* mesh) {
		return new OpenGLSkeletalMeshData(mesh);
	}

	MeshData* OpenGLRenderer::CreateStaticMeshData(Mesh* mesh) {
		return new OpenGLStaticMeshData(mesh);
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

	void OpenGLRenderer::InitRenderer() {

	}

	void OpenGLRenderer::DeInitRenderer() {

	}

	void OpenGLRenderer::RenderScene(Scene* scene, uint32_t width, uint32_t height) {
		Camera* mainCamera = scene->GetMainCamera();
		if (mainCamera) {
			glViewport(0, 0, width, height);
			glClearColor(mainCamera->m_ClearColor.r, mainCamera->m_ClearColor.g, mainCamera->m_ClearColor.b, mainCamera->m_ClearColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (auto entity : scene->GetEntities()) {
				RenderEntity(entity);
			}

			// Render Debug Objects:
			OpenGLDebugRenderer* debugRenderer = reinterpret_cast<OpenGLDebugRenderer*>(GetDebugRenderer());
			if (debugRenderer) {
				std::vector<OpenGLDebugObject*>& entities = debugRenderer->m_Entities;
				auto itr = entities.begin();
				while (itr != entities.end()) {
					OpenGLDebugObject* obj = *itr;
					if (obj->m_Lifetime > 0.0f) {
						if (glfwGetTime() - obj->m_SpawnTime > obj->m_Lifetime) {
							delete obj;
							itr = entities.erase(itr);
							continue;
						}
						obj->m_Scene = scene;
						RenderEntity(obj);
						itr++;
					} else {
						RenderEntity(obj);
						delete obj;
						itr = entities.erase(itr);
						continue;
					}
				}
			}

			glfwSwapBuffers(GetNativeWindowHandle());
		}
	}

	void OpenGLRenderer::RenderEntity(Entity* entity) {
		Scene* scene = entity->GetScene();
		if (!scene) return;

		Camera* cam = scene->GetMainCamera();
		if (!cam) return;

		Mesh* mesh = entity->GetMesh();
		Material* material = entity->GetMaterial();
		if (material) {
			if (mesh) {
				Uniform<glm::fmat4>* transformationMatrix = material->GetUniform<glm::fmat4>("transformationMatrix");
				if (transformationMatrix) transformationMatrix->m_Value = entity->GetTransformationMatrix();
				Uniform<glm::fmat4>* projectionViewMatrix = material->GetUniform<glm::fmat4>("projectionViewMatrix");
				if (projectionViewMatrix) projectionViewMatrix->m_Value = cam->GetProjectionViewMatrix();
				Uniform<glm::fvec3>* lightDirection = material->GetUniform<glm::fvec3>("lightDirection");
				if (lightDirection) lightDirection->m_Value = { 0, 0, 1 };

				RenderMeshWithMaterial(GetMeshData<OpenGLMeshData>(mesh), GetMaterialData<OpenGLMaterialData>(material));
			}
		} else if (mesh) {
			RenderMesh(GetMeshData<OpenGLMeshData>(mesh));
		}
	}

	void OpenGLRenderer::RenderMeshWithMaterial(OpenGLMeshData* mesh, OpenGLMaterialData* material) {
		PreMaterial(material);
		RenderMesh(mesh);
		PostMaterial(material);
	}

	void OpenGLRenderer::RenderMesh(OpenGLMeshData* mesh) {
		if (mesh->GetMesh<Mesh>()->m_RenderMode == RenderMode::POINTS)
			glPointSize(mesh->GetMesh<Mesh>()->m_LineWidth);
		else
			glLineWidth(mesh->GetMesh<Mesh>()->m_LineWidth);

		glBindVertexArray(mesh->GetVAO());
		for (uint8_t i = 0; i < mesh->m_NumAttribs; i++)
			glEnableVertexAttribArray(mesh->m_EnabledAttribs[i]);

		if (mesh->HasIndices())
			glDrawElements(mesh->GetRenderMode(), mesh->m_BufferSize, GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(mesh->GetRenderMode(), 0, mesh->m_BufferSize);

		for (uint8_t i = mesh->m_NumAttribs; i > 0; i--)
			glDisableVertexAttribArray(mesh->m_EnabledAttribs[i - 1]);
		glBindVertexArray(0);

		glPointSize(1);
		glLineWidth(1);
	}

	void OpenGLRenderer::PreMaterial(OpenGLMaterialData* material) {
		if (material->GetMaterial<Material>()->m_CullMode.m_Enabled) {
			glEnable(GL_CULL_FACE);
			glCullFace(material->GetCullFace());
		}

		if (material->GetMaterial<Material>()->m_DepthTest) {
			glEnable(GL_DEPTH_TEST);
		}

		if (material->GetMaterial<Material>()->m_BlendFunc.m_Enabled) {
			glEnable(GL_BLEND);
			glBlendFunc(material->GetSrcBlendFunc(), material->GetDstBlendFunc());
		}

		glPolygonMode(material->GetPolygonModeFace(), material->GetPolygonMode());

		OpenGLShaderData* shader = GetShaderData<OpenGLShaderData>(material);
		if (shader) {
			shader->Start();
			material->SetAllUniforms();
		}
	}

	void OpenGLRenderer::PostMaterial(OpenGLMaterialData* material) {
		OpenGLShaderData* shader = GetShaderData<OpenGLShaderData>(material);
		if (shader) {
			shader->Stop();
		}

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

} // namespace gp1
