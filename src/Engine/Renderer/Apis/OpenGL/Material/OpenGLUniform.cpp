//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Material/OpenGLUniform.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture2D.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture2DArray.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture3D.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTextureCubeMap.h"

#include <glad/glad.h>

namespace gp1::renderer::opengl
{
	bool OpenGLUniform::IsTextureType(EUniformType type)
	{
		switch (type)
		{
		case EUniformType::Texture2D:
		case EUniformType::Texture2DArray:
		case EUniformType::Texture3D:
		case EUniformType::TextureCubeMap:
			return true;
		default: return false;
		}
	}

	OpenGLUniformFloat::OpenGLUniformFloat()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformFloat::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformFloat::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformFVec2::OpenGLUniformFVec2()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformFVec2::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformFVec2::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformFVec3::OpenGLUniformFVec3()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformFVec3::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformFVec3::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformFVec4::OpenGLUniformFVec4()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformFVec4::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformFVec4::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformInt::OpenGLUniformInt()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformInt::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformInt::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformIVec2::OpenGLUniformIVec2()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformIVec2::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformIVec2::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformIVec3::OpenGLUniformIVec3()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformIVec3::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformIVec3::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformIVec4::OpenGLUniformIVec4()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformIVec4::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformIVec4::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformUInt::OpenGLUniformUInt()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformUInt::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformUInt::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformUVec2::OpenGLUniformUVec2()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformUVec2::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformUVec2::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformUVec3::OpenGLUniformUVec3()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformUVec3::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformUVec3::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformUVec4::OpenGLUniformUVec4()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformUVec4::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformUVec4::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformFMat2::OpenGLUniformFMat2()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformFMat2::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformFMat2::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformFMat3::OpenGLUniformFMat3()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformFMat3::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformFMat3::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformFMat4::OpenGLUniformFMat4()
	{
		RendererData::m_Next = static_cast<OpenGLUniform*>(this);
	}

	size_t OpenGLUniformFMat4::GetDataSize() const
	{
		return sizeof(m_Value);
	}

	void OpenGLUniformFMat4::PutData(std::vector<uint8_t>& data) const
	{
		const uint8_t* pValue = reinterpret_cast<const uint8_t*>(&m_Value);
		for (size_t i = 0; i < sizeof(m_Value); i++)
			data[m_Offset + i] = pValue[i];
	}

	OpenGLUniformTexture2D::OpenGLUniformTexture2D()
	{
		RendererData::m_Next  = static_cast<OpenGLUniform*>(this);
		OpenGLUniform::m_Next = static_cast<OpenGLUniformTexture*>(this);
	}

	void OpenGLUniformTexture2D::Update()
	{
		UniformTexture2D::Update();

		std::reinterpret_pointer_cast<OpenGLTexture2D>(m_Value)->Update();
	}

	void OpenGLUniformTexture2D::Bind()
	{
		if (m_Value)
		{
			glActiveTexture(GL_TEXTURE0 + m_Offset);
			glBindTexture(GL_TEXTURE_2D, std::reinterpret_pointer_cast<OpenGLTexture2D>(m_Value)->m_TextureId);
		}
		else
		{
			glActiveTexture(GL_TEXTURE0 + m_Offset);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	OpenGLUniformTexture2DArray::OpenGLUniformTexture2DArray()
	{
		RendererData::m_Next  = static_cast<OpenGLUniform*>(this);
		OpenGLUniform::m_Next = static_cast<OpenGLUniformTexture*>(this);
	}

	void OpenGLUniformTexture2DArray::Update()
	{
		UniformTexture2DArray::Update();

		std::reinterpret_pointer_cast<OpenGLTexture2DArray>(m_Value)->Update();
	}

	void OpenGLUniformTexture2DArray::Bind()
	{
		if (m_Value)
		{
			glActiveTexture(GL_TEXTURE0 + m_Offset);
			glBindTexture(GL_TEXTURE_2D_ARRAY, std::reinterpret_pointer_cast<OpenGLTexture2DArray>(m_Value)->m_TextureId);
		}
		else
		{
			glActiveTexture(GL_TEXTURE0 + m_Offset);
			glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
		}
	}

	OpenGLUniformTexture3D::OpenGLUniformTexture3D()
	{
		RendererData::m_Next  = static_cast<OpenGLUniform*>(this);
		OpenGLUniform::m_Next = static_cast<OpenGLUniformTexture*>(this);
	}

	void OpenGLUniformTexture3D::Update()
	{
		UniformTexture3D::Update();

		std::reinterpret_pointer_cast<OpenGLTexture3D>(m_Value)->Update();
	}

	void OpenGLUniformTexture3D::Bind()
	{
		if (m_Value)
		{
			glActiveTexture(GL_TEXTURE0 + m_Offset);
			glBindTexture(GL_TEXTURE_3D, std::reinterpret_pointer_cast<OpenGLTexture3D>(m_Value)->m_TextureId);
		}
		else
		{
			glActiveTexture(GL_TEXTURE0 + m_Offset);
			glBindTexture(GL_TEXTURE_3D, 0);
		}
	}

	OpenGLUniformTextureCubeMap::OpenGLUniformTextureCubeMap()
	{
		RendererData::m_Next  = static_cast<OpenGLUniform*>(this);
		OpenGLUniform::m_Next = static_cast<OpenGLUniformTexture*>(this);
	}

	void OpenGLUniformTextureCubeMap::Update()
	{
		UniformTextureCubeMap::Update();

		std::reinterpret_pointer_cast<OpenGLTextureCubeMap>(m_Value)->Update();
	}

	void OpenGLUniformTextureCubeMap::Bind()
	{
		if (m_Value)
		{
			glActiveTexture(GL_TEXTURE0 + m_Offset);
			glBindTexture(GL_TEXTURE_CUBE_MAP, std::reinterpret_pointer_cast<OpenGLTextureCubeMap>(m_Value)->m_TextureId);
		}
		else
		{
			glActiveTexture(GL_TEXTURE0 + m_Offset);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
	}
} // namespace gp1::renderer::opengl
#endif