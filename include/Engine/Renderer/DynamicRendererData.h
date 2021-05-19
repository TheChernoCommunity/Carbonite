//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#pragma once

#include "Engine/Renderer/RendererData.h"

namespace gp1::renderer
{
	struct DynamicRendererData : public RendererData
	{
	public:
		virtual ~DynamicRendererData() = default;

		void MarkDirty();
		void SetNonEditable();
		void SetDynamic(bool dynamic);

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
		DynamicRendererData() = default;

	protected:
		bool m_Dirty    = true;
		bool m_Editable = true;
		bool m_Dynamic  = false;
	};
} // namespace gp1::renderer