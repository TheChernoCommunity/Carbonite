#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

namespace gp1
{
	namespace window
	{
		class Window;
	}

	namespace renderer
	{
		class Renderer;

		struct RendererEntry
		{
		public:
			using Function = std::function<std::shared_ptr<Renderer>(window::Window*)>;

			RendererEntry(const std::string& name, uint32_t priority, Function createRenderer);

		public:
			std::string             m_Name;
			uint32_t                m_Priority;
			Function                m_CreateRenderer;
			std::weak_ptr<Renderer> m_Renderer;
		};

		class Renderers
		{
		public:
			static Renderers* const s_Renderers;

			inline const std::vector<RendererEntry>& GetEntries() const
			{
				return m_Renderers;
			}

			std::shared_ptr<Renderer> GetRenderer(const std::string& name, window::Window* window);
			std::shared_ptr<Renderer> GetBestRenderer(window::Window* window);

		private:
			Renderers(const std::initializer_list<RendererEntry>& entries);

			std::vector<RendererEntry> m_Renderers;
		};
	} // namespace renderer
} // namespace gp1