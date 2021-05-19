//
//	Created by MarcasRealAccount on 13. May. 2021
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/RenderableEntity.h"

#include <memory>

namespace gp1::renderer::opengl
{
	class OpenGLRenderer : public Renderer
	{
	public:
		virtual bool IsCompatible() const override;

		virtual void SetWindowHints() override;

	protected:
		virtual std::shared_ptr<StaticMesh>             OnCreateStaticMesh() override;
		virtual std::shared_ptr<Material>               OnCreateMaterial() override;
		virtual std::shared_ptr<ReservedUniformBuffers> OnCreateReversedUniformBuffers() override;
		virtual std::shared_ptr<Uniform>                OnCreateUniform(EUniformType type) override;
		virtual std::shared_ptr<UniformBuffer>          OnCreateUniformBuffer() override;
		virtual std::shared_ptr<ShaderProgram>          OnCreateShaderProgram() override;
		virtual std::shared_ptr<DebugRenderer>          OnCreateDebugRenderer() override;
		virtual std::shared_ptr<Texture2D>              OnCreateTexture2D() override;
		virtual std::shared_ptr<Texture2DArray>         OnCreateTexture2DArray() override;
		virtual std::shared_ptr<Texture3D>              OnCreateTexture3D() override;
		virtual std::shared_ptr<TextureCubeMap>         OnCreateTextureCubeMap() override;

		virtual void OnInit() override;
		virtual void OnDeInit() override;

		virtual void OnBeginFrame() override;
		virtual void OnEndFrame() override;

		virtual void OnRender(std::shared_ptr<scene::Camera> camera) override;

	public:
		void RenderEntity(std::shared_ptr<scene::RenderableEntity> entity);
	};
} // namespace gp1::renderer::opengl

#endif