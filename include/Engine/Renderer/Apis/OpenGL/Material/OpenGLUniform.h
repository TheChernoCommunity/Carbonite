//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Material/Uniform.h"

namespace gp1::renderer::opengl
{
	struct OpenGLUniform
	{
	public:
		friend struct OpenGLUniformBuffer;

		static bool IsTextureType(EUniformType type);

	public:
		virtual ~OpenGLUniform() = default;

		virtual size_t GetDataSize() const                       = 0;
		virtual void   PutData(std::vector<uint8_t>& data) const = 0;

		virtual bool IsTexture()
		{
			return false;
		}

		void* GetNext() const
		{
			return m_Next;
		}

		template <typename T>
		T* GetNext() const
		{
			return reinterpret_cast<T*>(m_Next);
		}

	protected:
		OpenGLUniform() = default;

	protected:
		uint32_t m_Offset = 0;
		void*    m_Next   = nullptr;
	};

	struct OpenGLUniformFloat : public UniformFloat, public OpenGLUniform
	{
	public:
		OpenGLUniformFloat();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformFVec2 : public UniformFVec2, public OpenGLUniform
	{
	public:
		OpenGLUniformFVec2();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformFVec3 : public UniformFVec3, public OpenGLUniform
	{
	public:
		OpenGLUniformFVec3();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformFVec4 : public UniformFVec4, public OpenGLUniform
	{
		OpenGLUniformFVec4();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformInt : public UniformInt, public OpenGLUniform
	{
	public:
		OpenGLUniformInt();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformIVec2 : public UniformIVec2, public OpenGLUniform
	{
	public:
		OpenGLUniformIVec2();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformIVec3 : public UniformIVec3, public OpenGLUniform
	{
		OpenGLUniformIVec3();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformIVec4 : public UniformIVec4, public OpenGLUniform
	{
	public:
		OpenGLUniformIVec4();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformUInt : public UniformUInt, public OpenGLUniform
	{
	public:
		OpenGLUniformUInt();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformUVec2 : public UniformUVec2, public OpenGLUniform
	{
	public:
		OpenGLUniformUVec2();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformUVec3 : public UniformUVec3, public OpenGLUniform
	{
	public:
		OpenGLUniformUVec3();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformUVec4 : public UniformUVec4, public OpenGLUniform
	{
	public:
		OpenGLUniformUVec4();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformFMat2 : public UniformFMat2, public OpenGLUniform
	{
	public:
		OpenGLUniformFMat2();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformFMat3 : public UniformFMat3, public OpenGLUniform
	{
	public:
		OpenGLUniformFMat3();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformFMat4 : public UniformFMat4, public OpenGLUniform
	{
	public:
		OpenGLUniformFMat4();

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data) const override;
	};

	struct OpenGLUniformTexture
	{
	public:
		virtual ~OpenGLUniformTexture() = default;

		virtual void Bind() = 0;

	protected:
		OpenGLUniformTexture() = default;
	};

	struct OpenGLUniformTexture2D : public UniformTexture2D, public OpenGLUniform, public OpenGLUniformTexture
	{
	public:
		OpenGLUniformTexture2D();

		virtual void   Update() override;
		virtual bool IsUpdatable() const override
		{
			return true;
		}

		virtual size_t GetDataSize() const override
		{
			return 0;
		}
		virtual void PutData([[maybe_unused]] std::vector<uint8_t>& data) const override {}

		virtual bool IsTexture()
		{
			return true;
		}

		virtual void Bind() override;
	};

	struct OpenGLUniformTexture2DArray : public UniformTexture2DArray, public OpenGLUniform, public OpenGLUniformTexture
	{
	public:
		OpenGLUniformTexture2DArray();

		virtual void   Update() override;
		virtual bool IsUpdatable() const override
		{
			return true;
		}

		virtual size_t GetDataSize() const override
		{
			return 0;
		}
		virtual void PutData([[maybe_unused]] std::vector<uint8_t>& data) const override {}

		virtual bool IsTexture()
		{
			return true;
		}

		virtual void Bind() override;
	};

	struct OpenGLUniformTexture3D : public UniformTexture3D, public OpenGLUniform, public OpenGLUniformTexture
	{
	public:
		OpenGLUniformTexture3D();

		virtual void   Update() override;
		virtual bool IsUpdatable() const override
		{
			return true;
		}

		virtual size_t GetDataSize() const override
		{
			return 0;
		}
		virtual void PutData([[maybe_unused]] std::vector<uint8_t>& data) const override {}

		virtual bool IsTexture()
		{
			return true;
		}

		virtual void Bind() override;
	};

	struct OpenGLUniformTextureCubeMap : public UniformTextureCubeMap, public OpenGLUniform, public OpenGLUniformTexture
	{
	public:
		OpenGLUniformTextureCubeMap();

		virtual void   Update() override;
		virtual bool IsUpdatable() const override
		{
			return true;
		}

		virtual size_t GetDataSize() const override
		{
			return 0;
		}
		virtual void PutData([[maybe_unused]] std::vector<uint8_t>& data) const override {}

		virtual bool IsTexture()
		{
			return true;
		}

		virtual void Bind() override;
	};
} // namespace gp1::renderer::opengl
#endif