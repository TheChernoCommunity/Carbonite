//
//	Created by MarcasRealAccount on 7. Dec. 2020.
//

#pragma once

#include "Engine/Renderer/Renderer.h"

#include <type_traits>

namespace gp1::renderer
{
	struct RendererData;

	struct Data
	{
	public:
		template <typename T>
		Data([[maybe_unused]] T* ptr)
		    : m_Type(typeid(T))
		{
		}
		virtual ~Data();

		// Get's the actual renderer data type.
		const std::type_info& GetType() const;

		// Get's the renderer data of the specified type.
		template <typename T> T* GetRendererData(Renderer* renderer);

		friend RendererData;

	private:
		const std::type_info& m_Type;                   // The actual type of Data.
		RendererData*         m_RendererData = nullptr; // The renderer data associated to this data.
	};

	struct RendererData
	{
	public:
		template <typename T>
		RendererData(T* data)
		    : m_Type(typeid(T)), m_Data(reinterpret_cast<Data*>(data))
		{
		}

		virtual ~RendererData();

		// Get the renderer type for this renderer data.
		virtual RendererType GetRendererType() const = 0;
		// Clean up this renderer data.
		virtual void CleanUp() = 0;

		friend Data;

	protected:
		// Gets the original data of the specified type only if the types are the same.
		template <typename T>
		T* GetDataSafe() const
		{
			if (typeid(T) == m_Type) return reinterpret_cast<T*>(this->m_Data);
			return nullptr;
		}

		// Gets the original data of the specified type.
		template <typename T>
		T* GetDataUnsafe() const
		{
			return reinterpret_cast<T*>(this->m_Data);
		}

	private:
		const std::type_info& m_Type; // The type of the original data.
		Data*                 m_Data; // The original data.
	};

	template <typename T>
	T* Data::GetRendererData(Renderer* renderer)
	{
		if (!this->m_RendererData || !renderer->IsRendererDataUsable(this->m_RendererData))
		{
			if (this->m_RendererData)
			{
				this->m_RendererData->CleanUp();
				delete this->m_RendererData;
			}
			this->m_RendererData = renderer->CreateRendererData(this);
		}
		return reinterpret_cast<T*>(this->m_RendererData);
	}
} // namespace gp1::renderer
