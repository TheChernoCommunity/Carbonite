//
//	Created by MarcasRealAccount on 13. May. 2021
//

#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Renderers.h"

namespace gp1::renderer
{
	std::unique_ptr<StaticMesh> Renderer::CreateStaticMesh()
	{
		auto data = OnCreateStaticMesh();
		AddRendererData(data.get());
		return data;
	}

	std::unique_ptr<Material> Renderer::CreateMaterial()
	{
		auto data = OnCreateMaterial();
		AddRendererData(data.get());
		return data;
	}

	std::unique_ptr<Uniform> Renderer::CreateUniform(EUniformType type)
	{
		auto data = OnCreateUniform(type);
		AddRendererData(data.get());
		return data;
	}

	std::unique_ptr<UniformBuffer> Renderer::CreateUniformBuffer()
	{
		auto data = OnCreateUniformBuffer();
		AddRendererData(data.get());
		return data;
	}

	std::unique_ptr<ShaderProgram> Renderer::CreateShaderProgram()
	{
		auto data = OnCreateShaderProgram();
		AddRendererData(data.get());
		return data;
	}

	std::unique_ptr<Texture2D> Renderer::CreateTexture2D()
	{
		auto data = OnCreateTexture2D();
		AddRendererData(data.get());
		return data;
	}

	std::unique_ptr<Texture2DArray> Renderer::CreateTexture2DArray()
	{
		auto data = OnCreateTexture2DArray();
		AddRendererData(data.get());
		return data;
	}

	std::unique_ptr<Texture3D> Renderer::CreateTexture3D()
	{
		auto data = OnCreateTexture3D();
		AddRendererData(data.get());
		return data;
	}

	std::unique_ptr<TextureCubeMap> Renderer::CreateTextureCubeMap()
	{
		auto data = OnCreateTextureCubeMap();
		AddRendererData(data.get());
		return data;
	}

	void Renderer::Init()
	{
		OnInit();

		m_DebugRenderer = OnCreateDebugRenderer();
		DebugRenderer::SetDebugRenderer(m_DebugRenderer.get());

		m_ReservedUniformBuffers = CreateReservedUniformBuffers();
	}

	void Renderer::DeInit()
	{
		DebugRenderer::SetDebugRenderer(nullptr);

		m_DebugRenderer.reset();
		m_ReservedUniformBuffers.reset();

		OnDeInit();
	}

	void Renderer::BeginFrame()
	{
		for (auto updatableRendererData : m_UpdatableRendererDatas)
			updatableRendererData->Update();

		OnBeginFrame();
	}

	void Renderer::EndFrame()
	{
		OnEndFrame();
	}

	void Renderer::Render(scene::Camera* camera)
	{
		OnRender(camera);
	}

	std::unique_ptr<ReservedUniformBuffers> Renderer::CreateReservedUniformBuffers()
	{
		auto data = OnCreateReservedUniformBuffers();
		AddRendererData(data.get());
		return data;
	}

	void Renderer::AddRendererData(RendererData* data)
	{
		if (data)
		{
			m_RendererDatas.push_back(data);
			if (data->IsUpdatable())
				m_UpdatableRendererDatas.push_back(data);
		}
	}

	void Renderer::RemoveRendererData(RendererData* data)
	{
		if (data)
		{
			auto itr0 = std::find(m_RendererDatas.begin(), m_RendererDatas.end(), data);
			if (itr0 != m_RendererDatas.end())
				m_RendererDatas.erase(itr0);

			auto itr1 = std::find(m_UpdatableRendererDatas.begin(), m_UpdatableRendererDatas.end(), data);
			if (itr1 != m_UpdatableRendererDatas.end())
				m_UpdatableRendererDatas.erase(itr1);
		}
	}
} // namespace gp1::renderer