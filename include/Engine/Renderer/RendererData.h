//
//	Created by MarcasRealAccount on 13. May. 2021
//

#pragma once

namespace gp1::renderer
{
	struct RendererData
	{
	public:
		virtual ~RendererData() = default;

		void MarkDirty();
		void SetNonEditable();
		void SetDynamic(bool dynamic);

		inline void* GetNext() const
		{
			return m_Next;
		}

		template <typename T>
		inline T* GetNext() const
		{
			return reinterpret_cast<T*>(m_Next);
		}

		inline bool IsDirty() const
		{
			return m_Dirty;
		}

		inline bool IsEditable() const
		{
			return m_Editable;
		}

		inline bool IsDynamic() const
		{
			return m_Dynamic;
		}

	protected:
		bool m_Dirty    = true;
		bool m_Editable = true;
		bool m_Dynamic  = false;

		void* m_Next = nullptr;
	};
} // namespace gp1::renderer