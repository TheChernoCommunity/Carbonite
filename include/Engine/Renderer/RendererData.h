//
//	Created by MarcasRealAccount on 13. May. 2021
//

#pragma once

#include <memory>
#include <type_traits>

namespace gp1::renderer
{
	struct RendererData
	{
	public:
		friend class Renderer;

	public:
		virtual ~RendererData();

		void* GetNext() const
		{
			return m_Next;
		}

		template <typename T>
		T* GetNext() const
		{
			return reinterpret_cast<T*>(m_Next);
		}

		virtual void Update() {}
		virtual bool IsUpdatable() const
		{
			return false;
		}

	protected:
		RendererData() = default;

	protected:
		void* m_Next = nullptr;
	};
} // namespace gp1::renderer