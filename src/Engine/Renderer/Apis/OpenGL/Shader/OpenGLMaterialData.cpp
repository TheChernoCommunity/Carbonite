//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#include "Engine/Renderer/Apis/OpenGL/Shader/OpenGLMaterialData.h"
#include "Engine/Renderer/Shader/Shader.h"

namespace gp1 {

	OpenGLMaterialData::OpenGLMaterialData(Material* material)
		: MaterialData(material) {}

	void OpenGLMaterialData::CleanUp() {}

	RendererType OpenGLMaterialData::GetRendererType() const {
		return RendererType::OPENGL;
	}

	GLenum OpenGLMaterialData::GetCullFace() const {
		return GetGLCullFace(GetMaterial<Material>()->m_CullMode.m_Face);
	}

	GLenum OpenGLMaterialData::GetSrcBlendFunc() const {
		return GetGLBlendFunc(GetMaterial<Material>()->m_BlendFunc.m_SrcFunc);
	}

	GLenum OpenGLMaterialData::GetDstBlendFunc() const {
		return GetGLBlendFunc(GetMaterial<Material>()->m_BlendFunc.m_DstFunc);
	}

	GLenum OpenGLMaterialData::GetPolygonModeFace() const {
		return GetGLCullFace(GetMaterial<Material>()->m_PolygonMode.m_Face);
	}

	GLenum OpenGLMaterialData::GetPolygonMode() const {
		return GetGLPolygonMode(GetMaterial<Material>()->m_PolygonMode.m_Mode);
	}

	void OpenGLMaterialData::SetAllUniforms() {
		if (!GetMaterial<Material>()->GetShader())
			return;

		for (auto& uniform : GetUniforms()) {
			const std::string& id = uniform.first;
			uint32_t location = GetMaterial<Material>()->GetShader()->GetUniformLocation(id);
			if (uniform.second.type() == typeid(Uniform<float>)) {
				const Uniform<float>* uniformFloat = std::any_cast<Uniform<float>>(&uniform.second);
				glUniform1f(location, uniformFloat->m_Value);
			} else if (uniform.second.type() == typeid(Uniform<Vec2f>)) {
				const Uniform<Vec2f>* uniformVec2f = std::any_cast<Uniform<Vec2f>>(&uniform.second);
				glUniform2f(location, uniformVec2f->m_Value.x, uniformVec2f->m_Value.y);
			} else if (uniform.second.type() == typeid(Uniform<Vec3f>)) {
				const Uniform<Vec3f>* uniformVec3f = std::any_cast<Uniform<Vec3f>>(&uniform.second);
				glUniform3f(location, uniformVec3f->m_Value.x, uniformVec3f->m_Value.y, uniformVec3f->m_Value.z);
			} else if (uniform.second.type() == typeid(Uniform<Vec4f>)) {
				const Uniform<Vec4f>* uniformVec4f = std::any_cast<Uniform<Vec4f>>(&uniform.second);
				glUniform4f(location, uniformVec4f->m_Value.x, uniformVec4f->m_Value.y, uniformVec4f->m_Value.z, uniformVec4f->m_Value.w);
			} else if (uniform.second.type() == typeid(Uniform<int32_t>)) {
				const Uniform<int32_t>* uniformInt = std::any_cast<Uniform<int32_t>>(&uniform.second);
				glUniform1i(location, uniformInt->m_Value);
			} else if (uniform.second.type() == typeid(Uniform<Vec2f>)) {
				const Uniform<Vec2i>* uniformVec2i = std::any_cast<Uniform<Vec2i>>(&uniform.second);
				glUniform2i(location, uniformVec2i->m_Value.x, uniformVec2i->m_Value.y);
			} else if (uniform.second.type() == typeid(Uniform<Vec3f>)) {
				const Uniform<Vec3i>* uniformVec3i = std::any_cast<Uniform<Vec3i>>(&uniform.second);
				glUniform3i(location, uniformVec3i->m_Value.x, uniformVec3i->m_Value.y, uniformVec3i->m_Value.z);
			} else if (uniform.second.type() == typeid(Uniform<Vec4f>)) {
				const Uniform<Vec4i>* uniformVec4i = std::any_cast<Uniform<Vec4i>>(&uniform.second);
				glUniform4i(location, uniformVec4i->m_Value.x, uniformVec4i->m_Value.y, uniformVec4i->m_Value.z, uniformVec4i->m_Value.w);
			} else if (uniform.second.type() == typeid(Uniform<uint32_t>)) {
				const Uniform<uint32_t>* uniformInt = std::any_cast<Uniform<uint32_t>>(&uniform.second);
				glUniform1ui(location, uniformInt->m_Value);
			} else if (uniform.second.type() == typeid(Uniform<Vec2f>)) {
				const Uniform<Vec2u>* uniformVec2u = std::any_cast<Uniform<Vec2u>>(&uniform.second);
				glUniform2ui(location, uniformVec2u->m_Value.x, uniformVec2u->m_Value.y);
			} else if (uniform.second.type() == typeid(Uniform<Vec3f>)) {
				const Uniform<Vec3u>* uniformVec3u = std::any_cast<Uniform<Vec3u>>(&uniform.second);
				glUniform3ui(location, uniformVec3u->m_Value.x, uniformVec3u->m_Value.y, uniformVec3u->m_Value.z);
			} else if (uniform.second.type() == typeid(Uniform<Vec4f>)) {
				const Uniform<Vec4u>* uniformVec4u = std::any_cast<Uniform<Vec4u>>(&uniform.second);
				glUniform4ui(location, uniformVec4u->m_Value.x, uniformVec4u->m_Value.y, uniformVec4u->m_Value.z, uniformVec4u->m_Value.w);
			} else if (uniform.second.type() == typeid(Uniform<Mat2f>)) {
				const Uniform<Mat2f>* uniformMat2f = std::any_cast<Uniform<Mat2f>>(&uniform.second);
				glUniformMatrix2fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&uniformMat2f->m_Value));
			} else if (uniform.second.type() == typeid(Uniform<Mat3f>)) {
				const Uniform<Mat3f>* uniformMat3f = std::any_cast<Uniform<Mat3f>>(&uniform.second);
				glUniformMatrix3fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&uniformMat3f->m_Value));
			} else if (uniform.second.type() == typeid(Uniform<Mat4f>)) {
				const Uniform<Mat4f>* uniformMat4f = std::any_cast<Uniform<Mat4f>>(&uniform.second);
				glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&uniformMat4f->m_Value));
			}
		}
	}

	GLenum OpenGLMaterialData::GetGLCullFace(TriangleFace face) {
		switch (face) {
		case TriangleFace::BACK:
			return GL_BACK;
		case TriangleFace::FRONT:
			return GL_FRONT;
		case TriangleFace::FRONT_AND_BACK:
			return GL_FRONT_AND_BACK;
		default:
			return GL_BACK;
		}
	}

	GLenum OpenGLMaterialData::GetGLBlendFunc(BlendFunc blendFunc) {
		switch (blendFunc) {
		case BlendFunc::ZERO:
			return GL_ZERO;
		case BlendFunc::ONE:
			return GL_ONE;
		case BlendFunc::SRC_COLOR:
			return GL_SRC_COLOR;
		case BlendFunc::ONE_MINUS_SRC_COLOR:
			return GL_ONE_MINUS_SRC_COLOR;
		case BlendFunc::DST_COLOR:
			return GL_DST_COLOR;
		case BlendFunc::ONE_MINUS_DST_COLOR:
			return GL_ONE_MINUS_DST_COLOR;
		case BlendFunc::SRC_ALPHA:
			return GL_SRC_ALPHA;
		case BlendFunc::ONE_MINUS_SRC_ALPHA:
			return GL_ONE_MINUS_SRC_ALPHA;
		case BlendFunc::DST_ALPHA:
			return GL_DST_ALPHA;
		case BlendFunc::ONE_MINUS_DST_ALPHA:
			return GL_ONE_MINUS_DST_ALPHA;
		case BlendFunc::CONSTANT_COLOR:
			return GL_CONSTANT_COLOR;
		case BlendFunc::ONE_MINUS_CONSTANT_COLOR:
			return GL_ONE_MINUS_CONSTANT_COLOR;
		case BlendFunc::CONSTANT_ALPHA:
			return GL_CONSTANT_ALPHA;
		case BlendFunc::ONE_MINUS_CONSTANT_ALPHA:
			return GL_ONE_MINUS_CONSTANT_ALPHA;
		case BlendFunc::SRC_ALPHA_SATURATE:
			return GL_SRC_ALPHA_SATURATE;
		case BlendFunc::SRC1_COLOR:
			return GL_SRC1_COLOR;
		case BlendFunc::ONE_MINUS_SRC1_COLOR:
			return GL_ONE_MINUS_SRC1_COLOR;
		case BlendFunc::SRC1_ALPHA:
			return GL_SRC1_ALPHA;
		case BlendFunc::ONE_MINUS_SRC1_ALPHA:
			return GL_ONE_MINUS_SRC1_ALPHA;
		default:
			return GL_ONE;
		}
	}

	GLenum OpenGLMaterialData::GetGLPolygonMode(PolygonMode polygonMode) {
		switch (polygonMode) {
		case PolygonMode::POINT:
			return GL_POINT;
		case PolygonMode::LINE:
			return GL_LINE;
		case PolygonMode::FILL:
			return GL_FILL;
		default:
			return GL_FILL;
		}
	}

} // namespace gp1
