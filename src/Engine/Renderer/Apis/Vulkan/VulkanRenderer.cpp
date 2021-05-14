//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/Vulkan/VulkanRenderer.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanMeshData.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanSkeletalMeshData.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanStaticMeshData.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanStaticVoxelMeshData.h"
#include "Engine/Renderer/Apis/Vulkan/Shader/VulkanMaterialData.h"
#include "Engine/Renderer/Apis/Vulkan/Shader/VulkanShaderData.h"
#include "Engine/Renderer/Apis/Vulkan/Texture/VulkanTexture2DArrayData.h"
#include "Engine/Renderer/Apis/Vulkan/Texture/VulkanTexture2DData.h"
#include "Engine/Renderer/Apis/Vulkan/Texture/VulkanTexture3DData.h"
#include "Engine/Renderer/Apis/Vulkan/Texture/VulkanTextureCubeMapData.h"
#include "Engine/Renderer/Apis/Vulkan/VulkanDebugRenderer.h"

namespace gp1::renderer::apis::vulkan
{
	VulkanRenderer::VulkanRenderer(window::Window* window)
	    : Renderer(window) {}

	RendererType VulkanRenderer::GetRendererType() const
	{
		return RendererType::VULKAN;
	}

	renderer::debug::DebugRenderer* VulkanRenderer::CreateDebugRenderer()
	{
		return new debug::VulkanDebugRenderer(this);
	}

	RendererData* VulkanRenderer::CreateRendererData(Data* data)
	{
		if (!data) return nullptr;

		const std::type_info& type = data->GetType();
		if (type == typeid(renderer::mesh::SkeletalMesh))
		{
			return new mesh::VulkanSkeletalMeshData(reinterpret_cast<renderer::mesh::SkeletalMesh*>(data));
		}
		else if (type == typeid(renderer::mesh::StaticMesh))
		{
			return new mesh::VulkanStaticMeshData(reinterpret_cast<renderer::mesh::StaticMesh*>(data));
		}
		else if (type == typeid(renderer::mesh::StaticVoxelMesh))
		{
			return new mesh::VulkanStaticVoxelMeshData(reinterpret_cast<renderer::mesh::StaticVoxelMesh*>(data));
		}
		else if (type == typeid(renderer::shader::Shader))
		{
			return new shader::VulkanShaderData(reinterpret_cast<renderer::shader::Shader*>(data));
		}
		else if (type == typeid(renderer::shader::Material))
		{
			return new shader::VulkanMaterialData(reinterpret_cast<renderer::shader::Material*>(data));
		}
		else if (type == typeid(renderer::texture::Texture2D))
		{
			return new texture::VulkanTexture2DData(reinterpret_cast<renderer::texture::Texture2D*>(data));
		}
		else if (type == typeid(renderer::texture::Texture2DArray))
		{
			return new texture::VulkanTexture2DArrayData(reinterpret_cast<renderer::texture::Texture2DArray*>(data));
		}
		else if (type == typeid(renderer::texture::Texture3D))
		{
			return new texture::VulkanTexture3DData(reinterpret_cast<renderer::texture::Texture3D*>(data));
		}
		else if (type == typeid(renderer::texture::TextureCubeMap))
		{
			return new texture::VulkanTextureCubeMapData(reinterpret_cast<renderer::texture::TextureCubeMap*>(data));
		}

		return nullptr;
	}

	void VulkanRenderer::InitRenderer()
	{
	}

	void VulkanRenderer::DeInitRenderer()
	{
	}

	void VulkanRenderer::RenderScene([[maybe_unused]] scene::Scene* scene, [[maybe_unused]] uint32_t width, [[maybe_unused]] uint32_t height)
	{
	}

} // namespace gp1::renderer::apis::vulkan
