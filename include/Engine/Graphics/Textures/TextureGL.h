#pragma once
#include <glad/glad.h>
#include "../third_party/STBImage/stb_image.h"
#include <stdint.h>

/*

Made by Vironacorus: 2/3 XI 2020

*/


namespace gp1
{

	namespace GL
	{
		typedef GLuint Obj;
		typedef GLenum Type;

		//image extent structs (I don't really see a reason for templating here)
		struct ExtentS;
		struct Extent;
		struct Extent
		{
			uint32_t width;
			uint32_t height;
			uint32_t depth;

			operator ExtentS();
		};

		struct ExtentS
		{
			int32_t width;
			int32_t height;
			int32_t depth;

			operator Extent();
		};

		typedef Extent Point;
		typedef ExtentS PointS;

		//range within an image

		struct Range
		{

			//upper left corner
			Point rangeBegin;
			//size of range
			Extent rangeSize;
		};


		//data acquired from file
		struct Image
		{
			uint8_t* imageData;
			Extent imageExtent;
		};

		//struct, that represents OpenGL texture object
		struct Texture
		{
			GL::Obj textureObject;
			GL::Type textureType;
			operator GL::Obj();
		};

		[[nodiscard]] Image LoadImage(const char* filename);
		void UnloadImage(const Image& image);

		void TextureImage(const Image& image, const Range& readRange, const Point& writePoint = {0,0}, GL::Type textureType = GL_TEXTURE_2D);
		void TextureImage(const Image& image, const Point& writePoint = { 0,0 }, GL::Type textureType = GL_TEXTURE_2D);
		void TextureImage3D(const Image& image, const Range& readRange, const Point& writePoint = { 0,0,0 }, GL::Type textureType = GL_TEXTURE_3D);
		inline  void TextureArray2DImage(const Image& image, const Range& readRange, const Point& writePoint = { 0,0,0 }){ TextureImage3D(image, readRange,writePoint,GL_TEXTURE_2D_ARRAY);}

		[[nodiscard]] Texture TextureCubeCreate(const Extent& textureSize, Type textureFormat = GL_RGBA32F);
		[[nodiscard]] Texture Texture2DCreate(const Extent& textureSize, Type textureFormat = GL_RGBA32F);
		[[nodiscard]] Texture TextureArray2DCreate(const Extent& textureSize, Type textureFormat = GL_RGBA32F);
		[[nodiscard]] Texture Texture3DCreate(const Extent& textureSize, Type textureFormat = GL_RGBA32F);


		void CopyTexture(const Texture& srcTex, const Texture& dstTex, const Range& srcRange, const Point& dstPoint = {0,0,0});
		void SetActiveTexture(uint32_t slot);
		void BindTexture(const Texture& texture,uint32_t slot);
		void UnbindTexture(uint32_t slot);
		void DeleteTexture(const Texture& texture);

		/*
			Loading single texture:


			//Load image to RAM
			Image img = LoadImage("file.txt");
			//Create a 2D texture of size 400x400px
			Texture tex = Texture2DCreate({400,400});
			//Bind texture to operate on it
			BindTexture(tex,0);
			//Copy image into texture
			TextureImage(img);
			//Free image memory
			UnloadImage(img);
			...
			//Destroy texture
			DeleteTexture(tex);
		*/

		/*

			Loading array of textures from sprite atlas:

			//Create 400x400 texture array with 5 elements
			Texture textureArray = TextureArray2DCreate({400,400,5});
			//Load sprite atlas
			Image img = LoadImage("atlas.png");

			//Bind texture to operate on it
			BindTexture(textureArray);

			for(uint32_t i = 0; i<5;++i)
			{
				//Load Image into texture array
				//We read from upper left corner of texture offset by sprite index * width
				//We write to upper left corner of textureArray[i]
				TextureArray2DImage(img,{i*400,0,0},{400,400,1}},{0,0,i});
			}

			//Cleanup image
			UnloadImage(img);

			...
			//Destroy texture array
			DeleteTexture(textureArray);
		*/

		/*

		Rendering textures is as easy as a BindTexture call (and setting up proper uniforms)

		BindTexture(myTexture,0);

		BindTexture(...) keeps track of currently used textures in debug mode and will warn you
		if you try to re-use texture slot, so remember to UnbindTexture(...) (in Release it does nothing for speed)
		*/
	}
}
