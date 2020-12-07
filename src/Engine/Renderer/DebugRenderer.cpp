//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Renderer/DebugRenderer.h"

namespace gp1::renderer::debug
{
	DebugRenderer* DebugRenderer::s_DebugRenderer = nullptr;

	DebugRenderer::DebugRenderer(Renderer* renderer)
	    : m_Renderer(renderer) {}

	void DebugRenderer::Init() {}

	void DebugRenderer::DeInit() {}

	void DebugRenderer::DebugDrawPoint(const glm::fvec3& point, float duration, const glm::fvec4& color)
	{
		if (DebugRenderer::s_DebugRenderer) DebugRenderer::s_DebugRenderer->DebugPoint(point, duration, color);
	}

	void DebugRenderer::DebugDrawSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color)
	{
		if (DebugRenderer::s_DebugRenderer) DebugRenderer::s_DebugRenderer->DebugSphere(origin, radius, duration, color);
	}

	void DebugRenderer::DebugDrawBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color)
	{
		if (DebugRenderer::s_DebugRenderer) DebugRenderer::s_DebugRenderer->DebugBox(origin, extents, rotation, duration, color);
	}

	void DebugRenderer::DebugDrawABox(const glm::ivec3& position, float duration, const glm::fvec4& color)
	{
		DebugDrawBox({ position.x + 0.5f, position.y + 0.5f, position.z + 0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, duration, color);
	}

	void DebugRenderer::DebugDrawLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color)
	{
		if (DebugRenderer::s_DebugRenderer) DebugRenderer::s_DebugRenderer->DebugLine(start, end, duration, color);
	}

	void DebugRenderer::SetDebugRenderer(DebugRenderer* debugRenderer)
	{
		CleanUp();

		DebugRenderer::s_DebugRenderer = debugRenderer;
		if (DebugRenderer::s_DebugRenderer) DebugRenderer::s_DebugRenderer->Init();
	}

	void DebugRenderer::CleanUp()
	{
		if (DebugRenderer::s_DebugRenderer)
		{
			DebugRenderer::s_DebugRenderer->DeInit();
			delete DebugRenderer::s_DebugRenderer;
		}
	}

} // namespace gp1::renderer::debug
