#include "PCH.h"

#include "Carbonite.h"
#include "Events/Event.h"
#include "Log.h"
#include "Renderer/Renderer.h"

#include <stdexcept>

static void ThrowInstanceException(Graphics::Instance& instance);

Renderer::Renderer()
    : m_Instance("Carbonite", { 0, 0, 1, 0 }, "Carbonite", { 0, 0, 1, 0 }, VK_API_VERSION_1_0, { 0, 2, 0, 0 }),
      m_Debug(m_Instance),
      m_Surface(m_Instance),
      m_Device(m_Surface),
      m_GraphicsPresentQueueFamily(nullptr),
      m_GraphicsPresentQueue(nullptr),
      m_Vma(m_Device),
      m_CurrentFrame(0),
      m_RenderPass(m_Device),
      m_Swapchain(m_Vma),
      m_CurrentImage(0)
{
}

void Renderer::init()
{
	Log::trace("Renderer init");

	m_CommandPools.reserve(m_MaxFramesInFlight);
	m_ImageAvailableSemaphores.reserve(m_MaxFramesInFlight);
	m_RenderFinishedSemaphores.reserve(m_MaxFramesInFlight);
	m_InFlightFences.reserve(m_MaxFramesInFlight);
	for (std::size_t i = 0; i < m_MaxFramesInFlight; ++i)
	{
		m_CommandPools.emplace_back(m_Device);
		m_ImageAvailableSemaphores.emplace_back(m_Device);
		m_RenderFinishedSemaphores.emplace_back(m_Device);
		m_InFlightFences.emplace_back(m_Device);
	}

	//-----------------
	// Create Instance
	{
		// Request extensions glfw require
		std::uint32_t glfwExtensionCount;
		const char**  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		for (std::size_t i = 0; i < glfwExtensionCount; ++i)
			m_Instance.requestExtension(glfwExtensions[i]);
	}

	if (!m_Instance.create())
		ThrowInstanceException(m_Instance);
	//-----------------

	//--------------
	// Create Debug
	if (Graphics::Debug::IsEnabled())
		m_Debug.create();
	//--------------

	//----------------
	// Create Window and Surface
	auto& window = Carbonite::Get().getWindow();
	if (!window.create())
		throw std::runtime_error("Failed to create GLFW window");
	Event::addWindow(*window);

	m_Surface.m_Window = &window;
	if (!m_Surface.create())
		throw std::runtime_error("Failed to create vulkan surface");
	//----------------

	//---------------
	// Create Device
	m_Device.requestExtension("VK_KHR_swapchain");
	m_Device.requestExtension("VK_KHR_portability_subset", { 0U }, false); // Requested for MoltenVK on MacOS

	m_Device.requestQueueFamily(1, vk::QueueFlagBits::eGraphics, true);

	if (!m_Device.create())
		throw std::runtime_error("Found no suitable vulkan device");

	m_GraphicsPresentQueueFamily = m_Device.getQueueFamily(vk::QueueFlagBits::eGraphics, true);
	m_GraphicsPresentQueue       = m_GraphicsPresentQueueFamily->getQueue(0);
	m_Device.setDebugName(*m_GraphicsPresentQueue, "m_GraphicsPresentQueue");
	//---------------

	//------------
	// Create Vma
	if (!m_Vma.create())
		throw std::runtime_error("Failed to create vulkan memory allocator");
	//------------

	//---------------------------------------------
	// Create Command Pools and Frame Sync Objects
	for (std::size_t i = 0; i < m_MaxFramesInFlight; ++i)
	{
		//---------------------
		// Create Command Pool
		auto& commandPool = m_CommandPools[i];
		commandPool.setQueueFamily(*m_GraphicsPresentQueueFamily);

		if (!commandPool.create())
			throw std::runtime_error("Failed to create command pool");
		m_Device.setDebugName(commandPool, "m_CommandPools[" + std::to_string(i) + ']');

		commandPool.allocateBuffers(vk::CommandBufferLevel::ePrimary, 1);
		//---------------------

		//----------------------------------
		// Create Image Available Semaphore
		auto& ias = m_ImageAvailableSemaphores[i];
		if (!ias.create())
			throw std::runtime_error("Failed to create vulkan semaphore");
		m_Device.setDebugName(ias, "m_ImageAvailableSemaphores[" + std::to_string(i) + ']');
		//----------------------------------

		//----------------------------------
		// Create Render Finished Semaphore
		auto& rfs = m_RenderFinishedSemaphores[i];
		if (!rfs.create())
			throw std::runtime_error("Failed to create vulkan semaphore");
		m_Device.setDebugName(rfs, "m_RenderFinishedSemaphores[" + std::to_string(i) + ']');
		//----------------------------------

		//-------------------------
		// Create In Flight Fences
		auto& iff = m_InFlightFences[i];
		iff.setSignaled();
		if (!iff.create())
			throw std::runtime_error("Failed to create vulkan fence");
		m_Device.setDebugName(iff, "m_InFlightFences[" + std::to_string(i) + ']');
		//-------------------------
	}
	//---------------------------------------------

	recreateSwapchain();

	initImpl();
}

void Renderer::deinit()
{
	deinitImpl();

	Log::trace("Renderer deinit");
}

void Renderer::render()
{
	//-------------
	// Begin frame
	if (m_RecreateSwapchain)
		recreateSwapchain();

	Graphics::Sync::Fence& iff = m_InFlightFences[m_CurrentFrame];
	iff.waitFor(~0ULL);
	iff.reset();

	vk::Result result = m_Swapchain.acquireNextImage(~0U, &m_ImageAvailableSemaphores[m_CurrentFrame], nullptr, m_CurrentImage);
	if (result == vk::Result::eErrorOutOfDateKHR)
	{
		recreateSwapchain();
		return;
	}
	else if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR)
	{
		throw std::runtime_error("Failed to acquire next vulkan swapchain image");
	}

	if (m_ImagesInFlight[m_CurrentImage])
		m_ImagesInFlight[m_CurrentImage]->waitFor(~0ULL);
	m_ImagesInFlight[m_CurrentImage] = &m_InFlightFences[m_CurrentFrame];

	m_CommandPools[m_CurrentFrame].reset();
	m_InFlightFences[m_CurrentFrame].reset();
	//-------------

	renderImpl();

	//-------------
	// End frame
	auto&       commandBufferLevels      = m_CommandPools[m_CurrentFrame].getCommandBuffers();
	std::size_t submitCommandBufferCount = 0;
	std::size_t submitCommandBufferI     = 0;
	for (auto& level : commandBufferLevels)
		submitCommandBufferCount += level.second.size();

	std::vector<Graphics::CommandBuffer*> submitCommandBuffers(submitCommandBufferCount);
	for (auto& level : commandBufferLevels)
	{
		for (auto& buf : level.second)
		{
			submitCommandBuffers[submitCommandBufferI] = const_cast<Graphics::CommandBuffer*>(&buf);
			++submitCommandBufferI;
		}
	}

	m_GraphicsPresentQueue->submitCommandBuffers(submitCommandBuffers, { &m_ImageAvailableSemaphores[m_CurrentFrame] }, { &m_RenderFinishedSemaphores[m_CurrentFrame] }, { vk::PipelineStageFlagBits::eColorAttachmentOutput }, &m_InFlightFences[m_CurrentFrame]);
	result = m_GraphicsPresentQueue->present({ &m_Swapchain }, { m_CurrentImage }, { &m_RenderFinishedSemaphores[m_CurrentFrame] })[0];
	if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR)
	{
		m_GraphicsPresentQueue->waitIdle();
		recreateSwapchain();
		return;
	}
	else if (result != vk::Result::eSuccess)
	{
		throw std::runtime_error("Failed to present vulkan swapchain");
	}

	m_GraphicsPresentQueue->waitIdle();

	m_CurrentFrame = (m_CurrentFrame + 1) % m_MaxFramesInFlight;
	//-------------
}

void Renderer::recreateSwapchain()
{
	m_SwapchainImageViews.clear();
	m_SwapchainDepthImages.clear();
	m_SwapchainDepthImageViews.clear();
	m_Framebuffers.clear();
	m_ImagesInFlight.clear();

	auto oldFormat = m_Swapchain.m_Format;

	auto& physicalDevice = m_Device.getPhysicalDevice();

	auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(*m_Surface);
	auto surfaceFormats      = physicalDevice.getSurfaceFormatsKHR(*m_Surface);
	auto format              = surfaceFormats[0];

	if (oldFormat != format.format)
	{
		//-------------------
		// Create RenderPass
		m_RenderPass.m_Attachments.clear();
		m_RenderPass.m_Subpasses.clear();
		m_RenderPass.m_Dependencies.clear();

		Graphics::RenderPassAttachment colorAttachment;
		colorAttachment.m_Format = format.format;
		m_RenderPass.m_Attachments.push_back(colorAttachment);

		Graphics::RenderPassAttachment depthAttachment;
		depthAttachment.m_Format         = vk::Format::eD32SfloatS8Uint;
		depthAttachment.m_StoreOp        = vk::AttachmentStoreOp::eDontCare;
		depthAttachment.m_StencilLoadOp  = vk::AttachmentLoadOp::eClear;
		depthAttachment.m_StencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		depthAttachment.m_FinalLayout    = vk::ImageLayout::eDepthStencilAttachmentOptimal;
		m_RenderPass.m_Attachments.push_back(depthAttachment);

		Graphics::RenderPassSubpass subpass;
		subpass.m_ColorAttachmentRefs.emplace_back(0, vk::ImageLayout::eColorAttachmentOptimal);
		subpass.m_UseDepthStencilAttachment = true;
		subpass.m_DepthStencilAttachment    = { 1, vk::ImageLayout::eDepthStencilAttachmentOptimal };
		m_RenderPass.m_Subpasses.push_back(subpass);

		Graphics::RenderPassSubpassDependency dependency;
		dependency.m_SrcSubpass    = ~0U;
		dependency.m_DstSubpass    = 0;
		dependency.m_SrcStageMask  = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
		dependency.m_SrcAccessMask = vk::AccessFlagBits::eNoneKHR;
		dependency.m_DstStageMask  = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
		dependency.m_DstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eDepthStencilAttachmentWrite;
		m_RenderPass.m_Dependencies.push_back(dependency);

		if (!m_RenderPass.create())
			throw std::runtime_error("Failed to create vulkan renderpass");
		m_Device.setDebugName(m_RenderPass, "m_RenderPass");
		//-------------------
	}

	//------------------
	// Create Swapchain
	m_Swapchain.m_ImageCount   = std::min(surfaceCapabilities.minImageCount + 1, surfaceCapabilities.maxImageCount);
	m_Swapchain.m_PreTransform = surfaceCapabilities.currentTransform;

	// TODO(MarcasRealAccount): Implement better system to get these variables.
	m_Swapchain.m_Format      = format.format;
	m_Swapchain.m_ColorSpace  = format.colorSpace;
	m_Swapchain.m_PresentMode = vk::PresentModeKHR::eFifo;
	m_Swapchain.m_Width       = surfaceCapabilities.currentExtent.width;
	m_Swapchain.m_Height      = surfaceCapabilities.currentExtent.height;

	m_Swapchain.m_Indices.clear();
	m_Swapchain.m_Indices.insert(m_GraphicsPresentQueueFamily->getFamilyIndex());
	if (!m_Swapchain.create())
		throw std::runtime_error("Failed to create vulkan swapchain");
	m_Device.setDebugName(m_Swapchain, "m_Swapchain");
	//------------------

	auto& swapchainImages = m_Swapchain.getImages();
	m_SwapchainImageViews.reserve(swapchainImages.size());
	m_SwapchainDepthImages.reserve(swapchainImages.size());
	m_SwapchainDepthImageViews.reserve(swapchainImages.size());
	m_Framebuffers.reserve(swapchainImages.size());
	m_ImagesInFlight.resize(swapchainImages.size(), nullptr);
	for (std::size_t i = 0; i < swapchainImages.size(); ++i)
	{
		//----------------------------
		// Create Swapchain ImageView
		auto& imageView    = m_SwapchainImageViews.emplace_back(swapchainImages[i]);
		imageView.m_Format = m_Swapchain.m_Format;
		if (!imageView.create())
			throw std::runtime_error("Failed to create vulkan image view");
		m_Device.setDebugName(imageView, "m_SwapchainImageViews[" + std::to_string(i) + ']');
		//----------------------------

		//------------------------------
		// Create Swapchain Depth Image
		auto& depthImage    = m_SwapchainDepthImages.emplace_back(m_Vma);
		depthImage.m_Format = vk::Format::eD32SfloatS8Uint;
		depthImage.m_Usage  = vk::ImageUsageFlagBits::eDepthStencilAttachment;
		depthImage.m_Width  = m_Swapchain.m_Width;
		depthImage.m_Height = m_Swapchain.m_Height;
		if (!depthImage.create())
			throw std::runtime_error("Failed to create vulkan image");
		m_Device.setDebugName(depthImage, "m_SwapchainDepthImages[" + std::to_string(i) + ']');
		//------------------------------

		//----------------------------------
		// Create Swapchain Depth ImageView
		auto& depthImageView    = m_SwapchainDepthImageViews.emplace_back(depthImage);
		depthImageView.m_Format = depthImage.m_Format;

		depthImageView.m_SubresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth | vk::ImageAspectFlagBits::eStencil;
		if (!depthImageView.create())
			throw std::runtime_error("Failed to create vulkan image view");
		m_Device.setDebugName(depthImageView, "m_SwapchainDepthImageViews[" + std::to_string(i) + ']');
		//----------------------------------

		//--------------------
		// Create Framebuffer
		auto& framebuffer = m_Framebuffers.emplace_back(m_RenderPass);
		framebuffer.m_Attachments.push_back(&imageView);
		framebuffer.m_Attachments.push_back(&depthImageView);
		framebuffer.m_Width  = m_Swapchain.m_Width;
		framebuffer.m_Height = m_Swapchain.m_Height;
		if (!framebuffer.create())
			throw std::runtime_error("Failed to create vulkan framebuffer");
		m_Device.setDebugName(framebuffer, "m_Framebuffers[" + std::to_string(i) + ']');
		//--------------------
	}

	{
		//-------------------------------------
		// Setup swapchain depth image layouts
		auto& currentCommandPool = m_CommandPools[m_CurrentFrame];
		currentCommandPool.reset();
		auto& currentCommandBuffer = *currentCommandPool.getCommandBuffer(vk::CommandBufferLevel::ePrimary, 0);
		if (currentCommandBuffer.begin())
		{
			std::vector<vk::ImageMemoryBarrier> imageMemoryBarriers(swapchainImages.size());
			for (std::size_t i = 0; i < swapchainImages.size(); ++i)
			{
				imageMemoryBarriers[i] = { vk::AccessFlagBits::eNoneKHR, vk::AccessFlagBits::eDepthStencilAttachmentRead | vk::AccessFlagBits::eDepthStencilAttachmentWrite, vk::ImageLayout::eUndefined, vk::ImageLayout::eDepthStencilAttachmentOptimal, ~0U, ~0U, m_SwapchainDepthImages[i], { vk::ImageAspectFlagBits::eDepth | vk::ImageAspectFlagBits::eStencil, 0, 1, 0, 1 } };
			}

			currentCommandBuffer.cmdPipelineBarrier(vk::PipelineStageFlagBits::eTopOfPipe, vk::PipelineStageFlagBits::eEarlyFragmentTests, {}, {}, {}, imageMemoryBarriers);
			currentCommandBuffer.end();

			m_GraphicsPresentQueue->submitCommandBuffers({ &currentCommandBuffer }, {}, {}, {}, nullptr);
			m_GraphicsPresentQueue->waitIdle();
		}
		//-------------------------------------
	}
}

void ThrowInstanceException(Graphics::Instance& instance)
{
	auto& missingLayers     = instance.getMissingLayers();
	auto& missingExtensions = instance.getMissingExtensions();
	if (!missingLayers.empty() || !missingExtensions.empty())
	{
		std::ostringstream str;
		if (!missingLayers.empty())
		{
			str << "Missing " << missingLayers.size() << " instance layers:";
			for (auto& layer : missingLayers)
				str << "\n  " << layer.m_Name << " with version: " << layer.m_Version.m_SubVersions.variant << '.' << layer.m_Version.m_SubVersions.major << '.' << layer.m_Version.m_SubVersions.minor << '.' << layer.m_Version.m_SubVersions.patch;
		}

		if (!missingExtensions.empty())
		{
			str << "Missing " << missingExtensions.size() << " instance extensions:";
			for (auto& extension : missingExtensions)
				str << "\n  " << extension.m_Name << " with version: " << extension.m_Version.m_SubVersions.variant << '.' << extension.m_Version.m_SubVersions.major << '.' << extension.m_Version.m_SubVersions.minor << '.' << extension.m_Version.m_SubVersions.patch;
		}
		throw std::runtime_error(str.str());
	}
	else
	{
		throw std::runtime_error("Failed to create vulkan instance");
	}
}
