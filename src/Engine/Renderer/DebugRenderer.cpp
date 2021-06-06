//
//	Created by MarcasRealAccount on 16. May. 2021
//

#include "Engine/Renderer/DebugRenderer.h"
#include "Engine/Application.h"

namespace gp1::renderer
{
	DebugRenderer* DebugRenderer::s_DebugRenderer = nullptr;

	void DebugRenderer::DebugDrawPoint(const glm::fvec3& position, float duration, const glm::fvec4& color)
	{
		if (s_DebugRenderer)
			s_DebugRenderer->DrawPoint(position, duration, color);
	}

	void DebugRenderer::DebugDrawSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color)
	{
		if (s_DebugRenderer)
			s_DebugRenderer->DrawSphere(origin, radius, duration, color);
	}

	void DebugRenderer::DebugDrawBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color)
	{
		if (s_DebugRenderer)
			s_DebugRenderer->DrawBox(origin, extents, rotation, duration, color);
	}

	void DebugRenderer::DebugDrawLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color)
	{
		if (s_DebugRenderer)
			s_DebugRenderer->DrawLine(start, end, duration, color);
	}

	void DebugRenderer::SetDebugRenderer(DebugRenderer* debugRenderer)
	{
		CleanUp();

		s_DebugRenderer = debugRenderer;
		if (s_DebugRenderer)
			s_DebugRenderer->Init();
	}

	void DebugRenderer::CleanUp()
	{
		if (s_DebugRenderer)
		{
			s_DebugRenderer->DeInit();
			s_DebugRenderer = nullptr;
		}
	}
} // namespace gp1::renderer