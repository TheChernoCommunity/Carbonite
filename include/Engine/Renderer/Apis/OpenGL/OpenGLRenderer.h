//
//	Created by MarcasRealAccount on 13. May. 2021
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLShaderProgram.h"
#include "Engine/Renderer/Material/Material.h"
#include "Engine/Renderer/Mesh/StaticMesh.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Shader/ShaderProgram.h"
#include "Engine/Scene/RenderableEntity.h"

#include <memory>
#include <vector>

namespace gp1::renderer::opengl
{
	class OpenGLRenderer : public Renderer
	{
	public:
		virtual std::shared_ptr<StaticMesh>    CreateStaticMesh() override;
		virtual std::shared_ptr<Material>      CreateMaterial() override;
		virtual std::shared_ptr<ShaderProgram> CreateShaderProgram() override;

		virtual bool IsCompatible() const override;

		virtual void SetWindowHints() override;

		virtual void Init() override;
		virtual void DeInit() override;

		virtual void Render(std::shared_ptr<scene::Camera> camera) override;
		void         RenderEntity(std::shared_ptr<scene::RenderableEntity> entity);

	private:
		std::vector<std::weak_ptr<OpenGLShaderProgram>> m_ShaderPrograms;
	};
} // namespace gp1::renderer::opengl

#endif