//
//	Created by MarcasRealAccount on 14. May. 2021
//

#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <string>
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
		FMat4
	};

	struct Uniform
	{
	public:
		static std::shared_ptr<Uniform> CreateUniform(EUniformType type);

	public:
		virtual ~Uniform() = default;

		bool IsOfSameType(const std::shared_ptr<Uniform>& other) const;

		virtual EUniformType GetType() const                                          = 0;
		virtual size_t       GetDataSize() const                                      = 0;
		virtual void         PutData(std::vector<uint8_t>& data, size_t offset) const = 0;
		virtual void         CopyFrom(const std::shared_ptr<Uniform>& other)          = 0;

		inline bool IsDirty() const
		{
			return m_Dirty;
		}

	public:
		bool m_Dirty = true;
	};

	struct UniformBuffer
	{
	public:
		struct UniformInfo
		{
		public:
			UniformInfo(EUniformType type);

		public:
			std::shared_ptr<Uniform> m_Uniform;
			uint32_t                 m_Offset = 0;
		};

		using UniformMap = std::map<std::string, UniformInfo>;

		using Iterator             = UniformMap::iterator;
		using ConstIterator        = UniformMap::const_iterator;
		using ReverseIterator      = UniformMap::reverse_iterator;
		using ConstReverseIterator = UniformMap::const_reverse_iterator;

	public:
		UniformBuffer(const std::string& name, const std::vector<std::pair<std::string, UniformInfo>>& uniforms);

		bool IsDirty() const;

		inline const std::string& GetName() const
		{
			return m_Name;
		}

		template <typename T, std::enable_if_t<std::is_base_of_v<Uniform, T>, bool> = true>
		std::shared_ptr<T> GetUniform(const std::string& name) const
		{
			return std::static_pointer_cast<T>(GetUniform(name));
		}

		std::shared_ptr<Uniform> GetUniform(const std::string& name) const;
		void                     GetUniformData(std::vector<uint8_t>& data) const;

		inline Iterator begin()
		{
			return m_Uniforms.begin();
		}

		inline Iterator end()
		{
			return m_Uniforms.end();
		}

		inline ConstIterator begin() const
		{
			return m_Uniforms.begin();
		}

		inline ConstIterator end() const
		{
			return m_Uniforms.end();
		}

		inline ConstIterator cbegin() const
		{
			return m_Uniforms.cbegin();
		}

		inline ConstIterator cend() const
		{
			return m_Uniforms.cend();
		}

		inline ReverseIterator rbegin()
		{
			return m_Uniforms.rbegin();
		}

		inline ReverseIterator rend()
		{
			return m_Uniforms.rend();
		}

		inline ConstReverseIterator rbegin() const
		{
			return m_Uniforms.rbegin();
		}

		inline ConstReverseIterator rend() const
		{
			return m_Uniforms.rend();
		}

		inline ConstReverseIterator crbegin() const
		{
			return m_Uniforms.crbegin();
		}

		inline ConstReverseIterator crend() const
		{
			return m_Uniforms.crend();
		}

	private:
		std::string                        m_Name;
		std::map<std::string, UniformInfo> m_Uniforms;
	};

	struct UniformFloat : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::Float;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void         SetValue(float value);
		inline float GetValue() const
		{
			return m_Value;
		}

	private:
		float m_Value = 0.0f;
	};

	struct UniformFVec2 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::FVec2;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void                     SetValue(const glm::fvec2& value);
		inline const glm::fvec2& GetValue() const
		{
			return m_Value;
		}

	private:
		glm::fvec2 m_Value = { 0.0f, 0.0f };
	};

	struct UniformFVec3 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::FVec3;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void                     SetValue(const glm::fvec3& value);
		inline const glm::fvec3& GetValue() const
		{
			return m_Value;
		}

	private:
		glm::fvec3 m_Value = { 0.0f, 0.0f, 0.0f };
	};

	struct UniformFVec4 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::FVec4;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void                     SetValue(const glm::fvec4& value);
		inline const glm::fvec4& GetValue() const
		{
			return m_Value;
		}

	private:
		glm::fvec4 m_Value = { 0.0f, 0.0f, 0.0f, 0.0f };
	};

	struct UniformInt : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::Int;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void           SetValue(int32_t value);
		inline int32_t GetValue() const
		{
			return m_Value;
		}

	private:
		int32_t m_Value = 0;
	};

	struct UniformIVec2 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::IVec2;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void                     SetValue(const glm::ivec2& value);
		inline const glm::ivec2& GetValue() const
		{
			return m_Value;
		}

	private:
		glm::ivec2 m_Value = { 0, 0 };
	};

	struct UniformIVec3 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::IVec3;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void                     SetValue(const glm::ivec3& value);
		inline const glm::ivec3& GetValue() const
		{
			return m_Value;
		}

	private:
		glm::ivec3 m_Value = { 0, 0, 0 };
	};

	struct UniformIVec4 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::IVec4;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void                     SetValue(const glm::ivec4& value);
		inline const glm::ivec4& GetValue() const
		{
			return m_Value;
		}

	private:
		glm::ivec4 m_Value = { 0, 0, 0, 0 };
	};

	struct UniformUInt : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::UInt;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void            SetValue(uint32_t value);
		inline uint32_t GetValue() const
		{
			return m_Value;
		}

	private:
		uint32_t m_Value = 0;
	};

	struct UniformUVec2 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::UVec2;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void                     SetValue(const glm::uvec2& value);
		inline const glm::uvec2& GetValue() const
		{
			return m_Value;
		}

	private:
		glm::uvec2 m_Value = { 0, 0 };
	};

	struct UniformUVec3 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::UVec3;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void                     SetValue(const glm::uvec3& value);
		inline const glm::uvec3& GetValue() const
		{
			return m_Value;
		}

	private:
		glm::uvec3 m_Value = { 0, 0, 0 };
	};

	struct UniformUVec4 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::UVec4;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void                     SetValue(const glm::uvec4& value);
		inline const glm::uvec4& GetValue() const
		{
			return m_Value;
		}

	private:
		glm::uvec4 m_Value = { 0, 0, 0, 0 };
	};

	struct UniformFMat2 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::FMat2;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void                     SetValue(const glm::fmat2& value);
		inline const glm::fmat2& GetValue() const
		{
			return m_Value;
		}

	private:
		glm::fmat2 m_Value = { 1.0f, 0.0f, 0.0f, 1.0f };
	};

	struct UniformFMat3 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::FMat3;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void                     SetValue(const glm::fmat3& value);
		inline const glm::fmat3& GetValue() const
		{
			return m_Value;
		}

	private:
		glm::fmat3 m_Value = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	};

	struct UniformFMat4 : public Uniform
	{
	public:
		static constexpr EUniformType GetTypeS()
		{
			return EUniformType::FMat4;
		}

		inline virtual EUniformType GetType() const override
		{
			return GetTypeS();
		}

		virtual size_t GetDataSize() const override;
		virtual void   PutData(std::vector<uint8_t>& data, size_t offset) const override;
		virtual void   CopyFrom(const std::shared_ptr<Uniform>& other) override;

		void                     SetValue(const glm::fmat4& value);
		inline const glm::fmat4& GetValue() const
		{
			return m_Value;
		}

	private:
		glm::fmat4 m_Value = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	};
} // namespace gp1::renderer