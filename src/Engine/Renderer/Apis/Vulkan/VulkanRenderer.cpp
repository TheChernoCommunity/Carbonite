//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/Vulkan/VulkanRenderer.h"
#include "Engine/Renderer/Apis/Vulkan/VulkanDebugRenderer.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanMeshData.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanSkeletalMeshData.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanStaticMeshData.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanStaticVoxelMeshData.h"
#include "Engine/Renderer/Apis/Vulkan/Shader/VulkanMaterialData.h"
#include "Engine/Renderer/Apis/Vulkan/Shader/VulkanShaderData.h"

namespace gp1 {

	VulkanRenderer::VulkanRenderer(Window* window)
		: Renderer(window) {}

	RendererType VulkanRenderer::GetRendererType() const {
		return RendererType::VULKAN;
	}

	DebugRenderer* VulkanRenderer::CreateDebugRenderer() {
		return new VulkanDebugRenderer(this);
	}

	MeshData* VulkanRenderer::CreateSkeletalMeshData(Mesh* mesh) {
		return new VulkanSkeletalMeshData(mesh);
	}

	MeshData* VulkanRenderer::CreateStaticMeshData(Mesh* mesh) {
		return new VulkanStaticMeshData(mesh);
	}

	MeshData* VulkanRenderer::CreateStaticVoxelMeshData(Mesh* mesh) {
		return new VulkanStaticVoxelMeshData(mesh);
	}

	ShaderData* VulkanRenderer::CreateShaderData(Shader* shader) {
		return new VulkanShaderData(shader);
	}

	MaterialData* VulkanRenderer::CreateMaterialData(Material* material) {
		return new VulkanMaterialData(material);
	}

	void VulkanRenderer::InitRenderer() {

	}

	void VulkanRenderer::DeInitRenderer() {

	}

	void VulkanRenderer::RenderScene(Scene* scene, uint32_t width, uint32_t height) {
		_CRT_UNUSED(scene);
		_CRT_UNUSED(width);
		_CRT_UNUSED(height);
	}

} // namespace gp1
