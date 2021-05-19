//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#include "Engine/Renderer/Texture/Texture2DArray.h"
#include "Engine/Application.h"

namespace gp1::renderer
{
	std::shared_ptr<Texture2DArray> Texture2DArray::Create()
	{
		return Application::GetInstance()->GetRenderer()->CreateTexture2DArray();
	}
} // namespace gp1::renderer