#pragma once

#include "Graphics/Pipeline/GraphicsPipeline.h"
#include "Graphics/Pipeline/PipelineLayout.h"
#include "Graphics/Shader.h"
#include "Renderer.h"

class RasterRenderer : public Renderer
{
public:
	RasterRenderer();

private:
	virtual void initImpl() override;
	virtual void deinitImpl() override;
	virtual void renderImpl() override;

protected:
	// Test pipeline
	Graphics::Shader           m_VertexShader;
	Graphics::Shader           m_FragmentShader;
	Graphics::PipelineLayout   m_PipelineLayout;
	Graphics::GraphicsPipeline m_Pipeline;
};