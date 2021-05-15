#include "Engine/Renderer/Apis/OpenGL/OpenGLRendererData.h"

namespace gp1::renderer::apis::opengl
{
	RendererType OpenGLRendererData::GetRendererType() const
	{
		return RendererType::OPENGL;
	}

} // namespace gp1::renderer::apis::opengl
