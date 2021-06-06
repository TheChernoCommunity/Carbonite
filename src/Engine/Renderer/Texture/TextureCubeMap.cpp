//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#include "Engine/Renderer/Texture/TextureCubeMap.h"
#include "Engine/Application.h"

namespace gp1::renderer
{
	std::unique_ptr<TextureCubeMap> TextureCubeMap::Create()
	{
		return Application::GetInstance()->GetRenderer()->CreateTextureCubeMap();
	}
} // namespace gp1::renderer