//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#pragma once

#include "Engine/Renderer/Renderer.h"

#include <glm.hpp>

namespace gp1 {

	namespace debug {
		const glm::fvec4 DEBUG_COLOR = { 1.0f, 0.0f, 1.0f, 1.0f };
	}

	class DebugRenderer {
	public:
		DebugRenderer(Renderer* renderer);
		virtual ~DebugRenderer() = default;

		friend Renderer;

		virtual RendererType GetRendererType() = 0;
	private:
		virtual void DebugPoint(const glm::fvec3& point, float duration, const glm::fvec4& color) = 0;
		virtual void DebugSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color) = 0;
		virtual void DebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color) = 0;
		virtual void DebugLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color) = 0;

		virtual void Init();
		virtual void DeInit();

	public:
		static void DebugDrawPoint(const glm::fvec3& point, float duration = 1.0f, const glm::fvec4& color = debug::DEBUG_COLOR);
		static void DebugDrawSphere(const glm::fvec3& origin, float radius, float duration = 1.0f, const glm::fvec4& color = debug::DEBUG_COLOR);
		static void DebugDrawBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration = 1.0f, const glm::fvec4& color = debug::DEBUG_COLOR);
		static void DebugDrawABox(const glm::ivec3& position, float duration = 1.0f, const glm::fvec4& color = debug::DEBUG_COLOR);
		static void DebugDrawLine(const glm::fvec3& start, const glm::fvec3& end, float duration = 1.0f, const glm::fvec4& color = debug::DEBUG_COLOR);

	private:
		static void SetDebugRenderer(DebugRenderer* debugRenderer);
		static void CleanUp();

	private:
		Renderer* m_Renderer;

	private:
		static DebugRenderer* m_DebugRenderer;
	};

} // namespace gp1
