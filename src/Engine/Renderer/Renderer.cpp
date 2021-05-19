//
//	Created by MarcasRealAccount on 13. May. 2021
//

#include "Engine/Renderer/Renderer.h"

namespace gp1::renderer
{
	std::shared_ptr<StaticMesh> Renderer::CreateStaticMesh()
	{
		std::shared_ptr<StaticMesh> mesh = OnCreateStaticMesh();
		if (mesh)
		{
			m_StaticMeshes.push_back(mesh);
			mesh->m_This = mesh;

			if (mesh->IsUpdatable())
				m_UpdatableRendererDatas.push_back(mesh);
		}
		return mesh;
	}

	std::shared_ptr<Material> Renderer::CreateMaterial()
	{
		std::shared_ptr<Material> material = OnCreateMaterial();
		if (material)
		{
			m_Materials.push_back(material);
			material->m_This = material;

			if (material->IsUpdatable())
				m_UpdatableRendererDatas.push_back(material);
		}
		return material;
	}

	std::shared_ptr<Uniform> Renderer::CreateUniform(EUniformType type)
	{
		std::shared_ptr<Uniform> uniform = OnCreateUniform(type);
		if (uniform)
		{
			m_Uniforms.push_back(uniform);
			uniform->m_This = uniform;

			if (uniform->IsUpdatable())
				m_UpdatableRendererDatas.push_back(uniform);
		}
		return uniform;
	}

	std::shared_ptr<UniformBuffer> Renderer::CreateUniformBuffer()
	{
		std::shared_ptr<UniformBuffer> uniformBuffer = OnCreateUniformBuffer();
		if (uniformBuffer)
		{
			m_UniformBuffers.push_back(uniformBuffer);
			uniformBuffer->m_This = uniformBuffer;

			if (uniformBuffer->IsUpdatable())
				m_UpdatableRendererDatas.push_back(uniformBuffer);
		}
		return uniformBuffer;
	}

	std::shared_ptr<ShaderProgram> Renderer::CreateShaderProgram()
	{
		std::shared_ptr<ShaderProgram> shaderProgram = OnCreateShaderProgram();
		if (shaderProgram)
		{
			m_ShaderPrograms.push_back(shaderProgram);
			shaderProgram->m_This = shaderProgram;
		}
		return shaderProgram;
	}

	std::shared_ptr<Texture2D> Renderer::CreateTexture2D()
	{
		std::shared_ptr<Texture2D> texture2D = OnCreateTexture2D();
		if (texture2D)
		{
			m_Texture2Ds.push_back(texture2D);
			texture2D->m_This = texture2D;

			if (texture2D->IsUpdatable())
				m_UpdatableRendererDatas.push_back(texture2D);
		}
		return texture2D;
	}

	std::shared_ptr<Texture2DArray> Renderer::CreateTexture2DArray()
	{
		std::shared_ptr<Texture2DArray> texture2DArray = OnCreateTexture2DArray();
		if (texture2DArray)
		{
			m_Texture2DArrays.push_back(texture2DArray);
			texture2DArray->m_This = texture2DArray;

			if (texture2DArray->IsUpdatable())
				m_UpdatableRendererDatas.push_back(texture2DArray);
		}
		return texture2DArray;
	}

	std::shared_ptr<Texture3D> Renderer::CreateTexture3D()
	{
		std::shared_ptr<Texture3D> texture3D = OnCreateTexture3D();
		if (texture3D)
		{
			m_Texture3Ds.push_back(texture3D);
			texture3D->m_This = texture3D;

			if (texture3D->IsUpdatable())
				m_UpdatableRendererDatas.push_back(texture3D);
		}
		return texture3D;
	}

	std::shared_ptr<TextureCubeMap> Renderer::CreateTextureCubeMap()
	{
		std::shared_ptr<TextureCubeMap> textureCubeMap = OnCreateTextureCubeMap();
		if (textureCubeMap)
		{
			m_TextureCubeMaps.push_back(textureCubeMap);
			textureCubeMap->m_This = textureCubeMap;

			if (textureCubeMap->IsUpdatable())
				m_UpdatableRendererDatas.push_back(textureCubeMap);
		}
		return textureCubeMap;
	}

	void Renderer::Init()
	{
		OnInit();

		m_DebugRenderer = OnCreateDebugRenderer();
		DebugRenderer::SetDebugRenderer(m_DebugRenderer);

		m_ReservedUniformBuffers = OnCreateReversedUniformBuffers();
	}

	void Renderer::DeInit()
	{
		m_DebugRenderer = nullptr;
		DebugRenderer::SetDebugRenderer(nullptr);

		m_ReservedUniformBuffers = nullptr;

		OnDeInit();
	}

	void Renderer::BeginFrame()
	{
		for (auto itr = m_StaticMeshes.begin(); itr != m_StaticMeshes.end();)
		{
			if (itr->expired())
				itr = m_StaticMeshes.erase(itr);
			else
				itr++;
		}

		for (auto itr = m_Materials.begin(); itr != m_Materials.end();)
		{
			if (itr->expired())
				itr = m_Materials.erase(itr);
			else
				itr++;
		}

		for (auto itr = m_Uniforms.begin(); itr != m_Uniforms.end();)
		{
			if (itr->expired())
				itr = m_Uniforms.erase(itr);
			else
				itr++;
		}

		for (auto itr = m_UniformBuffers.begin(); itr != m_UniformBuffers.end();)
		{
			if (itr->expired())
				itr = m_UniformBuffers.erase(itr);
			else
				itr++;
		}

		for (auto itr = m_ShaderPrograms.begin(); itr != m_ShaderPrograms.end();)
		{
			if (itr->expired())
			{
				itr = m_ShaderPrograms.erase(itr);
			}
			else
			{
				std::shared_ptr<ShaderProgram> shaderProgram = itr->lock();
				shaderProgram->Update();
				itr++;
			}
		}

		for (auto itr = m_Texture2Ds.begin(); itr != m_Texture2Ds.end();)
		{
			if (itr->expired())
				itr = m_Texture2Ds.erase(itr);
			else
				itr++;
		}

		for (auto itr = m_Texture2DArrays.begin(); itr != m_Texture2DArrays.end();)
		{
			if (itr->expired())
				itr = m_Texture2DArrays.erase(itr);
			else
				itr++;
		}

		for (auto itr = m_Texture3Ds.begin(); itr != m_Texture3Ds.end();)
		{
			if (itr->expired())
				itr = m_Texture3Ds.erase(itr);
			else
				itr++;
		}

		for (auto itr = m_TextureCubeMaps.begin(); itr != m_TextureCubeMaps.end();)
		{
			if (itr->expired())
				itr = m_TextureCubeMaps.erase(itr);
			else
				itr++;
		}

		for (auto itr = m_UpdatableRendererDatas.begin(); itr != m_UpdatableRendererDatas.end();)
		{
			if (itr->expired())
			{
				itr = m_UpdatableRendererDatas.erase(itr);
			}
			else
			{
				std::shared_ptr<RendererData> data = itr->lock();
				data->Update();
				itr++;
			}
		}

		OnBeginFrame();
	}

	void Renderer::EndFrame()
	{
		OnEndFrame();
	}

	void Renderer::Render(std::shared_ptr<scene::Camera> camera)
	{
		OnRender(camera);
	}
} // namespace gp1::renderer