//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#pragma once

#include <string>

namespace gp1::renderer
{
	namespace texture
	{
		struct Texture2D;
	}

	namespace textureLoaders
	{
		enum class TextureLoadMode
		{
			NORMAL,
			HDR,
			BPC16
		};

		// Load a 2D texture from the given file in the given mode.
		texture::Texture2D* LoadTexture2D(std::string file, TextureLoadMode mode = TextureLoadMode::NORMAL);

	} // namespace textureLoaders

} // namespace gp1::renderer
