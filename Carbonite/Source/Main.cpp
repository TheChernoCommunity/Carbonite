#include "Graphics/Commands/CommandPool.h"
#include "Graphics/Debug/Debug.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Device/Queue.h"
#include "Graphics/Device/Surface.h"
#include "Graphics/Instance.h"
#include "Graphics/Memory/VMA.h"
#include "Graphics/Swapchain/Swapchain.h"
#include "Graphics/Sync/Fence.h"
#include "Graphics/Sync/Semaphore.h"
#include "Log.h"

#include <GLFW/glfw3.h>

#include <cstdlib>

#include <iostream>
#include <stdexcept>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	Log::init();

	try
	{
		// Initialize GLFW
		if (!glfwInit())
		{
			Log::error("GLFW failed to initialize!");
			return EXIT_FAILURE;
		}

		// Check for vulkan support
		if (!glfwVulkanSupported())
		{
			Log::error("Vulkan is not supported on this system!");
			return EXIT_FAILURE;
		}

		// Set window hints
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // TODO(MarcasRealAccount): Disable resizing, enable once the Vulkan Swapchain can be recreated.

		// Create window
		GLFWwindow* windowPtr = glfwCreateWindow(1280, 720, "Carbonite", nullptr, nullptr);

		// Create Graphics Instance
		constexpr std::size_t MaxFramesInFlight = 2;

		Graphics::Instance    instance = { "Carbonite", { 0, 0, 1, 0 }, "Carbonite", { 0, 0, 1, 0 }, VK_API_VERSION_1_0, VK_API_VERSION_1_2 };
		Graphics::Debug       debug    = { instance };
		Graphics::Surface     surface  = { instance, windowPtr };
		Graphics::Device      device   = { surface };
		Graphics::Memory::VMA vma      = { device };

		std::vector<Graphics::CommandPool>     commandPools;
		std::vector<Graphics::Sync::Semaphore> imageAvailableSemaphores;
		std::vector<Graphics::Sync::Semaphore> renderFinishedSemaphores;
		std::vector<Graphics::Sync::Fence>     inFlightFences;

		Graphics::Swapchain swapchain = { vma };

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

		// Create debug if enabled
		if (Graphics::Debug::IsEnabled())
			debug.create();

		if (!surface.create())
			throw std::runtime_error("Failed to create vulkan surface");

		// Create Graphics Device
		device.requestExtension("VK_KHR_swapchain");
		device.requestExtension("VK_KHR_portability_subset", { 0U }, false);

		device.requestQueueFamily(1, vk::QueueFlagBits::eGraphics, true);

		if (!device.create())
			throw std::runtime_error("Found no suitable vulkan device");

		auto physicalDevice = device.getPhysicalDevice();

		auto                  graphicsPresentQueueFamily = device.getQueueFamily(vk::QueueFlagBits::eGraphics, true);
		[[maybe_unused]] auto graphicsPresentQueue       = graphicsPresentQueueFamily->getQueue(0);

		if (!vma.create())
			throw std::runtime_error("Failed to create vulkan memory allocator");

		// Create Graphics Command Pools and frame sync objects
		for (std::size_t i = 0; i < MaxFramesInFlight; ++i)
		{
			auto& commandPool = commandPools[i];

			commandPool.setQueueFamily(*graphicsPresentQueueFamily);

			if (!commandPool.create())
				throw std::runtime_error("Failed to create vulkan command pool");

			commandPool.allocateBuffers(vk::CommandBufferLevel::ePrimary, 1);

			auto& ias = imageAvailableSemaphores[i];
			if (!ias.create())
				throw std::runtime_error("Failed to create vulkan semaphore");

			auto& rfs = renderFinishedSemaphores[i];
			if (!rfs.create())
				throw std::runtime_error("Failed to create vulkan semaphore");

			auto& iff = inFlightFences[i];
			iff.setSignaled();
			if (!iff.create())
				throw std::runtime_error("Failed to create vulkan fence");
		}

		// Create swapchain

		auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface.getHandle());
		auto surfaceFormats      = physicalDevice.getSurfaceFormatsKHR(surface.getHandle());

		swapchain.m_ImageCount   = std::min(surfaceCapabilities.minImageCount + 1, surfaceCapabilities.maxImageCount);
		swapchain.m_PreTransform = surfaceCapabilities.currentTransform;
		swapchain.m_Format       = surfaceFormats[0].format;
		swapchain.m_ColorSpace   = surfaceFormats[0].colorSpace;
		swapchain.m_PresentMode  = vk::PresentModeKHR::eFifo;
		swapchain.m_Width        = surfaceCapabilities.currentExtent.width;
		swapchain.m_Height       = surfaceCapabilities.currentExtent.height;
		swapchain.m_Indices.clear();
		swapchain.m_Indices.insert(graphicsPresentQueueFamily->getFamilyIndex());
		if (!swapchain.create())
			throw std::runtime_error("Failed to create vulkan swapchain");

		//

		while (!glfwWindowShouldClose(windowPtr))
		{
			glfwPollEvents();
		}

		// Because the system is very automatic we have no need to destroy anything other than the Graphics Instance, that is if we don't need to do temporary stuff :D
		// But it will also auto destroy itself if we leave the scope. But since we have to manually destroy glfw, we have to manually call destroy before we destroy the window.

		// Destroy Graphics Instance
		instance.destroy();

		// Destroy window and terminate GLFW
		glfwDestroyWindow(windowPtr);
		glfwTerminate();

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