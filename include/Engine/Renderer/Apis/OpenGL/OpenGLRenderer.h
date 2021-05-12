#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Renderer.h"

namespace gp1::renderer::opengl
{
	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer(window::Window* window);

		virtual StaticMesh* CreateStaticMesh() override;

		virtual bool IsCompatible() const override;

		virtual void SetWindowHints() override;

		virtual void Init() override;
		virtual void DeInit() override;

		virtual void Render(scene::Camera* camera) override;
	};
} // namespace gp1::renderer::opengl

#endif