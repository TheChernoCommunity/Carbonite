//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#pragma once

#include "Engine/Renderer/DynamicRendererData.h"

#include <cstdint>

namespace gp1::renderer
{
	enum class ETextureWrapping
	{
		Repeat,
		MirroredRepeat,
		ClampToEdge,
		ClampToBorder,
		MirroredClampToEdge
	};

	enum class ETextureFilter
	{
		Nearest,
		Linear,
		NearestMipmapNearest,
		NearestMipmapLinear,
		LinearMipmapNearest,
		LinearMipmapLinear
	};

	enum class ETextureFormat
	{
		Red,
		RG,
		RGB,
		BGR,
		RGBA,
		BGRA,
		RedInteger,
		RGInteger,
		RGBInteger,
		BGRInteger,
		RGBAInteger,
		BGRAInteger,
		StencilIndex,
		DepthComponent,
		DepthStencil
	};

	enum class ETextureDataType
	{
		UByte,
		Byte,
		UShort,
		Short,
		UInt,
		Int,
		HalfFloat,
		Float,
		UByte_3_3_2,
		UByte_2_3_3_Rev,
		UShort_5_6_5,
		UShort_5_6_5_Rev,
		UShort_4_4_4_4,
		UShort_4_4_4_4_Rev,
		UShort_5_5_5_1,
		UShort_1_5_5_5_Rev,
		UInt_8_8_8_8,
		UInt_8_8_8_8_Rev,
		UInt_10_10_10_2,
		UInt_2_10_10_10_Rev
	};

	struct TextureFilter
	{
	public:
		ETextureFilter m_Minimize = ETextureFilter::LinearMipmapLinear;
		ETextureFilter m_Magnify  = ETextureFilter::Linear;
	};

	struct TextureLod
	{
	public:
		float    m_Bias      = 0.0f;
		float    m_Min       = -1000.0f;
		float    m_Max       = 1000.0f;
		uint32_t m_BaseLevel = 0;
		uint32_t m_MaxLevel  = 1000;
	};

	struct Texture : public DynamicRendererData
	{
	public:
		virtual ~Texture() = default;

	protected:
		Texture() = default;

	public:
		ETextureFormat   m_Format = ETextureFormat::RGBA;
		ETextureDataType m_Type   = ETextureDataType::UByte;
		TextureFilter    m_Filter;
		TextureLod       m_Lod;
	};
} // namespace gp1::renderer