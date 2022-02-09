#include "PCH.h"

#include "Carbonite/Scene/Components/CameraComponent.h"
#include "Carbonite/Scene/Components/StaticMeshComponent.h"
#include "Carbonite/Scene/Components/TransformComponent.h"
#include "Carbonite/Scene/ECS.h"
#include "RasterRenderer.h"
#include "Utils/Log.h"
#include "Utils/Utils.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

RasterRenderer::RasterRenderer()
    : m_VertexShader(m_Device),
      m_FragmentShader(m_Device),
      m_PipelineLayout(m_Device),
      m_Pipeline(m_RenderPass, m_PipelineLayout),
      m_DescriptorSetLayout(m_Device),
      m_DescriptorPool(m_Device),
      m_UniformBuffer(m_Vma),
      m_CameraTransform(nullptr),
      m_Mesh(m_Vma) {}

void RasterRenderer::initImpl()
{
	Log::trace("RasterRenderer init");

	m_VertexShader.m_ShaderFile   = "test.vert";
	m_FragmentShader.m_ShaderFile = "test.frag";
	m_VertexShader.updateShader();
	m_FragmentShader.updateShader();

	m_DescriptorSetLayout.m_Bindings = { { 0, vk::DescriptorType::eUniformBuffer, 1, vk::ShaderStageFlagBits::eVertex } };

	if (!m_DescriptorSetLayout.create())
		throw std::runtime_error("Failed to create vulkan descriptor set layout");
	m_Device.setDebugName(m_DescriptorSetLayout, "m_DescriptorSetLayout");

	m_PipelineLayout.m_DescriptorSetLayouts.push_back(&m_DescriptorSetLayout);

	if (!m_PipelineLayout.create())
		throw std::runtime_error("Failed to create vulkan pipeline layout");
	m_Device.setDebugName(m_PipelineLayout, "m_PipelineLayout");

	m_Pipeline.m_ShaderStages.push_back(&m_VertexShader.getShaderModule());
	m_Pipeline.m_ShaderStages.push_back(&m_FragmentShader.getShaderModule());

	m_Pipeline.m_VertexInputState.m_Bindings   = { { 0, sizeof(Vertex), vk::VertexInputRate::eVertex } };
	m_Pipeline.m_VertexInputState.m_Attributes = { { 0, 0, vk::Format::eR32G32B32A32Sfloat, offsetof(Vertex, m_Position) },
		                                           { 1, 0, vk::Format::eR32G32B32A32Sfloat, offsetof(Vertex, m_Normal) },
		                                           { 2, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, m_UV) } };

	m_Pipeline.m_ViewportState.m_Viewports = { { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f } };
	m_Pipeline.m_ViewportState.m_Scissors  = { { { 0, 0 }, { 0, 0 } } };

	m_Pipeline.m_ColorBlendState.m_Attachments.emplace_back(true, vk::BlendFactor::eSrcAlpha, vk::BlendFactor::eOneMinusSrcAlpha, vk::BlendOp::eAdd, vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd, vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);

	m_Pipeline.m_DynamicStates = { vk::DynamicState::eViewport,
		                           vk::DynamicState::eScissor,
		                           vk::DynamicState::eLineWidth };

	if (!m_Pipeline.create())
		throw std::runtime_error("Failed to create vulkan graphics pipeline");
	m_Device.setDebugName(m_Pipeline, "m_Pipeline");

	m_VertexShader.getShaderModule().destroy();
	m_FragmentShader.getShaderModule().destroy();

	m_DescriptorPool.m_MaxSets   = static_cast<std::uint32_t>(getMaxFramesInFlight());
	m_DescriptorPool.m_PoolSizes = { { vk::DescriptorType::eUniformBuffer, static_cast<std::uint32_t>(getMaxFramesInFlight()) } };

	if (!m_DescriptorPool.create())
		throw std::runtime_error("Failed to create vulkan descriptor pool");
	m_Device.setDebugName(m_DescriptorPool, "m_DescriptorPool");

	m_Mesh.m_Vertices = {
		{ { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 1.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
		{ { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
		{ { 1.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { 1.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 0.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
		{ { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { 0.0f, 0.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { 0.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 0.0f, 1.0f, 0.0f, 1.0f }, { -1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
		{ { 0.0f, 0.0f, 0.0f, 1.0f }, { -1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { 0.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
		{ { 1.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { 1.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
		{ { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
	};
	m_Mesh.m_Indices = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	m_Mesh.updateMeshData();

	m_UniformBuffer.m_Size = Utils::alignCeil(128, m_Device.getPhysicalDeviceLimits().minUniformBufferOffsetAlignment) * getMaxFramesInFlight();
	m_UniformBuffer.m_Usage = vk::BufferUsageFlagBits::eUniformBuffer;
	m_UniformBuffer.m_MemoryUsage = VMA_MEMORY_USAGE_CPU_TO_GPU;
	if (!m_UniformBuffer.create())
		throw std::runtime_error("Failed to create vulkan uniform buffer");
	m_Device.setDebugName(m_UniformBuffer, "m_UniformBuffer");

	m_DescriptorSets = m_DescriptorPool.allocateSets(std::vector<Graphics::DescriptorSetLayout*>(getMaxFramesInFlight(), &m_DescriptorSetLayout));

	std::vector<vk::DescriptorBufferInfo> writeDescriptorBufferInfos;
	std::vector<vk::WriteDescriptorSet>   writeDescriptorSets;
	writeDescriptorBufferInfos.resize(getMaxFramesInFlight());
	writeDescriptorSets.resize(getMaxFramesInFlight());
	for (std::size_t i = 0; i < getMaxFramesInFlight(); ++i)
	{
		writeDescriptorBufferInfos[i] = { m_UniformBuffer, Utils::alignCeil(128, m_Device.getPhysicalDeviceLimits().minUniformBufferOffsetAlignment) * i, 128 };
		writeDescriptorSets[i]        = { m_DescriptorSets[i], 0, 0, 1, vk::DescriptorType::eUniformBuffer, nullptr, &writeDescriptorBufferInfos[i], nullptr };
	}

	m_DescriptorPool.updateDescriptorSets(writeDescriptorSets, {});

	auto& ecs      = ECS::Get();
	auto& registry = ecs.getRegistry();

	entt::entity camera = m_Scene.instantiate({});
	registry.emplace<CameraComponent>(camera);
	m_CameraTransform = &registry.get<TransformComponent>(camera);

	entt::entity cube = m_Scene.instantiate({});
	registry.emplace<StaticMeshComponent>(cube, &m_Mesh);
}

void RasterRenderer::deinitImpl()
{
	Log::trace("RasterRenderer deinit");
}

static glm::fvec3 rotation = { 0.0f, 0.0f, 0.0f };

void RasterRenderer::renderImpl()
{
	rotation.y += 0.01f;
	rotation.z += 0.03f;
	m_CameraTransform->setRotation(rotation);
	m_CameraTransform->setTranslation(m_CameraTransform->getForward() * -5.0f);

	void* uniformBufferMemory = m_UniformBuffer.mapMemory();

	auto& currentCommandPool   = *getCurrentCommandPool();
	auto& currentCommandBuffer = *currentCommandPool.getCommandBuffer(vk::CommandBufferLevel::ePrimary, 0);
	if (currentCommandBuffer.begin())
	{
		auto& ecs      = ECS::Get();
		auto& registry = ecs.getRegistry();
		auto  cameras  = registry.view<CameraComponent>();
		auto  meshes   = registry.view<TransformComponent, StaticMeshComponent>();

		for (auto camera : cameras)
		{
			auto& cameraComponent = cameras.get<CameraComponent>(camera);
			cameraComponent.setAspect(static_cast<float>(m_Swapchain.m_Width) / m_Swapchain.m_Height);
			auto& projectionViewMatrix = cameraComponent.getProjectionViewMatrix();
			std::memcpy(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(uniformBufferMemory) + Utils::alignCeil(128, m_Device.getPhysicalDeviceLimits().minUniformBufferOffsetAlignment) * m_CurrentFrame), &projectionViewMatrix, sizeof(projectionViewMatrix));

			currentCommandBuffer.cmdBeginRenderPass(m_RenderPass, m_Framebuffers[m_CurrentImage], { { 0, 0 }, { m_Swapchain.m_Width, m_Swapchain.m_Height } }, { vk::ClearColorValue(std::array<float, 4> { 0.1f, 0.1f, 0.1f, 1.0f }), vk::ClearDepthStencilValue(1.0f, 0) });
			currentCommandBuffer.cmdSetViewports({ { 0.0f, 0.0f, static_cast<float>(m_Swapchain.m_Width), static_cast<float>(m_Swapchain.m_Height), 0.0f, 1.0f } });
			currentCommandBuffer.cmdSetScissors({ { { 0, 0 }, { m_Swapchain.m_Width, m_Swapchain.m_Height } } });

			for (auto mesh : meshes)
			{
				auto [transformComponent, meshComponent] = meshes.get<TransformComponent, StaticMeshComponent>(mesh);

				Mesh* pMesh = meshComponent.m_Mesh;
				if (!pMesh)
					continue;

				auto& transformationMatrix = transformComponent.getMatrix();
				std::memcpy(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(uniformBufferMemory) + Utils::alignCeil(128, m_Device.getPhysicalDeviceLimits().minUniformBufferOffsetAlignment) * m_CurrentFrame + 64), &transformationMatrix, sizeof(transformationMatrix));

				currentCommandBuffer.cmdBindPipeline(m_Pipeline);
				currentCommandBuffer.cmdBindDescriptorSets(m_Pipeline.getBindPoint(), m_Pipeline.getPipelineLayout(), 0, { &m_DescriptorSets[m_CurrentFrame] }, {});

				currentCommandBuffer.cmdSetLineWidth(1.0f);
				currentCommandBuffer.cmdBindVertexBuffers(0, { &pMesh->getMeshData() }, { 0 });
				currentCommandBuffer.cmdBindIndexBuffer(pMesh->getMeshData(), pMesh->getVertexCount() * sizeof(Vertex), vk::IndexType::eUint32);
				currentCommandBuffer.cmdDrawIndexed(static_cast<std::uint32_t>(pMesh->getIndexCount()), 1, 0, 0, 0);
			}

			currentCommandBuffer.cmdEndRenderPass();
		}

		currentCommandBuffer.end();
	}

	m_UniformBuffer.unmapMemory();
}
