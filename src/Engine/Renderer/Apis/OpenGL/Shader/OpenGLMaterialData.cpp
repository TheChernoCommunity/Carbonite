//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLMaterialData.h"
#include "Engine/Renderer/Apis/OpenGL/OpenGLRenderer.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture2DArrayData.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture2DData.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture3DData.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTextureCubeMapData.h"
#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Renderer/Texture/Texture2D.h"

#include <glm.hpp>

namespace gp1::renderer::apis::opengl::shader
{
	OpenGLMaterialData::OpenGLMaterialData(renderer::shader::Material* material)
	    : OpenGLRendererData(material) {}

	void OpenGLMaterialData::CleanUp() {}

	GLenum OpenGLMaterialData::GetCullFace() const
	{
		return GetGLCullFace(GetDataUnsafe<renderer::shader::Material>()->m_CullMode.m_Face);
	}

	GLenum OpenGLMaterialData::GetSrcBlendFunc() const
	{
		return GetGLBlendFunc(GetDataUnsafe<renderer::shader::Material>()->m_BlendFunc.m_SrcFunc);
	}

	GLenum OpenGLMaterialData::GetDstBlendFunc() const
	{
		return GetGLBlendFunc(GetDataUnsafe<renderer::shader::Material>()->m_BlendFunc.m_DstFunc);
	}

	GLenum OpenGLMaterialData::GetPolygonModeFace() const
	{
		return GetGLCullFace(GetDataUnsafe<renderer::shader::Material>()->m_PolygonMode.m_Face);
	}

	GLenum OpenGLMaterialData::GetPolygonMode() const
	{
		return GetGLPolygonMode(GetDataUnsafe<renderer::shader::Material>()->m_PolygonMode.m_Mode);
	}

	void OpenGLMaterialData::SetAllUniforms(OpenGLRenderer* renderer)
	{
		renderer::shader::Material* material = GetDataUnsafe<renderer::shader::Material>();
		if (!material) return;
		if (!material->GetShader()) return;

		uint32_t texIndex = 0;
		for (auto& uniform : material->GetUniforms())
		{
			using namespace renderer::shader;

			const std::string& id       = uniform.first;
			uint32_t           location = material->GetShader()->GetUniformLocation(id);
			if (uniform.second.type() == typeid(Uniform<float>))
			{
				const Uniform<float>* uniformFloat = std::any_cast<Uniform<float>>(&uniform.second);
				glUniform1f(location, uniformFloat->m_Value);
			}
			else if (uniform.second.type() == typeid(Uniform<glm::fvec2>))
			{
				const Uniform<glm::fvec2>* uniformVec2f = std::any_cast<Uniform<glm::fvec2>>(&uniform.second);
				glUniform2f(location, uniformVec2f->m_Value.x, uniformVec2f->m_Value.y);
			}
			else if (uniform.second.type() == typeid(Uniform<glm::fvec3>))
			{
				const Uniform<glm::fvec3>* uniformVec3f = std::any_cast<Uniform<glm::fvec3>>(&uniform.second);
				glUniform3f(location, uniformVec3f->m_Value.x, uniformVec3f->m_Value.y, uniformVec3f->m_Value.z);
			}
			else if (uniform.second.type() == typeid(Uniform<glm::fvec4>))
			{
				const Uniform<glm::fvec4>* uniformVec4f = std::any_cast<Uniform<glm::fvec4>>(&uniform.second);
				glUniform4f(location, uniformVec4f->m_Value.x, uniformVec4f->m_Value.y, uniformVec4f->m_Value.z, uniformVec4f->m_Value.w);
			}
			else if (uniform.second.type() == typeid(Uniform<int32_t>))
			{
				const Uniform<int32_t>* uniformInt = std::any_cast<Uniform<int32_t>>(&uniform.second);
				glUniform1i(location, uniformInt->m_Value);
			}
			else if (uniform.second.type() == typeid(Uniform<glm::ivec2>))
			{
				const Uniform<glm::ivec2>* uniformVec2i = std::any_cast<Uniform<glm::ivec2>>(&uniform.second);
				glUniform2i(location, uniformVec2i->m_Value.x, uniformVec2i->m_Value.y);
			}
			else if (uniform.second.type() == typeid(Uniform<glm::ivec3>))
			{
				const Uniform<glm::ivec3>* uniformVec3i = std::any_cast<Uniform<glm::ivec3>>(&uniform.second);
				glUniform3i(location, uniformVec3i->m_Value.x, uniformVec3i->m_Value.y, uniformVec3i->m_Value.z);
			}
			else if (uniform.second.type() == typeid(Uniform<glm::ivec4>))
			{
				const Uniform<glm::ivec4>* uniformVec4i = std::any_cast<Uniform<glm::ivec4>>(&uniform.second);
				glUniform4i(location, uniformVec4i->m_Value.x, uniformVec4i->m_Value.y, uniformVec4i->m_Value.z, uniformVec4i->m_Value.w);
			}
			else if (uniform.second.type() == typeid(Uniform<uint32_t>))
			{
				const Uniform<uint32_t>* uniformInt = std::any_cast<Uniform<uint32_t>>(&uniform.second);
				glUniform1ui(location, uniformInt->m_Value);
			}
			else if (uniform.second.type() == typeid(Uniform<glm::uvec2>))
			{
				const Uniform<glm::uvec2>* uniformVec2u = std::any_cast<Uniform<glm::uvec2>>(&uniform.second);
				glUniform2ui(location, uniformVec2u->m_Value.x, uniformVec2u->m_Value.y);
			}
			else if (uniform.second.type() == typeid(Uniform<glm::uvec3>))
			{
				const Uniform<glm::uvec3>* uniformVec3u = std::any_cast<Uniform<glm::uvec3>>(&uniform.second);
				glUniform3ui(location, uniformVec3u->m_Value.x, uniformVec3u->m_Value.y, uniformVec3u->m_Value.z);
			}
			else if (uniform.second.type() == typeid(Uniform<glm::uvec4>))
			{
				const Uniform<glm::uvec4>* uniformVec4u = std::any_cast<Uniform<glm::uvec4>>(&uniform.second);
				glUniform4ui(location, uniformVec4u->m_Value.x, uniformVec4u->m_Value.y, uniformVec4u->m_Value.z, uniformVec4u->m_Value.w);
			}
			else if (uniform.second.type() == typeid(Uniform<glm::fmat2>))
			{
				const Uniform<glm::fmat2>* uniformMat2f = std::any_cast<Uniform<glm::fmat2>>(&uniform.second);
				glUniformMatrix2fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&uniformMat2f->m_Value));
			}
			else if (uniform.second.type() == typeid(Uniform<glm::fmat3>))
			{
				const Uniform<glm::fmat3>* uniformMat3f = std::any_cast<Uniform<glm::fmat3>>(&uniform.second);
				glUniformMatrix3fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&uniformMat3f->m_Value));
			}
			else if (uniform.second.type() == typeid(Uniform<glm::fmat4>))
			{
				const Uniform<glm::fmat4>* uniformMat4f = std::any_cast<Uniform<glm::fmat4>>(&uniform.second);
				glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&uniformMat4f->m_Value));
			}
			else if (uniform.second.type() == typeid(Uniform<renderer::texture::Texture2D*>))
			{
				Uniform<renderer::texture::Texture2D*>* uniformTexture2D = const_cast<Uniform<renderer::texture::Texture2D*>*>(std::any_cast<Uniform<renderer::texture::Texture2D*>>(&uniform.second));
				if (texIndex < reinterpret_cast<OpenGLRenderer*>(renderer)->GetMaxTextureUnits())
				{
					if (uniformTexture2D->m_Value)
					{
						glUniform1i(location, texIndex);
						glActiveTexture(GL_TEXTURE0 + texIndex);
						texture::OpenGLTexture2DData* texture2DData = reinterpret_cast<texture::OpenGLTexture2DData*>(uniformTexture2D->m_Value->GetRendererData<texture::OpenGLTexture2DData>(renderer));
						glBindTexture(GL_TEXTURE_2D, texture2DData->GetTextureID());
						texIndex++;
					}
					else
					{
						glUniform1i(location, texIndex);
						glActiveTexture(GL_TEXTURE0 + texIndex);
						glBindTexture(GL_TEXTURE_2D, 0);
						texIndex++;
					}
				}
			}
			else if (uniform.second.type() == typeid(Uniform<renderer::texture::Texture2DArray*>))
			{
				Uniform<renderer::texture::Texture2DArray*>* uniformTexture2DArray = const_cast<Uniform<renderer::texture::Texture2DArray*>*>(std::any_cast<Uniform<renderer::texture::Texture2DArray*>>(&uniform.second));
				if (texIndex < reinterpret_cast<OpenGLRenderer*>(renderer)->GetMaxTextureUnits())
				{
					if (uniformTexture2DArray->m_Value)
					{
						glUniform1i(location, texIndex);
						glActiveTexture(GL_TEXTURE0 + texIndex);
						texture::OpenGLTexture2DArrayData* texture2DArrayData = reinterpret_cast<texture::OpenGLTexture2DArrayData*>(uniformTexture2DArray->m_Value->GetRendererData<texture::OpenGLTexture2DArrayData>(renderer));
						glBindTexture(GL_TEXTURE_2D_ARRAY, texture2DArrayData->GetTextureID());
						texIndex++;
					}
					else
					{
						glUniform1i(location, texIndex);
						glActiveTexture(GL_TEXTURE0 + texIndex);
						glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
						texIndex++;
					}
				}
			}
			else if (uniform.second.type() == typeid(Uniform<renderer::texture::Texture3D*>))
			{
				Uniform<renderer::texture::Texture3D*>* uniformTexture3D = const_cast<Uniform<renderer::texture::Texture3D*>*>(std::any_cast<Uniform<renderer::texture::Texture3D*>>(&uniform.second));
				if (texIndex < reinterpret_cast<OpenGLRenderer*>(renderer)->GetMaxTextureUnits())
				{
					if (uniformTexture3D->m_Value)
					{
						glUniform1i(location, texIndex);
						glActiveTexture(GL_TEXTURE0 + texIndex);
						texture::OpenGLTexture3DData* texture3DData = reinterpret_cast<texture::OpenGLTexture3DData*>(uniformTexture3D->m_Value->GetRendererData<texture::OpenGLTexture3DData>(renderer));
						glBindTexture(GL_TEXTURE_3D, texture3DData->GetTextureID());
						texIndex++;
					}
					else
					{
						glUniform1i(location, texIndex);
						glActiveTexture(GL_TEXTURE0 + texIndex);
						glBindTexture(GL_TEXTURE_3D, 0);
						texIndex++;
					}
				}
			}
			else if (uniform.second.type() == typeid(Uniform<renderer::texture::TextureCubeMap*>))
			{
				Uniform<renderer::texture::TextureCubeMap*>* uniformTextureCubeMap = const_cast<Uniform<renderer::texture::TextureCubeMap*>*>(std::any_cast<Uniform<renderer::texture::TextureCubeMap*>>(&uniform.second));
				if (texIndex < reinterpret_cast<OpenGLRenderer*>(renderer)->GetMaxTextureUnits())
				{
					if (uniformTextureCubeMap->m_Value)
					{
						glUniform1i(location, texIndex);
						glActiveTexture(GL_TEXTURE0 + texIndex);
						texture::OpenGLTextureCubeMapData* textureCubeMapData = reinterpret_cast<texture::OpenGLTextureCubeMapData*>(uniformTextureCubeMap->m_Value->GetRendererData<texture::OpenGLTextureCubeMapData>(renderer));
						glBindTexture(GL_TEXTURE_CUBE_MAP, textureCubeMapData->GetTextureID());
						texIndex++;
					}
					else
					{
						glUniform1i(location, texIndex);
						glActiveTexture(GL_TEXTURE0 + texIndex);
						glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
						texIndex++;
					}
				}
			}
		}
	}

	GLenum OpenGLMaterialData::GetGLCullFace(renderer::shader::TriangleFace face)
	{
		switch (face)
		{
		case renderer::shader::TriangleFace::BACK:
			return GL_BACK;
		case renderer::shader::TriangleFace::FRONT:
			return GL_FRONT;
		case renderer::shader::TriangleFace::FRONT_AND_BACK:
			return GL_FRONT_AND_BACK;
		default:
			return GL_BACK;
		}
	}

	GLenum OpenGLMaterialData::GetGLBlendFunc(renderer::shader::BlendFunc blendFunc)
	{
		switch (blendFunc)
		{
		case renderer::shader::BlendFunc::ZERO:
			return GL_ZERO;
		case renderer::shader::BlendFunc::ONE:
			return GL_ONE;
		case renderer::shader::BlendFunc::SRC_COLOR:
			return GL_SRC_COLOR;
		case renderer::shader::BlendFunc::ONE_MINUS_SRC_COLOR:
			return GL_ONE_MINUS_SRC_COLOR;
		case renderer::shader::BlendFunc::DST_COLOR:
			return GL_DST_COLOR;
		case renderer::shader::BlendFunc::ONE_MINUS_DST_COLOR:
			return GL_ONE_MINUS_DST_COLOR;
		case renderer::shader::BlendFunc::SRC_ALPHA:
			return GL_SRC_ALPHA;
		case renderer::shader::BlendFunc::ONE_MINUS_SRC_ALPHA:
			return GL_ONE_MINUS_SRC_ALPHA;
		case renderer::shader::BlendFunc::DST_ALPHA:
			return GL_DST_ALPHA;
		case renderer::shader::BlendFunc::ONE_MINUS_DST_ALPHA:
			return GL_ONE_MINUS_DST_ALPHA;
		case renderer::shader::BlendFunc::CONSTANT_COLOR:
			return GL_CONSTANT_COLOR;
		case renderer::shader::BlendFunc::ONE_MINUS_CONSTANT_COLOR:
			return GL_ONE_MINUS_CONSTANT_COLOR;
		case renderer::shader::BlendFunc::CONSTANT_ALPHA:
			return GL_CONSTANT_ALPHA;
		case renderer::shader::BlendFunc::ONE_MINUS_CONSTANT_ALPHA:
			return GL_ONE_MINUS_CONSTANT_ALPHA;
		case renderer::shader::BlendFunc::SRC_ALPHA_SATURATE:
			return GL_SRC_ALPHA_SATURATE;
		case renderer::shader::BlendFunc::SRC1_COLOR:
			return GL_SRC1_COLOR;
		case renderer::shader::BlendFunc::ONE_MINUS_SRC1_COLOR:
			return GL_ONE_MINUS_SRC1_COLOR;
		case renderer::shader::BlendFunc::SRC1_ALPHA:
			return GL_SRC1_ALPHA;
		case renderer::shader::BlendFunc::ONE_MINUS_SRC1_ALPHA:
			return GL_ONE_MINUS_SRC1_ALPHA;
		default:
			return GL_ONE;
		}
	}

	GLenum OpenGLMaterialData::GetGLPolygonMode(renderer::shader::PolygonMode polygonMode)
	{
		switch (polygonMode)
		{
		case renderer::shader::PolygonMode::POINT:
			return GL_POINT;
		case renderer::shader::PolygonMode::LINE:
			return GL_LINE;
		case renderer::shader::PolygonMode::FILL:
			return GL_FILL;
		default:
			return GL_FILL;
		}
	}

} // namespace gp1::renderer::apis::opengl::shader
