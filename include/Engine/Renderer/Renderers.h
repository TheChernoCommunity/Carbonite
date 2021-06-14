//
//	Created by MarcasRealAccount on 13. May. 2021
//
//	Implements a system for storing all compiled renderers.
//

#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace gp1::renderer
{
	class Renderer;

	struct RendererEntry
	{
	public:
		using Function = std::function<std::unique_ptr<Renderer>()>;

		RendererEntry(const std::string& name, uint32_t priority, Function createRenderer);

	public:
		std::string m_Name;
		uint32_t    m_Priority;
		Function    m_CreateRenderer;
		Renderer*   m_Renderer;
	};

	class Renderers
	{
	public:
		static Renderers* const s_Renderers;

		const std::vector<RendererEntry>& GetEntries() const
		{
			return m_Renderers;
		}

		std::unique_ptr<Renderer> GetRenderer(const std::string& name);
		std::unique_ptr<Renderer> GetBestRenderer();

		std::string GetName(Renderer* renderer) const;

	private:
		Renderers(const std::initializer_list<RendererEntry>& entries);

	private:
		std::vector<RendererEntry> m_Renderers;
	};
} // namespace gp1::renderer