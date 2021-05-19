#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_VULKAN

#include "Engine/Renderer/Material/Uniform.h"

namespace gp1::renderer::vulkan
{
	struct VulkanUniformBuffer : public UniformBuffer
	{
	};

	struct VulkanUniformFloat : public UniformFloat
	{
	};

	struct VulkanUniformFVec2 : public UniformFVec2
	{
	};

	struct VulkanUniformFVec3 : public UniformFVec3
	{
	};

	struct VulkanUniformFVec4 : public UniformFVec4
	{
	};

	struct VulkanUniformInt : public UniformInt
	{
	};

	struct VulkanUniformIVec2 : public UniformIVec2
	{
	};

	struct VulkanUniformIVec3 : public UniformIVec3
	{
	};

	struct VulkanUniformIVec4 : public UniformIVec4
	{
	};

	struct VulkanUniformUInt : public UniformUInt
	{
	};

	struct VulkanUniformUVec2 : public UniformUVec2
	{
	};

	struct VulkanUniformUVec3 : public UniformUVec3
	{
	};

	struct VulkanUniformUVec4 : public UniformUVec4
	{
	};

	struct VulkanUniformFMat2 : public UniformFMat2
	{
	};

	struct VulkanUniformFMat3 : public UniformFMat3
	{
	};

	struct VulkanUniformFMat4 : public UniformFMat4
	{
	};

	struct VulkanUniformTexture2D : public UniformTexture2D
	{
	};

	struct VulkanUniformTexture2DArray : public UniformTexture2DArray
	{
	};

	struct VulkanUniformTexture3D : public UniformTexture3D
	{
	};

	struct VulkanUniformTextureCubeMap : public UniformTextureCubeMap
	{
	};
} // namespace gp1::renderer::vulkan
#endif