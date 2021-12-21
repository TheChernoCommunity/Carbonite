#include "PCH.h"

#include "Log.h"
#include "Renderer/RasterRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

RasterRenderer::RasterRenderer()
    : m_VertexShader(m_Device, { "test.vert" }),
      m_FragmentShader(m_Device, { "test.frag" }),
      m_PipelineLayout(m_Device),
      m_Pipeline(m_RenderPass, m_PipelineLayout),
      m_DescriptorSetLayout(m_Device),
      m_DescriptorPool(m_Device),
      m_UniformBuffer(m_Vma),
      m_Mesh(m_Vma)
{
}

void RasterRenderer::initImpl()
{
	Log::trace("RasterRenderer init");

	if (!m_VertexShader.create())
		throw std::runtime_error("Failed to create vertex shader");

	if (!m_FragmentShader.create())
		throw std::runtime_error("Failed to create fragment shader");

	m_DescriptorSetLayout.m_Bindings = { { 0, vk::DescriptorType::eUniformBuffer, 1, vk::ShaderStageFlagBits::eVertex } };

	if (!m_DescriptorSetLayout.create())
		throw std::runtime_error("Failed to create vulkan descriptor set layout");
	m_Device.setDebugName(m_DescriptorSetLayout, "m_DescriptorSetLayout");

	m_PipelineLayout.m_DescriptorSetLayouts.push_back(&m_DescriptorSetLayout);

	if (!m_PipelineLayout.create())
		throw std::runtime_error("Failed to create vulkan pipeline layout");
	m_Device.setDebugName(m_PipelineLayout, "m_PipelineLayout");

	m_Pipeline.m_Shaders.push_back(&m_VertexShader);
	m_Pipeline.m_Shaders.push_back(&m_FragmentShader);

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

	m_UniformBuffer.m_Size = 128 * getMaxFramesInFlight();
	m_UniformBuffer.m_Usage |= vk::BufferUsageFlagBits::eUniformBuffer;
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
		writeDescriptorBufferInfos[i] = { m_UniformBuffer, 128 * i, 128 };
		writeDescriptorSets[i]        = { m_DescriptorSets[i], 0, 0, 1, vk::DescriptorType::eUniformBuffer, nullptr, &writeDescriptorBufferInfos[i], nullptr };
	}

	m_DescriptorPool.updateDescriptorSets(writeDescriptorSets, {});
}

void RasterRenderer::deinitImpl()
{
	Log::trace("RasterRenderer deinit");
}

static glm::fmat4 transformationMatrix(glm::fvec3 position, glm::fvec3 rotation, glm::fvec3 scale, bool negative = false)
{
	if (negative)
	{
		// What even is all of this???
		// Look at the old src/Engine/Scene/Entity.cpp file ;)
		float rx = rotation.x * 0.01745329251994329576923690768489f;
		float ry = rotation.y * 0.01745329251994329576923690768489f;
		float rz = rotation.z * 0.01745329251994329576923690768489f;
		float cx = cosf(rx);
		float cy = cosf(ry);
		float cz = cosf(rz);
		float sx = sinf(rx);
		float sy = sinf(ry);
		float sz = sinf(rz);

		glm::fvec4 r0 = { (cy * cz) * scale.x, (cx * sz + cz * sx * sy) * scale.x, (sx * sz - cx * cz * sy) * scale.x, 0.0f };
		glm::fvec4 r1 = { (-cy * sz) * scale.y, (cx * cz - sx * sy * sz) * scale.y, (cz * sx + cx * sy * sz) * scale.y, 0.0f };
		glm::fvec4 r2 = { sy * scale.z, (-cy * sx) * scale.z, (cx * cy) * scale.z, 0.0f };

		return {
			r0,
			r1,
			r2,
			{ r0.x * -position.x + r1.x * -position.y + r2.x * -position.z, r0.y * -position.x + r1.y * -position.y + r2.y * -position.z, r0.z * -position.x + r1.z * -position.y + r2.z * -position.z, 1.0f }
		};
	}
	else
	{
		float rx = rotation.x * 0.01745329251994329576923690768489f;
		float ry = rotation.y * 0.01745329251994329576923690768489f;
		float rz = rotation.z * 0.01745329251994329576923690768489f;
		float cx = cosf(rx);
		float cy = cosf(ry);
		float cz = cosf(rz);
		float sx = sinf(rx);
		float sy = sinf(ry);
		float sz = sinf(rz);

		return {
			{ (cy * cz) * scale.x, (cx * sz + cz * sx * sy) * scale.x, (sx * sz - cx * cz * sy) * scale.x, 0.0f },
			{ (-cy * sz) * scale.y, (cx * cz - sx * sy * sz) * scale.y, (cz * sx + cx * sy * sz) * scale.y, 0.0f },
			{ sy * scale.z, (-cy * sx) * scale.z, (cx * cy) * scale.z, 0.0f },
			{ position.x, position.y, position.z, 1.0f }
		};
	}
}

static glm::fmat4 infinitePerspective(float fovx, float aspectRatio, float near)
{
	float invAsp      = 1.0f / aspectRatio;
	float focalLength = 1.0f / std::tanf(glm::radians(fovx * invAsp) * 0.5f);

	return {
		0.0f, 0.0f, 0.0f, 1.0f,
		focalLength * invAsp, 0.0f, 0.0f, 0.0f,
		0.0f, -focalLength, 0.0f, 0.0f,
		0.0f, 0.0f, near, 0.0f
	};
}

static glm::fvec3 rotation = { 0.0f, 0.0f, 0.0f };
static float      t        = 0.0f;

void RasterRenderer::renderImpl()
{
	t += 0.01f;
	rotation.y += 1.10f;
	rotation.z += 2.30f;

	glm::fvec3 forward = {
		cosf(glm::radians(rotation.y)) * cosf(glm::radians(rotation.z)),
		cosf(glm::radians(rotation.y)) * -sinf(glm::radians(rotation.z)),
		sinf(glm::radians(rotation.y))
	};
	glm::fvec3 position = forward * 5.0f;

	glm::fmat4 modelMatrix = transformationMatrix(position, {}, { 1.0f, 1.0f, 1.0f });
	glm::fmat4 viewMatrix  = transformationMatrix({}, rotation, { 1.0f, 1.0f, 1.0f }, true);
	glm::fmat4 projMatrix  = infinitePerspective(90.0f, static_cast<float>(m_Swapchain.m_Width) / m_Swapchain.m_Height, 0.01f);

	glm::fmat4 projViewMatrix = projMatrix * viewMatrix;

	void* uniformBufferMemory = m_UniformBuffer.mapMemory();
	std::memcpy(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(uniformBufferMemory) + 128 * m_CurrentFrame), &modelMatrix, sizeof(glm::fmat4));
	std::memcpy(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(uniformBufferMemory) + 128 * m_CurrentFrame + 64), &projViewMatrix, sizeof(glm::fmat4));
	m_UniformBuffer.unmapMemory();

	auto& currentCommandPool   = *getCurrentCommandPool();
	auto& currentCommandBuffer = *currentCommandPool.getCommandBuffer(vk::CommandBufferLevel::ePrimary, 0);
	if (currentCommandBuffer.begin())
	{
		currentCommandBuffer.cmdBeginRenderPass(m_RenderPass, m_Framebuffers[m_CurrentImage], { { 0, 0 }, { m_Swapchain.m_Width, m_Swapchain.m_Height } }, { vk::ClearColorValue(std::array<float, 4> { 0.1f, 0.1f, 0.1f, 1.0f }), vk::ClearDepthStencilValue(1.0f, 0) });

		currentCommandBuffer.cmdSetViewports({ { 0.0f, 0.0f, static_cast<float>(m_Swapchain.m_Width), static_cast<float>(m_Swapchain.m_Height), 0.0f, 1.0f } });
		currentCommandBuffer.cmdSetScissors({ { { 0, 0 }, { m_Swapchain.m_Width, m_Swapchain.m_Height } } });

		currentCommandBuffer.cmdSetLineWidth(1.0f);
		currentCommandBuffer.cmdBindPipeline(m_Pipeline);
		currentCommandBuffer.cmdBindVertexBuffers(0, { &m_Mesh.getMeshData() }, { 0 });
		currentCommandBuffer.cmdBindIndexBuffer(m_Mesh.getMeshData(), m_Mesh.getVertexCount() * sizeof(Vertex), vk::IndexType::eUint32);
		currentCommandBuffer.cmdBindDescriptorSets(m_Pipeline.getBindPoint(), m_Pipeline.getPipelineLayout(), 0, { &m_DescriptorSets[m_CurrentFrame] }, {});
		currentCommandBuffer.cmdDrawIndexed(m_Mesh.getIndexCount(), 1, 0, 0, 0);

		currentCommandBuffer.cmdEndRenderPass();
		currentCommandBuffer.end();
	}
}
