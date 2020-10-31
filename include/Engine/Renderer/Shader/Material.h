//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Renderer.h"

#include <unordered_map>
#include <any>

namespace gp1 {

	struct Mat2f {
		float m00, m01;
		float m10, m11;
	};

	struct Mat3f {
		float m00, m01, m02;
		float m10, m11, m12;
		float m20, m21, m22;
	};

	struct Mat4f {
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;
	};

	struct Vec2f {
		float x, y;
	};

	struct Vec3f {
		float x, y, z;
	};

	struct Vec4f {
		float x, y, z, w;
	};

	struct Vec2i {
		int32_t x, y;
	};

	struct Vec3i {
		int32_t x, y, z;
	};

	struct Vec4i {
		int32_t x, y, z, w;
	};

	struct Vec2u {
		uint32_t x, y;
	};

	struct Vec3u {
		uint32_t x, y, z;
	};

	struct Vec4u {
		uint32_t x, y, z, w;
	};

	class Shader;

	template <typename T>
	struct Uniform;

	enum class TriangleFace : uint32_t {
		BACK,
		FRONT,
		FRONT_AND_BACK
	};

	enum class BlendFunc : uint32_t {
		ZERO,
		ONE,
		SRC_COLOR,
		ONE_MINUS_SRC_COLOR,
		DST_COLOR,
		ONE_MINUS_DST_COLOR,
		SRC_ALPHA,
		ONE_MINUS_SRC_ALPHA,
		DST_ALPHA,
		ONE_MINUS_DST_ALPHA,
		CONSTANT_COLOR,
		ONE_MINUS_CONSTANT_COLOR,
		CONSTANT_ALPHA,
		ONE_MINUS_CONSTANT_ALPHA,
		SRC_ALPHA_SATURATE,
		SRC1_COLOR,
		ONE_MINUS_SRC1_COLOR,
		SRC1_ALPHA,
		ONE_MINUS_SRC1_ALPHA
	};

	enum class PolygonMode : uint32_t {
		POINT,
		LINE,
		FILL
	};

	class MaterialData;

	class Material {
	public:
		~Material();

		// Set the shader this material uses.
		void SetShader(Shader* shader);
		// Get the shader this material uses.
		Shader* GetShader() const;

		// Get a pointer to a uniform.
		template <typename T>
		Uniform<T>* GetUniform(const std::string& id) {
			if (!this->m_Shader)
				return nullptr;

			auto itr = this->m_Uniforms.find(id);
			if (itr != this->m_Uniforms.end())
				return std::any_cast<Uniform<T>>(&itr->second);
			return nullptr;
		}

		// Get the graphics specific material data.
		MaterialData* GetMaterialData(Renderer* renderer);

		friend MaterialData;

	private:
		virtual MaterialData* CreateCustomMaterialData(Renderer* renderer);

	public:
		struct {
			bool m_Enabled = true;						// Is face culling enabled.
			TriangleFace m_Face = TriangleFace::BACK;	// The face to cull.
		} m_CullMode;					// This mesh's cullmode.

		bool m_DepthTest = true;		// Is depth testing enabled.

		struct {
			bool m_Enabled = true;									// Is blending enabled.
			BlendFunc m_SrcFunc = BlendFunc::SRC_ALPHA;				// The blend function's source function.
			BlendFunc m_DstFunc = BlendFunc::ONE_MINUS_SRC_ALPHA;	// The blend function's destination function.
		} m_BlendFunc;					// The mesh's blend function.

		struct {
			bool m_Enabled = true;									// Is polygon mode enabled.
			TriangleFace m_Face = TriangleFace::FRONT_AND_BACK;		// The face to render with this mode.
			PolygonMode m_Mode = PolygonMode::FILL;					// The polygon mode.
		} m_PolygonMode;				// The mesh's polygon mode.

	protected:
		std::unordered_map<std::string, std::any> m_Uniforms;	// The uniforms this material has.

	private:
		Shader* m_Shader = nullptr;								// The shader this material uses.
		MaterialData* m_MaterialData = nullptr;					// The graphics specific data.
	};

	class MaterialData {
	public:
		MaterialData(Material* material);
		virtual ~MaterialData();

		virtual void CleanUp() = 0;

		virtual RendererType GetRendererType() const = 0;

		friend Renderer;

	protected:
		template <typename T>
		T* GetMaterial() const {
			return reinterpret_cast<T*>(this->m_Material);
		}

		const std::unordered_map<std::string, std::any>& GetUniforms() const;

	private:
		Material* m_Material;
	};

} // namespace gp1
