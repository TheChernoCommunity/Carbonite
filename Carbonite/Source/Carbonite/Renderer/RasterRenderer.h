#pragma once

#include "Carbonite/Scene/Scene.h"
#include "Graphics/Memory/Buffer.h"
#include "Graphics/Pipeline/Descriptor/DescriptorPool.h"
#include "Graphics/Pipeline/Descriptor/DescriptorSet.h"
#include "Graphics/Pipeline/Descriptor/DescriptorSetLayout.h"
#include "Graphics/Pipeline/GraphicsPipeline.h"
#include "Graphics/Pipeline/PipelineLayout.h"
#include "Graphics/Pipeline/ShaderModule.h"
#include "Mesh/Mesh.h"
#include "Renderer.h"
#include "Shader/Shader.h"

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
	Shader                               m_VertexShader;
	Shader                               m_FragmentShader;
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