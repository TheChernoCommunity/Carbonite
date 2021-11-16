#pragma once

#include "Graphics/Commands/CommandPool.h"
#include "Graphics/Debug/Debug.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Device/Queue.h"
#include "Graphics/Device/Surface.h"
#include "Graphics/Image/Framebuffer.h"
#include "Graphics/Image/Image.h"
#include "Graphics/Image/ImageView.h"
#include "Graphics/Instance.h"
#include "Graphics/Memory/VMA.h"
#include "Graphics/Pipeline/RenderPass.h"
#include "Graphics/Swapchain/Swapchain.h"
#include "Graphics/Sync/Fence.h"
#include "Graphics/Sync/Semaphore.h"
#include "Graphics/Window.h"

#include <vector>

class Renderer
{
public:
	Renderer();
	virtual ~Renderer() = default;

	void init();
	void deinit();

	void render();

private:
	virtual void initImpl()   = 0;
	virtual void deinitImpl() = 0;
	virtual void renderImpl() = 0;

	void recreateSwapchain();

protected:
	Graphics::Instance m_Instance;
	Graphics::Debug    m_Debug;
	Graphics::Surface  m_Surface;
	Graphics::Device   m_Device;

	Graphics::QueueFamily* m_GraphicsPresentQueueFamily;
	Graphics::Queue*       m_GraphicsPresentQueue;

	Graphics::Memory::VMA m_Vma;

	std::vector<Graphics::CommandPool>     m_CommandPools;
	std::vector<Graphics::Sync::Semaphore> m_ImageAvailableSemaphores;
	std::vector<Graphics::Sync::Semaphore> m_RenderFinishedSemaphores;
	std::vector<Graphics::Sync::Fence>     m_InFlightFences;
	std::uint32_t                          m_CurrentFrame;

	bool                                m_RecreateSwapchain = false;
	Graphics::Swapchain                 m_Swapchain;
	std::vector<Graphics::ImageView>    m_SwapchainImageViews;
	std::vector<Graphics::Image>        m_SwapchainDepthImages;
	std::vector<Graphics::ImageView>    m_SwapchainDepthImageViews;
	std::vector<Graphics::Framebuffer>  m_Framebuffers;
	std::vector<Graphics::Sync::Fence*> m_ImagesInFlight;
	std::uint32_t                       m_CurrentImage;
	Graphics::RenderPass                m_RenderPass;

private:
	std::size_t m_MaxFramesInFlight = 2;
};