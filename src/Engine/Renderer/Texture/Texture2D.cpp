//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#include "Engine/Renderer/Texture/Texture2D.h"
#include "Engine/Application.h"

namespace gp1::renderer
{
	std::unique_ptr<Texture2D> Texture2D::Create()
	{
		return Application::GetInstance()->GetRenderer()->CreateTexture2D();
	}
} // namespace gp1::renderer