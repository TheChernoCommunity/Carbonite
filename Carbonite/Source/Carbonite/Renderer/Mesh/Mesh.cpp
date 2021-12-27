#include "PCH.h"

#include "Carbonite/Carbonite.h"
#include "Carbonite/Renderer/Renderer.h"
#include "Mesh.h"

Mesh::Mesh(Graphics::Memory::VMA& vma)
    : m_MeshData(vma)
{
	m_MeshData.m_Usage |= vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eIndexBuffer;
}

void Mesh::updateMeshData()
{
	m_VertexCount = m_Vertices.size();
	m_IndexCount  = m_Indices.size();

	m_MeshData.m_Size = m_VertexCount * sizeof(Vertex) + m_IndexCount * sizeof(std::uint32_t);

	if (!m_MeshData.create())
		throw std::runtime_error("Failed to create vulkan buffer");
	m_MeshData.getVma().getDevice().setDebugName(m_MeshData, "m_MeshData");

	{
		Graphics::Memory::Buffer stagingBuffer = { m_MeshData.getVma() };

		stagingBuffer.m_Size        = m_MeshData.getSize();
		stagingBuffer.m_Usage       = vk::BufferUsageFlagBits::eTransferSrc;
		stagingBuffer.m_MemoryUsage = VMA_MEMORY_USAGE_CPU_ONLY;
		if (!stagingBuffer.create())
			throw std::runtime_error("Failed to create vulkan staging buffer");

		void* mappedMemory = stagingBuffer.mapMemory();
		std::memcpy(mappedMemory, m_Vertices.data(), m_VertexCount * sizeof(Vertex));
		std::memcpy(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(mappedMemory) + m_VertexCount * sizeof(Vertex)), m_Indices.data(), m_IndexCount * sizeof(std::uint32_t));
		stagingBuffer.unmapMemory();

		Renderer* renderer = Carbonite::Get().getRenderer();

		auto& currentCommandPool   = *renderer->getCurrentCommandPool();
		auto& currentCommandBuffer = *currentCommandPool.getCommandBuffer(vk::CommandBufferLevel::ePrimary, 0);
		if (currentCommandBuffer.begin())
		{
			currentCommandBuffer.cmdCopyBuffer(stagingBuffer, m_MeshData, { { 0, 0, m_MeshData.getSize() } });
			currentCommandBuffer.end();

			renderer->m_GraphicsPresentQueue->submitCommandBuffers({ &currentCommandBuffer }, {}, {}, {}, nullptr);
			renderer->m_GraphicsPresentQueue->waitIdle();
		}
	}
}