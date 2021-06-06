//
//	Created by MarcasRealAccount on 16. May. 2021
//

#pragma once

#include <memory>

#include <glm.hpp>

namespace gp1::renderer
{
	class DebugRenderer
	{
	public:
		static constexpr glm::fvec4 DebugColor = { 1.0f, 0.0f, 1.0f, 1.0f };
		static DebugRenderer*       s_DebugRenderer;

		static void DebugDrawPoint(const glm::fvec3& position, float duration = 1.0f, const glm::fvec4& color = DebugColor);
		static void DebugDrawSphere(const glm::fvec3& origin, float radius, float duration = 1.0f, const glm::fvec4& color = DebugColor);
		static void DebugDrawBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration = 1.0f, const glm::fvec4& color = DebugColor);
		static void DebugDrawLine(const glm::fvec3& start, const glm::fvec3& end, float duration = 1.0f, const glm::fvec4& color = DebugColor);

		static void DebugDrawABox(const glm::fvec3& origin, const glm::fvec3& extents, float duration = 1.0f, const glm::fvec4& color = DebugColor)
		{
			DebugDrawBox(origin, extents, { 0.0f, 0.0f, 0.0f }, duration, color);
		}

		static void SetDebugRenderer(DebugRenderer* debugRenderer);
		static void CleanUp();

	public:
		virtual ~DebugRenderer() = default;

		virtual void DrawPoint(const glm::fvec3& position, float duration, const glm::fvec4& color)                                                    = 0;
		virtual void DrawSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color)                                       = 0;
		virtual void DrawBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color) = 0;
		virtual void DrawLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color)                                 = 0;

		virtual void Init()   = 0;
		virtual void DeInit() = 0;

	protected:
		DebugRenderer() = default;
	};
} // namespace gp1::renderer