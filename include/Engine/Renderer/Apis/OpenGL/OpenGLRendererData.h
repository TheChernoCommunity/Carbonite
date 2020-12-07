#pragma once

#include "Engine/Renderer/RendererData.h"

namespace gp1::renderer::apis::opengl
{
	class OpenGLRenderer;

	struct OpenGLRendererData : public RendererData
	{
	public:
		template <typename T>
		OpenGLRendererData(T* data)
		    : RendererData(data)
		{
		}

		virtual RendererType GetRendererType() const override;
	};

} // namespace gp1::renderer::apis::opengl
