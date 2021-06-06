//
//	Created by MarcasRealAccount on 13. May. 2021
//

#pragma once

#include "Engine/Renderer/DebugRenderer.h"
#include "Engine/Renderer/Material/Material.h"
#include "Engine/Renderer/Material/ReservedUniformBuffers.h"
#include "Engine/Renderer/Material/Uniform.h"
#include "Engine/Renderer/Material/UniformBuffer.h"
#include "Engine/Renderer/Mesh/StaticMesh.h"
#include "Engine/Renderer/Shader/ShaderProgram.h"
#include "Engine/Renderer/Texture/Texture2D.h"
#include "Engine/Renderer/Texture/Texture2DArray.h"
#include "Engine/Renderer/Texture/Texture3D.h"
#include "Engine/Renderer/Texture/TextureCubeMap.h"
#include "Engine/Scene/Camera.h"

#include <memory>
#include <vector>

namespace gp1::renderer
{
	class Renderer
	{
	public:
		friend RendererData;

	public:
		virtual ~Renderer() = default;

		std::unique_ptr<StaticMesh>     CreateStaticMesh();
		std::unique_ptr<Material>       CreateMaterial();
		std::unique_ptr<Uniform>        CreateUniform(EUniformType type);
		std::unique_ptr<UniformBuffer>  CreateUniformBuffer();
		std::unique_ptr<ShaderProgram>  CreateShaderProgram();
		std::unique_ptr<Texture2D>      CreateTexture2D();
		std::unique_ptr<Texture2DArray> CreateTexture2DArray();
		std::unique_ptr<Texture3D>      CreateTexture3D();
		std::unique_ptr<TextureCubeMap> CreateTextureCubeMap();

		virtual void SetWindowHints() = 0;

		virtual bool IsCompatible() const = 0;

		void Init();
		void DeInit();

		void BeginFrame();
		void EndFrame();
		void Render(scene::Camera* camera);

		ReservedUniformBuffers* GetReservedUniformBuffers() const
		{
			return m_ReservedUniformBuffers.get();
		}

		DebugRenderer* GetDebugRenderer() const
		{
			return m_DebugRenderer.get();
		}

	protected:
		Renderer() = default;

		virtual std::unique_ptr<StaticMesh>             OnCreateStaticMesh()               = 0;
		virtual std::unique_ptr<Material>               OnCreateMaterial()                 = 0;
		virtual std::unique_ptr<Uniform>                OnCreateUniform(EUniformType type) = 0;
		virtual std::unique_ptr<UniformBuffer>          OnCreateUniformBuffer()            = 0;
		virtual std::unique_ptr<ShaderProgram>          OnCreateShaderProgram()            = 0;
		virtual std::unique_ptr<Texture2D>              OnCreateTexture2D()                = 0;
		virtual std::unique_ptr<Texture2DArray>         OnCreateTexture2DArray()           = 0;
		virtual std::unique_ptr<Texture3D>              OnCreateTexture3D()                = 0;
		virtual std::unique_ptr<TextureCubeMap>         OnCreateTextureCubeMap()           = 0;
		std::unique_ptr<ReservedUniformBuffers>         CreateReservedUniformBuffers();
		virtual std::unique_ptr<ReservedUniformBuffers> OnCreateReservedUniformBuffers() = 0;
		virtual std::unique_ptr<DebugRenderer>          OnCreateDebugRenderer()          = 0;

		virtual void OnInit() {}
		virtual void OnDeInit() {}

		virtual void OnBeginFrame() {}
		virtual void OnEndFrame() {}
		virtual void OnRender(scene::Camera* camera) = 0;

	private:
		void AddRendererData(RendererData* data);
		void RemoveRendererData(RendererData* data);

	protected:
		std::unique_ptr<ReservedUniformBuffers> m_ReservedUniformBuffers;
		std::unique_ptr<DebugRenderer>          m_DebugRenderer;

		std::vector<RendererData*> m_RendererDatas;
		std::vector<RendererData*> m_UpdatableRendererDatas;

		// TODO(MarcasRealAccount): This stuff might not be needed for anything
		// std::vector<StaticMesh*>     m_StaticMeshes;
		// std::vector<Material*>       m_Materials;
		// std::vector<Uniform*>        m_Uniforms;
		// std::vector<UniformBuffer*>  m_UniformBuffers;
		// std::vector<ShaderProgram*>  m_ShaderPrograms;
		// std::vector<Texture2D*>      m_Texture2Ds;
		// std::vector<Texture2DArray*> m_Texture2DArrays;
		// std::vector<Texture3D*>      m_Texture3Ds;
		// std::vector<TextureCubeMap*> m_TextureCubeMaps;
	};
} // namespace gp1::renderer