#include <array>

#include "Graphics/Debug/Debug.h"
#include "Graphics/Device.h"

namespace Graphics
{
	DeviceLayer::DeviceLayer(std::string_view name, Version version, bool required)
	    : m_Name(name), m_Version(version), m_Required(required) {}

	Device::Device(Surface& surface)
	    : Handle({ &surface }), m_Surface(&surface)
	{
	}

	Device::~Device()
	{
		if (isCreated())
			destroy();
	}

	void Device::requestLayer(std::string_view name, Version requiredVersion, bool required)
	{
		auto itr = std::find_if(m_Layers.begin(), m_Layers.end(), [name](const DeviceLayer& layer) -> bool
		                        { return layer.m_Name == name; });

		if (itr != m_Layers.end())
		{
			auto& layer = *itr;
			if (requiredVersion < layer.m_Version)
				layer.m_Version = requiredVersion;
			layer.m_Required = required;
		}
		else
		{
			m_Layers.emplace_back(name, requiredVersion, required);
		}
	}

	void Device::requestExtension(std::string_view name, Version requiredVersion, bool required)
	{
		auto itr = std::find_if(m_Extensions.begin(), m_Extensions.end(), [name](const DeviceExtension& extension) -> bool
		                        { return extension.m_Name == name; });

		if (itr != m_Extensions.end())
		{
			auto& extension = *itr;
			if (requiredVersion < extension.m_Version)
				extension.m_Version = requiredVersion;
			extension.m_Required = required;
		}
		else
		{
			m_Extensions.emplace_back(name, requiredVersion, required);
		}
	}

	Version Device::getLayerVersion(std::string_view name) const
	{
		for (auto& layer : m_EnabledLayers)
			if (layer.m_Name == name)
				return layer.m_Version;
		return {};
	}

	Version Device::getExtensionVersion(std::string_view name) const
	{
		for (auto& extension : m_EnabledExtensions)
			if (extension.m_Name == name)
				return extension.m_Version;
		return {};
	}

	void Device::createImpl()
	{
		[[maybe_unused]] auto& surfaceHandle   = m_Surface->getHandle();
		auto&                  instanceHandle  = m_Surface->getInstance()->getHandle();
		auto                   physicalDevices = instanceHandle.enumeratePhysicalDevices();

		vk::PhysicalDevice bestPhysicalDevice = nullptr;
		std::size_t        bestScore          = 0;

		for (auto& physicalDevice : physicalDevices)
		{
			std::size_t score             = 1;
			bool        missingLayers     = false;
			bool        missingExtensions = false;

			auto availableLayers = physicalDevice.enumerateDeviceLayerProperties();
			for (auto& layer : m_Layers)
			{
				bool found = false;
				for (auto& availLayer : availableLayers)
				{
					std::string layerName(availLayer.layerName.size(), '\0');
					std::memcpy(layerName.data(), availLayer.layerName.data(), availLayer.layerName.size());
					auto end = layerName.find_first_of('\0');
					if (end < layerName.size())
						layerName.resize(end);

					if (layerName == layer.m_Name && availLayer.implementationVersion > layer.m_Version)
					{
						if (!layer.m_Required) ++score;
						found = true;
						break;
					}
				}
				if (found) continue;
				if (layer.m_Required)
				{
					missingLayers = true;
					break;
				}
			}
			if (missingLayers) continue;

			auto availableExtensions = physicalDevice.enumerateDeviceExtensionProperties();
			for (auto& extension : m_Extensions)
			{
				bool found = false;
				for (auto& availExtension : availableExtensions)
				{
					std::string extensionName(availExtension.extensionName.size(), '\0');
					std::memcpy(extensionName.data(), availExtension.extensionName.data(), availExtension.extensionName.size());
					auto end = extensionName.find_first_of('\0');
					if (end < extensionName.size())
						extensionName.resize(end);

					if (extensionName == extension.m_Name && availExtension.specVersion > extension.m_Version)
					{
						if (!extension.m_Required) ++score;
						found = true;
						break;
					}
				}
				if (found) continue;
				if (extension.m_Required)
				{
					missingExtensions = true;
					break;
				}
			}
			if (missingExtensions) continue;

			// Check if the physical device supports a graphics queue, if not move on to the next physical device. If so
			auto queueFamilyProperties = physicalDevice.getQueueFamilyProperties();

			bool foundGraphicsFamily = false;

			for (const auto& queueFamilyProperty : queueFamilyProperties)
			{
				if (queueFamilyProperty.queueFlags | vk::QueueFlagBits::eGraphics)
				{
					foundGraphicsFamily = true;
					break;
				}
			}

			if (!foundGraphicsFamily) continue;

			auto                  properties = physicalDevice.getProperties();
			[[maybe_unused]] auto features   = physicalDevice.getFeatures(); // TODO(MarcasRealAccount): Unused for now, implement feature check for required and wanted features.

			switch (properties.deviceType)
			{
			case vk::PhysicalDeviceType::eCpu:
				break;
			case vk::PhysicalDeviceType::eOther:
				score *= 2;
				break;
			case vk::PhysicalDeviceType::eVirtualGpu:
				score *= 3;
				break;
			case vk::PhysicalDeviceType::eIntegratedGpu:
				score *= 4;
				break;
			case vk::PhysicalDeviceType::eDiscreteGpu:
				score *= 5;
				break;
			}

			if (score > bestScore)
			{
				bestScore          = score;
				bestPhysicalDevice = physicalDevice;
			}
		}

		if (!bestPhysicalDevice)
			return;

		m_PhysicalDevice     = bestPhysicalDevice;
		auto availableLayers = m_PhysicalDevice.enumerateDeviceLayerProperties();
		for (auto& layer : m_Layers)
		{
			bool found = false;
			for (auto& availLayer : availableLayers)
			{
				std::string layerName(availLayer.layerName.size(), '\0');
				std::memcpy(layerName.data(), availLayer.layerName.data(), availLayer.layerName.size());
				auto end = layerName.find_first_of('\0');
				if (end < layerName.size())
					layerName.resize(end);

				if (layerName == layer.m_Name && availLayer.implementationVersion > layer.m_Version)
				{
					m_EnabledLayers.push_back({ layerName, availLayer.implementationVersion });
					found = true;
					break;
				}
			}
			if (found) continue;
		}

		auto availableExtensions = m_PhysicalDevice.enumerateDeviceExtensionProperties();
		for (auto& extension : m_Extensions)
		{
			bool found = false;
			for (auto& availExtension : availableExtensions)
			{
				std::string extensionName(availExtension.extensionName.size(), '\0');
				std::memcpy(extensionName.data(), availExtension.extensionName.data(), availExtension.extensionName.size());
				auto end = extensionName.find_first_of('\0');
				if (end < extensionName.size())
					extensionName.resize(end);

				if (extensionName == extension.m_Name && availExtension.specVersion > extension.m_Version)
				{
					m_EnabledExtensions.push_back({ extensionName, availExtension.specVersion });
					found = true;
					break;
				}

				// https://vulkan.lunarg.com/doc/view/1.2.189.0/mac/1.2-extensions/vkspec.html#VUID-VkDeviceCreateInfo-pProperties-04451
				if (extensionName == "VK_KHR_portability_subset")
				{
					m_EnabledExtensions.push_back({ extensionName, availExtension.specVersion });
					break;
				}
			}
			if (found) continue;
		}

		if (Debug::IsEnabled())
		{
			for (auto& availLayer : availableLayers)
			{
				std::string layerName(availLayer.layerName.size(), '\0');
				std::memcpy(layerName.data(), availLayer.layerName.data(), availLayer.layerName.size());
				auto end = layerName.find_first_of('\0');
				if (end < layerName.size())
					layerName.resize(end);

				if (layerName == "VK_LAYER_KHRONOS_validation")
				{
					m_EnabledLayers.push_back({ layerName, availLayer.implementationVersion });
					break;
				}
			}
		}

		auto queueFamilyProperties = m_PhysicalDevice.getQueueFamilyProperties();

		for (unsigned i = 0; i < queueFamilyProperties.size(); i++)
		{
			if (queueFamilyProperties[0].queueFlags | vk::QueueFlagBits::eGraphics)
			{
				m_queues.graphicsFamilyIndex = i;
				break;
			}
		}

		std::array<float, 1> queuePriorities = { 1 };

		std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos = { vk::DeviceQueueCreateInfo()
			                                                            .setQueueFamilyIndex(m_queues.graphicsFamilyIndex)
			                                                            .setQueueCount(1)
			                                                            .setQueuePriorities(queuePriorities) };
		vk::PhysicalDeviceFeatures             enabledFeatures;

		std::vector<const char*> useLayers(m_EnabledLayers.size());
		std::vector<const char*> useExtensions(m_EnabledExtensions.size());

		for (std::size_t i = 0; i < useLayers.size(); ++i)
		{
			auto& layer = m_EnabledLayers[i];
			char* buf   = new char[layer.m_Name.size() + 1] { 0 };
			std::memcpy(buf, layer.m_Name.c_str(), layer.m_Name.size());
			useLayers[i] = buf;
		}

		for (std::size_t i = 0; i < useExtensions.size(); ++i)
		{
			auto& extension = m_EnabledExtensions[i];
			char* buf       = new char[extension.m_Name.size() + 1] { 0 };
			std::memcpy(buf, extension.m_Name.c_str(), extension.m_Name.size());
			useExtensions[i] = buf;
		}

		vk::DeviceCreateInfo createInfo = { {}, queueCreateInfos, useLayers, useExtensions, &enabledFeatures };

		m_Handle               = m_PhysicalDevice.createDevice(createInfo);
		m_queues.graphicsQueue = m_Handle.getQueue(m_queues.graphicsFamilyIndex, 0);
	}

	bool Device::destroyImpl()
	{
		m_Handle.destroy();
		m_EnabledLayers.clear();
		m_EnabledExtensions.clear();
		return true;
	}
} // namespace Graphics