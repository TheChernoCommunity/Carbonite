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
		virtual ~Renderer() = default;

		std::shared_ptr<StaticMesh>     CreateStaticMesh();
		std::shared_ptr<Material>       CreateMaterial();
		std::shared_ptr<Uniform>        CreateUniform(EUniformType type);
		std::shared_ptr<UniformBuffer>  CreateUniformBuffer();
		std::shared_ptr<ShaderProgram>  CreateShaderProgram();
		std::shared_ptr<Texture2D>      CreateTexture2D();
		std::shared_ptr<Texture2DArray> CreateTexture2DArray();
		std::shared_ptr<Texture3D>      CreateTexture3D();
		std::shared_ptr<TextureCubeMap> CreateTextureCubeMap();

		virtual void SetWindowHints() = 0;

		virtual bool IsCompatible() const = 0;

		void Init();
		void DeInit();

		void BeginFrame();
		void EndFrame();
		void Render(std::shared_ptr<scene::Camera> camera);

		inline std::shared_ptr<ReservedUniformBuffers> GetReservedUniformBuffers() const
		{
			return m_ReservedUniformBuffers;
		}

		inline std::shared_ptr<DebugRenderer> GetDebugRenderer() const
		{
			return m_DebugRenderer;
		}

	protected:
		Renderer() = default;

	protected:
		virtual std::shared_ptr<StaticMesh>             OnCreateStaticMesh()               = 0;
		virtual std::shared_ptr<Material>               OnCreateMaterial()                 = 0;
		virtual std::shared_ptr<ReservedUniformBuffers> OnCreateReversedUniformBuffers()   = 0;
		virtual std::shared_ptr<Uniform>                OnCreateUniform(EUniformType type) = 0;
		virtual std::shared_ptr<UniformBuffer>          OnCreateUniformBuffer()            = 0;
		virtual std::shared_ptr<ShaderProgram>          OnCreateShaderProgram()            = 0;
		virtual std::shared_ptr<DebugRenderer>          OnCreateDebugRenderer()            = 0;
		virtual std::shared_ptr<Texture2D>              OnCreateTexture2D()                = 0;
		virtual std::shared_ptr<Texture2DArray>         OnCreateTexture2DArray()           = 0;
		virtual std::shared_ptr<Texture3D>              OnCreateTexture3D()                = 0;
		virtual std::shared_ptr<TextureCubeMap>         OnCreateTextureCubeMap()           = 0;

		virtual void OnInit() {}
		virtual void OnDeInit() {}

		virtual void OnBeginFrame() {}
		virtual void OnEndFrame() {}
		virtual void OnRender(std::shared_ptr<scene::Camera> camera) = 0;

	protected:
		std::shared_ptr<ReservedUniformBuffers> m_ReservedUniformBuffers;
		std::shared_ptr<DebugRenderer>          m_DebugRenderer;

		std::vector<std::weak_ptr<StaticMesh>>     m_StaticMeshes;
		std::vector<std::weak_ptr<Material>>       m_Materials;
		std::vector<std::weak_ptr<Uniform>>        m_Uniforms;
		std::vector<std::weak_ptr<UniformBuffer>>  m_UniformBuffers;
		std::vector<std::weak_ptr<ShaderProgram>>  m_ShaderPrograms;
		std::vector<std::weak_ptr<Texture2D>>      m_Texture2Ds;
		std::vector<std::weak_ptr<Texture2DArray>> m_Texture2DArrays;
		std::vector<std::weak_ptr<Texture3D>>      m_Texture3Ds;
		std::vector<std::weak_ptr<TextureCubeMap>> m_TextureCubeMaps;

		std::vector<std::weak_ptr<RendererData>> m_UpdatableRendererDatas;
	};
} // namespace gp1::renderer