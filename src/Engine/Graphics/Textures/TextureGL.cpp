#include "Engine/Graphics/Textures/TextureGL.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../third_party/STBImage/stb_image.h"
#include "Engine/Utility/Logger.h"
#include "Engine/Application.h"
#include "Engine/Graphics/GraphicsLogger.h"
/*

Made by Vironacorus

*/
namespace gp1
{

	GL::Image GL::LoadImage(const char* filename)
	{
		GL::Image resultImg;
		{
			ExtentS imageExtentS;
			int cmp;
			resultImg.imageData = stbi_load(filename, &imageExtentS.width, &imageExtentS.height, &cmp, STBI_rgb_alpha);
			resultImg.imageExtent = imageExtentS;
		}
		if(!resultImg.imageData)
			graphicsLogger.LogError("Image didn't load properly or not present. GL::LoadImage::resultImg.imageData was NULL.");
		return resultImg;
	}

	void GL::UnloadImage(const GL::Image& image)
	{
		stbi_image_free(image.imageData);
	}

	void GL::TextureImage(const GL::Image& image, const Point& writePoint, GL::Type textureType)
	{
		GL::TextureImage(image, { {0,0},image.imageExtent },writePoint,textureType);
	}

	void GL::TextureImage3D(const Image& image, const Range& readRange, const Point& writePoint, GL::Type textureType)
	{
		glTexSubImage3D
		(
			textureType,
			0, writePoint.width, writePoint.height, writePoint.depth,
			readRange.rangeSize.width,
			readRange.rangeSize.height,
			1,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image.imageData + (((readRange.rangeBegin.height * image.imageExtent.width) + readRange.rangeBegin.width) * 4)
		);
	}

	void GL::TextureImage(const GL::Image& image, const GL::Range& readRange, const Point& writePoint,GL::Type textureType)
	{

		glTexSubImage2D
		(
			textureType,0,writePoint.width,writePoint.height,
			readRange.rangeSize.width,
			readRange.rangeSize.height,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image.imageData + (((readRange.rangeBegin.height*image.imageExtent.width)+ readRange.rangeBegin.width) * 4)
		);
	}

	void GL::DeleteTexture(const GL::Texture& texture)
	{
		glDeleteTextures(1,&texture.textureObject);
	}

	void GL::CopyTexture(const GL::Texture& srcTex, const GL::Texture& dstTex, const GL::Range& srcRange, const GL::Point& dstPoint)
	{
		glCopyImageSubData
		(
			srcTex.textureObject, srcTex.textureType,0,
			srcRange.rangeBegin.width,
			srcRange.rangeBegin.height,
			srcRange.rangeBegin.depth,
			dstTex.textureObject,dstTex.textureType,0,
			dstPoint.width,
			dstPoint.height,
			dstPoint.depth,
			srcRange.rangeSize.width,
			srcRange.rangeSize.height,
			srcRange.rangeSize.depth
		);
	}

	void GL::SetActiveTexture(uint32_t slot)
	{
		glActiveTexture(GL_TEXTURE0+slot);
	}

	GL::Texture GL::Texture2DCreate(const GL::Extent& textureSize,GL::Type textureFormat)
	{
		GL::Texture resultTexture;
		resultTexture.textureType = GL_TEXTURE_2D;
		glGenTextures(1,&resultTexture.textureObject);
		glBindTexture(GL_TEXTURE_2D,resultTexture.textureObject);
		glTextureStorage2D(resultTexture.textureObject, 1, textureFormat, textureSize.width, textureSize.height);
		return resultTexture;
	}

	GL::Texture GL::TextureArray2DCreate(const GL::Extent& textureSize, GL::Type textureFormat)
	{
		GL::Texture resultTexture;
		resultTexture.textureType = GL_TEXTURE_2D_ARRAY;
		glGenTextures(1, &resultTexture.textureObject);
		glBindTexture(GL_TEXTURE_2D_ARRAY, resultTexture.textureObject);
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, textureFormat, textureSize.width, textureSize.height,textureSize.depth);
		return resultTexture;
	}

	GL::Texture GL::Texture3DCreate(const GL::Extent& textureSize, GL::Type textureFormat)
	{
		GL::Texture resultTexture;
		resultTexture.textureType = GL_TEXTURE_3D;
		glGenTextures(1, &resultTexture.textureObject);
		glBindTexture(GL_TEXTURE_3D, resultTexture.textureObject);
		glTexStorage3D(GL_TEXTURE_3D, 1, textureFormat, textureSize.width, textureSize.height, textureSize.depth);
		return resultTexture;
	}

	GL::Texture GL::TextureCubeCreate(const GL::Extent& textureSize, GL::Type textureFormat)
	{
		GL::Texture resultTexture;
		resultTexture.textureType = GL_TEXTURE_CUBE_MAP;
		glGenTextures(1, &resultTexture.textureObject);
		glBindTexture(GL_TEXTURE_CUBE_MAP,resultTexture.textureObject);
		//TODO: Check if it actually works
		glTexStorage3D(GL_TEXTURE_CUBE_MAP, 1, textureFormat, textureSize.width, textureSize.height, 6);
		return resultTexture;
	}


#ifdef _DEBUG
	uint32_t slotUsed[32]{};

	void GL::BindTexture(const GL::Texture& texture, uint32_t slot)
	{
		if(slotUsed[slot] == texture.textureObject)
			graphicsLogger.LogWarning("Texture %x is already bound to slot %i.", texture.textureObject,slot);
		else if (slotUsed[slot] /* != 0*/)
			graphicsLogger.LogWarning("Slot %i already used by texture %x. Did you forget to UnbindTexture(...)?", slot, slotUsed[slot]);

		slotUsed[slot] = texture.textureObject;
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(texture.textureType, texture.textureObject);
	}

	void GL::UnbindTexture(uint32_t slot)
	{
		if(!slotUsed[slot])
			graphicsLogger.LogWarning("Slot %i is unused and you tried to unbind it. Did you forget to BindTexture(...)?", slot);
		slotUsed[slot] = 0;

		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D,0);
	}
#else

	void GL::BindTexture(const GL::Texture& texture, uint32_t slot)
	{
		glActiveTexture(GL_TEXTURE0+slot);
		glBindTexture(GL_TEXTURE_2D,texture.textureObject);
	}
	void GL::UnbindTexture(uint32_t slot) {}
#endif

	GL::ExtentS::operator GL::Extent() { return { (uint32_t)width,(uint32_t)height,(uint32_t)depth }; }
	GL::Extent::operator GL::ExtentS() { return { (int32_t)width,(int32_t)height,(int32_t)depth }; }
	GL::Texture::operator GL::Obj() { return textureObject; }
}
