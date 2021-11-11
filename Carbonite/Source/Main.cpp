#include "PCH.h"

#include "Asset.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
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
#include "Graphics/Pipeline/Pipeline.h"
#include "Graphics/Pipeline/RenderPass.h"
#include "Graphics/Shader.h"
#include "Graphics/Swapchain/Swapchain.h"
#include "Graphics/Sync/Fence.h"
#include "Graphics/Sync/Semaphore.h"
#include "Graphics/Window.h"
#include "Log.h"

#include <GLFW/glfw3.h>

#include <cstdlib>

#include <iostream>
#include <stdexcept>

class Handler : public EventHandler
{
	void onEvent(std::shared_ptr<Event> e) override
	{
		if (e->IsInCategory(Event::Category::MouseButton))
		{
			Log::info(e->ToString());
		}
	}
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	try
	{
		//Asset license("LICENSE");
		//Log::info(license.data.get());

		Handler handler;

		// Create Graphics Instance
		constexpr std::size_t MaxFramesInFlight = 2;

		Graphics::Instance instance = { "Carbonite", { 0, 0, 1, 0 }, "Carbonite", { 0, 0, 1, 0 }, VK_API_VERSION_1_0, VK_API_VERSION_1_2 };

		Graphics::Window window = { instance, "Carbonite" };

		Graphics::Surface     surface = { window };
		Graphics::Device      device  = { surface };
		Graphics::Memory::VMA vma     = { device };
		Graphics::Shader      vert    = { device, { "Carbonite/Assets/test.vert" } };
		Graphics::Shader      frag    = { device, { "Carbonite/Assets/test.frag" } };

		// Passing Shader by value creates issues.
		std::vector<Graphics::Shader*> shaders { &vert, &frag };

		std::vector<Graphics::CommandPool>
		                                       commandPools;
		std::vector<Graphics::Sync::Semaphore> imageAvailableSemaphores;
		std::vector<Graphics::Sync::Semaphore> renderFinishedSemaphores;
		std::vector<Graphics::Sync::Fence>     inFlightFences;
		[[maybe_unused]] std::uint32_t         currentFrame = 0;

		Graphics::Swapchain  swapchain  = { vma };
		Graphics::RenderPass renderPass = { device };
		Graphics::Pipeline   pipeline   = { swapchain, renderPass, shaders };

		std::vector<Graphics::ImageView>    imageViews;
		std::vector<Graphics::Image>        swapchainDepthImages;
		std::vector<Graphics::ImageView>    swapchainDepthImageViews;
		std::vector<Graphics::Framebuffer>  framebuffers;
		std::vector<Graphics::Sync::Fence*> imagesInFlight;
		[[maybe_unused]] std::uint32_t      currentImage = 0;

		commandPools.reserve(MaxFramesInFlight);
		for (std::size_t i = 0; i < MaxFramesInFlight; ++i)
			commandPools.emplace_back(device);
		imageAvailableSemaphores.reserve(MaxFramesInFlight);
		for (std::size_t i = 0; i < MaxFramesInFlight; ++i)
			imageAvailableSemaphores.emplace_back(device);
		renderFinishedSemaphores.reserve(MaxFramesInFlight);
		for (std::size_t i = 0; i < MaxFramesInFlight; ++i)
			renderFinishedSemaphores.emplace_back(device);
		inFlightFences.reserve(MaxFramesInFlight);
		for (std::size_t i = 0; i < MaxFramesInFlight; ++i)
			inFlightFences.emplace_back(device);

		std::uint32_t glfwExtensionCount;
		const char**  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		for (std::size_t i = 0; i < glfwExtensionCount; ++i)
			instance.requestExtension(glfwExtensions[i]);

		if (!instance.create())
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

		window.create();

		Event::addWindow(window.getHandle());

		// Create debug if enabled
		if (Graphics::Debug::IsEnabled())
			instance.getDebug().create();

		if (!surface.create())
			throw std::runtime_error("Failed to create vulkan surface");

		// Create Graphics Device
		device.requestExtension("VK_KHR_swapchain");
		device.requestExtension("VK_KHR_portability_subset", { 0U }, false);

		device.requestQueueFamily(1, vk::QueueFlagBits::eGraphics, true);

		if (!device.create())
			throw std::runtime_error("Found no suitable vulkan device");

		vert.create();
		frag.create();

		auto physicalDevice = device.getPhysicalDevice();

		auto&                  graphicsPresentQueueFamily = *device.getQueueFamily(vk::QueueFlagBits::eGraphics, true);
		[[maybe_unused]] auto& graphicsPresentQueue       = *graphicsPresentQueueFamily.getQueue(0);
		device.setDebugName(graphicsPresentQueue, "graphicsPresentQueue");

		if (!vma.create())
			throw std::runtime_error("Failed to create vulkan memory allocator");

		// Create Graphics Command Pools and frame sync objects
		for (std::size_t i = 0; i < MaxFramesInFlight; ++i)
		{
			auto& commandPool = commandPools[i];

			commandPool.setQueueFamily(graphicsPresentQueueFamily);

			if (!commandPool.create())
				throw std::runtime_error("Failed to create vulkan command pool");
			device.setDebugName(commandPool, "commandPools_" + std::to_string(i));

			commandPool.allocateBuffers(vk::CommandBufferLevel::ePrimary, 1);

			auto& ias = imageAvailableSemaphores[i];
			if (!ias.create())
				throw std::runtime_error("Failed to create vulkan semaphore");
			device.setDebugName(ias, "imageAvailableSemaphores_" + std::to_string(i));

			auto& rfs = renderFinishedSemaphores[i];
			if (!rfs.create())
				throw std::runtime_error("Failed to create vulkan semaphore");
			device.setDebugName(rfs, "renderFinishedSemaphores_" + std::to_string(i));

			auto& iff = inFlightFences[i];
			iff.setSignaled();
			if (!iff.create())
				throw std::runtime_error("Failed to create vulkan fence");
			device.setDebugName(iff, "inFlightFences_" + std::to_string(i));
		}

		// Create swapchain
		imageViews.clear();
		swapchainDepthImageViews.clear();
		swapchainDepthImages.clear();
		framebuffers.clear();

		auto oldFormat = swapchain.m_Format;

		// TODO(MarcasRealAccount): Implement better system to get these variables.
		auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface.getHandle());
		auto surfaceFormats      = physicalDevice.getSurfaceFormatsKHR(surface.getHandle());
		auto format              = surfaceFormats[0];

		if (oldFormat != format.format)
		{
			renderPass.m_Attachments.clear();
			renderPass.m_Subpasses.clear();
			renderPass.m_Dependencies.clear();

			Graphics::RenderPassAttachment colorAttachment;
			colorAttachment.m_Format = format.format;
			renderPass.m_Attachments.push_back(colorAttachment);

			Graphics::RenderPassAttachment depthAttachment;
			depthAttachment.m_Format         = vk::Format::eD32SfloatS8Uint;
			depthAttachment.m_StoreOp        = vk::AttachmentStoreOp::eDontCare;
			depthAttachment.m_StencilLoadOp  = vk::AttachmentLoadOp::eClear;
			depthAttachment.m_StencilStoreOp = vk::AttachmentStoreOp::eDontCare;
			depthAttachment.m_FinalLayout    = vk::ImageLayout::eDepthStencilAttachmentOptimal;
			renderPass.m_Attachments.push_back(depthAttachment);

			Graphics::RenderPassSubpass       subpass;
			Graphics::RenderPassAttachmentRef colorAttachmentRef;
			colorAttachmentRef.m_Attachment = 0;
			colorAttachmentRef.m_Layout     = vk::ImageLayout::eColorAttachmentOptimal;
			subpass.m_ColorAttachmentRefs.push_back(colorAttachmentRef);
			subpass.m_UseDepthStencilAttachment           = true;
			subpass.m_DepthStencilAttachment.m_Attachment = 1;
			subpass.m_DepthStencilAttachment.m_Layout     = vk::ImageLayout::eDepthStencilAttachmentOptimal;
			renderPass.m_Subpasses.push_back(subpass);

			Graphics::RenderPassSubpassDependency dependency;
			dependency.m_SrcSubpass    = ~0U;
			dependency.m_DstSubpass    = 0;
			dependency.m_SrcStageMask  = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
			dependency.m_SrcAccessMask = vk::AccessFlagBits::eNoneKHR;
			dependency.m_DstStageMask  = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
			dependency.m_DstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eDepthStencilAttachmentWrite;
			renderPass.m_Dependencies.push_back(dependency);

			if (!renderPass.create()) throw std::runtime_error("Failed to create vulkan renderpass");
			device.setDebugName(renderPass, "RenderPass");
		}

		swapchain.m_ImageCount   = std::min(surfaceCapabilities.minImageCount + 1, surfaceCapabilities.maxImageCount);
		swapchain.m_PreTransform = surfaceCapabilities.currentTransform;
		swapchain.m_Format       = format.format;
		swapchain.m_ColorSpace   = format.colorSpace;
		swapchain.m_PresentMode  = vk::PresentModeKHR::eFifo;
		swapchain.m_Width        = surfaceCapabilities.currentExtent.width;
		swapchain.m_Height       = surfaceCapabilities.currentExtent.height;
		swapchain.m_Indices.clear();
		swapchain.m_Indices.insert(graphicsPresentQueueFamily.getFamilyIndex());
		if (!swapchain.create())
			throw std::runtime_error("Failed to create vulkan swapchain");
		device.setDebugName(swapchain, "Swapchain");

		pipeline.create();

		auto& swapchainImages = swapchain.getImages();
		imageViews.reserve(swapchainImages.size());
		swapchainDepthImages.reserve(swapchainImages.size());
		swapchainDepthImageViews.reserve(swapchainImages.size());
		framebuffers.reserve(swapchainImages.size());
		for (std::size_t i = 0; i < swapchainImages.size(); ++i)
		{
			auto& imageView    = imageViews.emplace_back(swapchainImages[i]);
			imageView.m_Format = swapchain.m_Format;
			if (!imageView.create())
				throw std::runtime_error("Failed to create vulkan imageview");
			device.setDebugName(imageView, "imageViews_" + std::to_string(i));

			auto& depthImage    = swapchainDepthImages.emplace_back(vma);
			depthImage.m_Format = vk::Format::eD32SfloatS8Uint;
			depthImage.m_Usage  = vk::ImageUsageFlagBits::eDepthStencilAttachment;
			depthImage.m_Width  = swapchain.m_Width;
			depthImage.m_Height = swapchain.m_Height;
			if (!depthImage.create())
				throw std::runtime_error("Failed to create vulkan image");
			device.setDebugName(depthImage, "swapchainDepthImages_" + std::to_string(i));

			auto& depthImageView    = swapchainDepthImageViews.emplace_back(depthImage);
			depthImageView.m_Format = depthImage.m_Format;

			depthImageView.m_SubresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth | vk::ImageAspectFlagBits::eStencil;
			if (!depthImageView.create())
				throw std::runtime_error("Failed to create vulkan imageview");
			device.setDebugName(depthImageView, "swapchainDepthImageViews_" + std::to_string(i));

			auto& framebuffer = framebuffers.emplace_back(renderPass);
			framebuffer.m_Attachments.push_back(&imageView);
			framebuffer.m_Attachments.push_back(&depthImageView);
			framebuffer.m_Width  = swapchain.m_Width;
			framebuffer.m_Height = swapchain.m_Height;
			if (!framebuffer.create())
				throw std::runtime_error("Failed to create vulkan framebuffer");
			device.setDebugName(framebuffer, "framebuffers_" + std::to_string(i));
		}

		imagesInFlight.clear();
		imagesInFlight.resize(swapchainImages.size(), nullptr);

		{
			auto& currentCommandPool = commandPools[currentFrame];
			currentCommandPool.reset();
			auto& currentCommandBuffer = *currentCommandPool.getCommandBuffer(vk::CommandBufferLevel::ePrimary, 0);
			if (currentCommandBuffer.begin())
			{
				std::vector<vk::ImageMemoryBarrier> imageMemoryBarriers(swapchainImages.size());
				for (std::size_t i = 0; i < swapchainImages.size(); ++i)
				{
					imageMemoryBarriers[i] = { vk::AccessFlagBits::eNoneKHR, vk::AccessFlagBits::eDepthStencilAttachmentRead | vk::AccessFlagBits::eDepthStencilAttachmentWrite, vk::ImageLayout::eUndefined, vk::ImageLayout::eDepthStencilAttachmentOptimal, ~0U, ~0U, swapchainDepthImages[i], { vk::ImageAspectFlagBits::eDepth | vk::ImageAspectFlagBits::eStencil, 0, 1, 0, 1 } };
				}

				currentCommandBuffer.cmdPipelineBarrier(vk::PipelineStageFlagBits::eTopOfPipe, vk::PipelineStageFlagBits::eEarlyFragmentTests, {}, {}, {}, imageMemoryBarriers);
				currentCommandBuffer.end();

				graphicsPresentQueue.submitCommandBuffers({ &currentCommandBuffer }, {}, {}, {}, nullptr);
				graphicsPresentQueue.waitIdle();
			}
		}

		vk::Viewport viewport = { 0, 0, static_cast<float>(swapchain.m_Width), static_cast<float>(swapchain.m_Height), 0, 1 };

		std::vector<vk::Viewport> viewports = { viewport };

		vk::Rect2D scissor = { { 0, 0 }, surfaceCapabilities.currentExtent };

		std::vector<vk::Rect2D> scissors = { scissor };

		while (!glfwWindowShouldClose(*window))
		{
			glfwPollEvents();

			Event::push(std::make_shared<AppUpdateEvent>());
			Event::push(std::make_shared<AppRenderEvent>());

			Event::dispatchEvents();

			if (glfwGetWindowAttrib(*window, GLFW_ICONIFIED))
				continue;

			// Begin frame
			// TODO(MarcasRealAccount): Check if swapchain should be recreated and recreate it

			Graphics::Sync::Fence& iff = inFlightFences[currentFrame];
			iff.waitFor(~0ULL);
			iff.reset();

			vk::Result result = swapchain.acquireNextImage(~0U, &imageAvailableSemaphores[currentFrame], nullptr, currentImage);
			if (result == vk::Result::eErrorOutOfDateKHR)
			{
				// recreate swapchain and restart frame
				// createSwapchain();
				continue;
			}
			else if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR)
			{
				throw std::runtime_error("Failed to acquire next Vulkan Swapchain image");
			}

			if (imagesInFlight[currentImage])
				imagesInFlight[currentImage]->waitFor(~0ULL);
			imagesInFlight[currentImage] = &inFlightFences[currentFrame];

			commandPools[currentFrame].reset();
			inFlightFences[currentFrame].reset();

			// -Begin frame

			auto& currentCommandPool   = commandPools[currentFrame];
			auto& currentCommandBuffer = *currentCommandPool.getCommandBuffer(vk::CommandBufferLevel::ePrimary, 0);
			if (currentCommandBuffer.begin())
			{
				currentCommandBuffer.cmdBeginRenderPass(renderPass, framebuffers[currentImage], { { 0, 0 }, { swapchain.m_Width, swapchain.m_Height } }, { vk::ClearColorValue(std::array<float, 4> { 0.1f, 0.1f, 0.1f, 1.0f }), vk::ClearDepthStencilValue(1.0f, 0) });
				currentCommandBuffer.cmdBindPipeline(pipeline);

				currentCommandBuffer.cmdSetViewport(viewports);
				currentCommandBuffer.cmdSetScissor(scissors);

				currentCommandBuffer.draw();
				currentCommandBuffer.cmdEndRenderPass();
				currentCommandBuffer.end();
			}

			// End frame

			auto&                                 commandBufferLevels = commandPools[currentFrame].getCommandBuffers();
			std::vector<Graphics::CommandBuffer*> submitCommandBuffers;
			std::size_t                           submitCommandBufferCount = 0;
			for (auto& level : commandBufferLevels)
				submitCommandBufferCount += level.second.size();
			submitCommandBuffers.resize(submitCommandBufferCount);
			std::size_t submitCommandBufferI = 0;
			for (auto& level : commandBufferLevels)
			{
				for (auto& buf : level.second)
				{
					submitCommandBuffers[submitCommandBufferI] = const_cast<Graphics::CommandBuffer*>(&buf);
					++submitCommandBufferI;
				}
			}

			graphicsPresentQueue.submitCommandBuffers(submitCommandBuffers, { &imageAvailableSemaphores[currentFrame] }, { &renderFinishedSemaphores[currentFrame] }, { vk::PipelineStageFlagBits::eColorAttachmentOutput }, &inFlightFences[currentFrame]);
			result = graphicsPresentQueue.present({ &swapchain }, { currentImage }, { &renderFinishedSemaphores[currentFrame] })[0];
			if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR)
			{
				// Recreate swapchain
				// createSwapchain();
				continue;
			}
			else if (result != vk::Result::eSuccess)
			{
				throw std::runtime_error("Failed to present to Vulkan Swapchain");
			}

			graphicsPresentQueue.waitIdle();

			currentFrame = (currentFrame + 1) % MaxFramesInFlight;
			// -End frame
		}

		// Because the system is very automatic we have no need to destroy anything other than the Graphics Instance, that is if we don't need to do temporary stuff :D
		// But it will also auto destroy itself if we leave the scope. But since we have to manually destroy glfw, we have to manually call destroy before we destroy the window.

		// Destroy Graphics Instance
		instance.destroy();

		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		Log::critical(e.what());
		return EXIT_FAILURE;
	}
}

#if _WIN32
#undef APIENTRY
#include <Windows.h>

int WinMain([[maybe_unused]] _In_ HINSTANCE hInstance, [[maybe_unused]] _In_opt_ HINSTANCE hPrevInstance, [[maybe_unused]] _In_ LPSTR lpCmdLine, [[maybe_unused]] _In_ int nShowCmd)
{
	return main(__argc, __argv);
}
#endif
