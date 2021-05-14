#include "Engine/Renderer/RendererData.h"

namespace gp1::renderer
{
	Data::~Data()
	{
		if (this->m_RendererData)
		{
			this->m_RendererData->CleanUp();
			delete this->m_RendererData;
		}
	}

	const std::type_info& Data::GetType() const
	{
		return this->m_Type;
	}

	RendererData::~RendererData()
	{
		if (this->m_Data) this->m_Data->m_RendererData = nullptr;
	}

} // namespace gp1::renderer
