//
//	Created by MarcasRealAccount on 13. May. 2021
//

#pragma once

namespace gp1::renderer
{
	struct RendererData
	{
	public:
		void MarkDirty();
		void SetNonEditable();
		void SetDynamic(bool dynamic);

		inline bool IsDirty() const
		{
			return this->m_Dirty;
		}

		inline bool IsEditable() const
		{
			return this->m_Editable;
		}

		inline bool IsDynamic() const
		{
			return this->m_Dynamic;
		}

	protected:
		bool m_Dirty    = true;
		bool m_Editable = true;
		bool m_Dynamic  = false;
	};
} // namespace gp1::renderer