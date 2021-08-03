//
//	Created by MarcasRealAccount on 13. May. 2021
//

#include "Engine/Renderer/RendererData.h"

#include "Engine/Application.h"

namespace gp1::renderer
{
	RendererData::~RendererData()
	{
		Application::GetInstance()->GetRenderer()->RemoveRendererData(this);
	}
} // namespace gp1::renderer