#include "Graphics/Debug.h"
#include "Graphics/Device.h"
#include "Graphics/Instance.h"

#include <GLFW/glfw3.h>

#include <cstdlib>

#include <iostream>
#include <stdexcept>

int main(int argc, char** argv)
{
	try
	{
		// Initialize GLFW
		if (!glfwInit())
		{
			std::cerr << "GLFW failed to initialize!\n";
			return EXIT_FAILURE;
		}

		// Check for vulkan support
		if (!glfwVulkanSupported())
		{
			std::cerr << "Vulkan is not supported on this system!\n";
			return EXIT_FAILURE;
		}

		// Set window hints
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // TODO(MarcasRealAccount): Disable resizing, enable once the Vulkan Swapchain can be recreated.

		// Create window
		GLFWwindow* windowPtr = glfwCreateWindow(1280, 720, "Carbonite", nullptr, nullptr);

		// Create Graphics Instance
		Graphics::Instance instance = { "Carbonite", { 0, 0, 1, 0 }, "Carbonite", { 0, 0, 1, 0 }, VK_API_VERSION_1_0, VK_API_VERSION_1_2 };

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
						str << "\n  " << layer.m_Name << " with version: " << layer.m_Version.m_Variant << '.' << layer.m_Version.m_Major << '.' << layer.m_Version.m_Minor << '.' << layer.m_Version.m_Patch;
				}

				if (!missingExtensions.empty())
				{
					str << "Missing " << missingExtensions.size() << " instance extensions:";
					for (auto& extension : missingExtensions)
						str << "\n  " << extension.m_Name << " with version: " << extension.m_Version.m_Variant << '.' << extension.m_Version.m_Major << '.' << extension.m_Version.m_Minor << '.' << extension.m_Version.m_Patch;
				}
				throw std::runtime_error(str.str());
			}
			else
			{
				throw std::runtime_error("Failed to create vulkan instance");
			}
		}

		// Create debug if enabled
		Graphics::Debug debug = { instance };
		if (Graphics::Debug::IsEnabled())
			debug.create();

		// Create Graphics Device
		Graphics::Device device = { instance };

		device.requestExtension("VK_KHR_swapchain");

		if (!device.create())
			throw std::runtime_error("Found no suitable vulkan device");

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
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}

#if _WIN32
#undef APIENTRY
#include <Windows.h>

int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	return main(__argc, __argv);
}
#endif