#pragma once

#include "Graphics/Memory/Buffer.h"
#include "Graphics/Pipeline/DescriptorPool.h"
#include "Graphics/Pipeline/DescriptorSet.h"
#include "Graphics/Pipeline/DescriptorSetLayout.h"
#include "Graphics/Pipeline/GraphicsPipeline.h"
#include "Graphics/Pipeline/PipelineLayout.h"
#include "Graphics/Shader.h"
#include "Mesh/Mesh.h"
#include "Renderer.h"
#include "Scene/Scene.h"

class RasterRenderer : public Renderer
{
public:
	RasterRenderer();

private:
	virtual void initImpl() override;
	virtual void deinitImpl() override;
	virtual void renderImpl() override;

public:
	// Test pipeline
	Graphics::Shader                     m_VertexShader;
	Graphics::Shader                     m_FragmentShader;
	Graphics::PipelineLayout             m_PipelineLayout;
	Graphics::GraphicsPipeline           m_Pipeline;
	Graphics::DescriptorSetLayout        m_DescriptorSetLayout;
	Graphics::DescriptorPool             m_DescriptorPool;
	std::vector<Graphics::DescriptorSet> m_DescriptorSets;
	Graphics::Memory::Buffer             m_UniformBuffer;

	Scene               m_Scene;
	TransformComponent* m_CameraTransform;
	Mesh                m_Mesh;
};