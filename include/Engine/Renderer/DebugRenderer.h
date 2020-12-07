//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#pragma once

#include "Engine/Renderer/Renderer.h"

#include <glm.hpp>

namespace gp1::renderer::debug
{
	const glm::fvec4 DEBUG_COLOR = { 1.0f, 0.0f, 1.0f, 1.0f }; // The default debug color.

	class DebugRenderer
	{
	public:
		DebugRenderer(Renderer* renderer);
		virtual ~DebugRenderer() = default;

		// Get the renderer type of this debug renderer.
		virtual RendererType GetRendererType() = 0;

		friend Renderer;

	private:
		// Draw a debug point.
		virtual void DebugPoint(const glm::fvec3& point, float duration, const glm::fvec4& color) = 0;
		// Draw a debug sphere.
		virtual void DebugSphere(const glm::fvec3& origin, float radius, float duration, const glm::fvec4& color) = 0;
		// Draw a debug box.
		virtual void DebugBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration, const glm::fvec4& color) = 0;
		// Draw a debug line.
		virtual void DebugLine(const glm::fvec3& start, const glm::fvec3& end, float duration, const glm::fvec4& color) = 0;

		// Initialize the debug renderer.
		virtual void Init();
		// Deinitialize the debug renderer.
		virtual void DeInit();

	public:
		// Draw a debug point.
		static void DebugDrawPoint(const glm::fvec3& point, float duration = 1.0f, const glm::fvec4& color = debug::DEBUG_COLOR);
		// Draw a debug sphere.
		static void DebugDrawSphere(const glm::fvec3& origin, float radius, float duration = 1.0f, const glm::fvec4& color = debug::DEBUG_COLOR);
		// Draw a debug box.
		static void DebugDrawBox(const glm::fvec3& origin, const glm::fvec3& extents, const glm::fvec3& rotation, float duration = 1.0f, const glm::fvec4& color = debug::DEBUG_COLOR);
		// Draw an axis aligned debug box.
		static void DebugDrawABox(const glm::ivec3& position, float duration = 1.0f, const glm::fvec4& color = debug::DEBUG_COLOR);
		// Draw a debug line.
		static void DebugDrawLine(const glm::fvec3& start, const glm::fvec3& end, float duration = 1.0f, const glm::fvec4& color = debug::DEBUG_COLOR);

	private:
		// Set the debug renderer to use.
		static void SetDebugRenderer(DebugRenderer* debugRenderer);
		// Clean up the debug renderer.
		static void CleanUp();

	private:
		Renderer* m_Renderer; // The renderer this debug renderer is part of.

	private:
		static DebugRenderer* s_DebugRenderer; // The static debug renderer instance.
	};

} // namespace gp1::renderer::debug
