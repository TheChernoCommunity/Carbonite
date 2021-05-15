//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/OpenGL/OpenGLRenderer.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLMeshData.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLSkeletalMeshData.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLStaticMeshData.h"
#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLStaticVoxelMeshData.h"
#include "Engine/Renderer/Apis/OpenGL/OpenGLDebugRenderer.h"
#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLMaterialData.h"
#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLShaderData.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture2DArrayData.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture2DData.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture3DData.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTextureCubeMapData.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include <stdint.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace gp1::renderer::apis::opengl
{
	Logger OpenGLRenderer::s_Logger = Logger("OpenGL Renderer");

	OpenGLRenderer::OpenGLRenderer(window::Window* window)
	    : Renderer(window) {}

	RendererType OpenGLRenderer::GetRendererType() const
	{
		return RendererType::OPENGL;
	}

	renderer::debug::DebugRenderer* OpenGLRenderer::CreateDebugRenderer()
	{
		return new debug::OpenGLDebugRenderer(this);
	}

	RendererData* OpenGLRenderer::CreateRendererData(Data* data)
	{
		if (!data) return nullptr;

		const type_info& type = data->GetType();
		if (type == typeid(renderer::mesh::SkeletalMesh))
		{
			return new mesh::OpenGLSkeletalMeshData(reinterpret_cast<renderer::mesh::SkeletalMesh*>(data));
		}
		else if (type == typeid(renderer::mesh::StaticMesh))
		{
			return new mesh::OpenGLStaticMeshData(reinterpret_cast<renderer::mesh::StaticMesh*>(data));
		}
		else if (type == typeid(renderer::mesh::StaticVoxelMesh))
		{
			return new mesh::OpenGLStaticVoxelMeshData(reinterpret_cast<renderer::mesh::StaticVoxelMesh*>(data));
		}
		else if (type == typeid(renderer::shader::Shader))
		{
			return new shader::OpenGLShaderData(reinterpret_cast<renderer::shader::Shader*>(data));
		}
		else if (type == typeid(renderer::shader::Material))
		{
			return new shader::OpenGLMaterialData(reinterpret_cast<renderer::shader::Material*>(data));
		}
		else if (type == typeid(renderer::texture::Texture2D))
		{
			return new texture::OpenGLTexture2DData(reinterpret_cast<renderer::texture::Texture2D*>(data));
		}
		else if (type == typeid(renderer::texture::Texture2DArray))
		{
			return new texture::OpenGLTexture2DArrayData(reinterpret_cast<renderer::texture::Texture2DArray*>(data));
		}
		else if (type == typeid(renderer::texture::Texture3D))
		{
			return new texture::OpenGLTexture3DData(reinterpret_cast<renderer::texture::Texture3D*>(data));
		}
		else if (type == typeid(renderer::texture::TextureCubeMap))
		{
			return new texture::OpenGLTextureCubeMapData(reinterpret_cast<renderer::texture::TextureCubeMap*>(data));
		}

		return nullptr;
	}

	uint32_t OpenGLRenderer::GetMaxTextureUnits() const
	{
		return this->m_MaxTextureUnits;
	}

	void OpenGLRenderer::InitRenderer()
	{
		int32_t maxTextureUnits;
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
		this->m_MaxTextureUnits = static_cast<uint32_t>(maxTextureUnits);

		glDebugMessageCallback(&OpenGLRenderer::ErrorMessageCallback, this);
	}

	void OpenGLRenderer::DeInitRenderer()
	{
	}

	void OpenGLRenderer::RenderScene(scene::Scene* scene, uint32_t width, uint32_t height)
	{
		scene::Camera* mainCamera = scene->GetMainCamera();
		if (mainCamera)
		{
			glViewport(0, 0, width, height);
			glClearColor(mainCamera->m_ClearColor.r, mainCamera->m_ClearColor.g, mainCamera->m_ClearColor.b, mainCamera->m_ClearColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (auto entity : scene->GetEntities())
			{
				RenderEntity(entity);
			}

			// Render Debug Objects:
			debug::OpenGLDebugRenderer* debugRenderer = reinterpret_cast<debug::OpenGLDebugRenderer*>(GetDebugRenderer());
			if (debugRenderer)
			{
				std::vector<debug::OpenGLDebugObject*>& entities = debugRenderer->m_Entities;
				auto                                    itr      = entities.begin();
				while (itr != entities.end())
				{
					debug::OpenGLDebugObject* obj = *itr;
					if (obj->m_Lifetime > 0.0f)
					{
						if (glfwGetTime() - obj->m_SpawnTime > obj->m_Lifetime)
						{
							delete obj;
							itr = entities.erase(itr);
							continue;
						}
						obj->m_Scene = scene;
						RenderEntity(obj);
						itr++;
					}
					else
					{
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

	void OpenGLRenderer::RenderEntity(scene::Entity* entity)
	{
		scene::Scene* scene = entity->GetScene();
		if (!scene) return;

		scene::Camera* cam = scene->GetMainCamera();
		if (!cam) return;

		renderer::mesh::Mesh*       mesh     = entity->GetMesh();
		renderer::shader::Material* material = entity->GetMaterial();
		if (material)
		{
			if (mesh)
			{
				renderer::shader::Uniform<glm::fmat4>* transformationMatrix = material->GetUniform<glm::fmat4>("transformationMatrix");
				if (transformationMatrix) transformationMatrix->m_Value = entity->GetTransformationMatrix();
				renderer::shader::Uniform<glm::fmat4>* projectionViewMatrix = material->GetUniform<glm::fmat4>("projectionViewMatrix");
				if (projectionViewMatrix) projectionViewMatrix->m_Value = cam->GetProjectionViewMatrix();
				renderer::shader::Uniform<glm::fvec3>* lightDirection = material->GetUniform<glm::fvec3>("lightDirection");
				if (lightDirection) lightDirection->m_Value = { 0, 0, 1 };

				RenderMeshWithMaterial(mesh, material);
			}
		}
		else if (mesh)
		{
			RenderMesh(mesh);
		}
	}

	void OpenGLRenderer::RenderMeshWithMaterial(renderer::mesh::Mesh* mesh, renderer::shader::Material* material)
	{
		PreMaterial(material);
		RenderMesh(mesh);
		PostMaterial(material);
	}

	void OpenGLRenderer::RenderMesh(renderer::mesh::Mesh* mesh)
	{
		mesh::OpenGLMeshData* meshData = mesh->GetRendererData<mesh::OpenGLMeshData>(this);
		if (!meshData) return;

		if (mesh->m_RenderMode == renderer::mesh::RenderMode::POINTS)
			glPointSize(mesh->m_LineWidth);
		else
			glLineWidth(mesh->m_LineWidth);

		glBindVertexArray(meshData->GetVAO());

		if (meshData->HasIndices())
			glDrawElements(meshData->GetRenderMode(), meshData->m_BufferSize, GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(meshData->GetRenderMode(), 0, meshData->m_BufferSize);

		glBindVertexArray(0);

		glPointSize(1);
		glLineWidth(1);
	}

	void OpenGLRenderer::PreMaterial(renderer::shader::Material* material)
	{
		shader::OpenGLMaterialData* materialData = material->GetRendererData<shader::OpenGLMaterialData>(this);
		if (!materialData) return;

		if (material->m_CullMode.m_Enabled)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(materialData->GetCullFace());
		}

		if (material->m_DepthTest) glEnable(GL_DEPTH_TEST);

		if (material->m_BlendFunc.m_Enabled)
		{
			glEnable(GL_BLEND);
			glBlendFunc(materialData->GetSrcBlendFunc(), materialData->GetDstBlendFunc());
		}

		glPolygonMode(materialData->GetPolygonModeFace(), materialData->GetPolygonMode());

		shader::OpenGLShaderData* shaderData = material->GetShader()->GetRendererData<shader::OpenGLShaderData>(this);
		if (shaderData)
		{
			shaderData->Start();
			materialData->SetAllUniforms(this);
		}
	}

	void OpenGLRenderer::PostMaterial(renderer::shader::Material* material)
	{
		shader::OpenGLShaderData* shader = material->GetShader()->GetRendererData<shader::OpenGLShaderData>(this);
		if (shader) shader->Stop();

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void OpenGLRenderer::ErrorMessageCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char* message, const void* userParam)
	{
		_CRT_UNUSED(length);
		_CRT_UNUSED(userParam);

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			OpenGLRenderer::s_Logger.LogTrace("Source: %d, Type: %d, Id: %d, Message: %s", source, type, id, message);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			OpenGLRenderer::s_Logger.LogDebug("Source: %d, Type: %d, Id: %d, Message: %s", source, type, id, message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			OpenGLRenderer::s_Logger.LogWarning("Source: %d, Type: %d, Id: %d, Message: %s", source, type, id, message);
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			OpenGLRenderer::s_Logger.LogError("Source: %d, Type: %d, Id: %d, Message: %s", source, type, id, message);
			break;
		}
	}

} // namespace gp1::renderer::apis::opengl
