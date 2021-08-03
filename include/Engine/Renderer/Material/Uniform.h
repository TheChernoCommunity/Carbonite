//
//	Created by MarcasRealAccount on 14. May. 2021
//

#pragma once

#include "Engine/Renderer/DynamicRendererData.h"
#include "Engine/Renderer/Texture/Texture2D.h"
#include "Engine/Renderer/Texture/Texture2DArray.h"
#include "Engine/Renderer/Texture/Texture3D.h"
#include "Engine/Renderer/Texture/TextureCubeMap.h"

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <glm.hpp>

namespace gp1::renderer
{
	enum class EUniformType : uint32_t
	{
		Float,
		FVec2,
		FVec3,
		FVec4,
		Int,
		IVec2,
		IVec3,
		IVec4,
		UInt,
		UVec2,
		UVec3,
		UVec4,
		FMat2,
		FMat3,
		FMat4,
		Texture2D,
		Texture2DArray,
		Texture3D,
		TextureCubeMap
	};

	struct Uniform : public DynamicRendererData
	{
	public:
		friend struct UniformBuffer;

		static std::unique_ptr<Uniform> Create(EUniformType type);

	public:
		virtual ~Uniform() = default;

		bool IsOfSameType(const Uniform* other) const;

		virtual EUniformType GetType() const                = 0;
		virtual void         CopyFrom(const Uniform* other) = 0;

	protected:
		Uniform() = default;
	};

	struct UniformFloat : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::Float;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void  SetValue(float value);
		float GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformFloat() = default;

	protected:
		float m_Value = 0.0f;
	};

	struct UniformFVec2 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::FVec2;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void              SetValue(const glm::fvec2& value);
		const glm::fvec2& GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformFVec2() = default;

	protected:
		glm::fvec2 m_Value = { 0.0f, 0.0f };
	};

	struct UniformFVec3 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::FVec3;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void              SetValue(const glm::fvec3& value);
		const glm::fvec3& GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformFVec3() = default;

	protected:
		glm::fvec3 m_Value = { 0.0f, 0.0f, 0.0f };
	};

	struct UniformFVec4 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::FVec4;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void              SetValue(const glm::fvec4& value);
		const glm::fvec4& GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformFVec4() = default;

	protected:
		glm::fvec4 m_Value = { 0.0f, 0.0f, 0.0f, 0.0f };
	};

	struct UniformInt : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::Int;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void    SetValue(int32_t value);
		int32_t GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformInt() = default;

	protected:
		int32_t m_Value = 0;
	};

	struct UniformIVec2 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::IVec2;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void              SetValue(const glm::ivec2& value);
		const glm::ivec2& GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformIVec2() = default;

	protected:
		glm::ivec2 m_Value = { 0, 0 };
	};

	struct UniformIVec3 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::IVec3;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void              SetValue(const glm::ivec3& value);
		const glm::ivec3& GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformIVec3() = default;

	protected:
		glm::ivec3 m_Value = { 0, 0, 0 };
	};

	struct UniformIVec4 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::IVec4;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void              SetValue(const glm::ivec4& value);
		const glm::ivec4& GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformIVec4() = default;

	protected:
		glm::ivec4 m_Value = { 0, 0, 0, 0 };
	};

	struct UniformUInt : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::UInt;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void     SetValue(uint32_t value);
		uint32_t GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformUInt() = default;

	protected:
		uint32_t m_Value = 0;
	};

	struct UniformUVec2 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::UVec2;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void              SetValue(const glm::uvec2& value);
		const glm::uvec2& GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformUVec2() = default;

	protected:
		glm::uvec2 m_Value = { 0, 0 };
	};

	struct UniformUVec3 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::UVec3;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void              SetValue(const glm::uvec3& value);
		const glm::uvec3& GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformUVec3() = default;

	protected:
		glm::uvec3 m_Value = { 0, 0, 0 };
	};

	struct UniformUVec4 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::UVec4;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void              SetValue(const glm::uvec4& value);
		const glm::uvec4& GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformUVec4() = default;

	protected:
		glm::uvec4 m_Value = { 0, 0, 0, 0 };
	};

	struct UniformFMat2 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::FMat2;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void              SetValue(const glm::fmat2& value);
		const glm::fmat2& GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformFMat2() = default;

	protected:
		glm::fmat2 m_Value = { 1.0f, 0.0f, 0.0f, 1.0f };
	};

	struct UniformFMat3 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::FMat3;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void              SetValue(const glm::fmat3& value);
		const glm::fmat3& GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformFMat3() = default;

	protected:
		glm::fmat3 m_Value = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	};

	struct UniformFMat4 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::FMat4;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void              SetValue(const glm::fmat4& value);
		const glm::fmat4& GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformFMat4() = default;

	protected:
		glm::fmat4 m_Value = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	};

	struct UniformTexture2D : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::Texture2D;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void       SetValue(Texture2D* value);
		Texture2D* GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformTexture2D() = default;

	protected:
		Texture2D* m_Value = nullptr;
	};

	struct UniformTexture2DArray : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::Texture2DArray;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void            SetValue(Texture2DArray* value);
		Texture2DArray* GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformTexture2DArray() = default;

	protected:
		Texture2DArray* m_Value = nullptr;
	};

	struct UniformTexture3D : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::Texture3D;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void       SetValue(Texture3D* value);
		Texture3D* GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformTexture3D() = default;

	protected:
		Texture3D* m_Value = nullptr;
	};

	struct UniformTextureCubeMap : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::TextureCubeMap;
		}

		virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual void CopyFrom(const Uniform* other) override;

		void            SetValue(TextureCubeMap* value);
		TextureCubeMap* GetValue() const
		{
			return m_Value;
		}

	protected:
		UniformTextureCubeMap() = default;

	protected:
		TextureCubeMap* m_Value = nullptr;
	};
} // namespace gp1::renderer