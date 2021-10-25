#include "Graphics/Instance.h"
#include "Graphics/Debug/Debug.h"

#include <utility>

namespace Graphics
{
	namespace Detail
	{
		InstanceLayer::InstanceLayer(std::string_view name, Version version, bool required)
		    : m_Name(name), m_Version(version), m_Required(required) {}
	} // namespace Detail

	Version                            Instance::s_CachedVersion;
	std::vector<Detail::InstanceLayer> Instance::s_CachedAvailableLayers;
	std::vector<Detail::InstanceLayer> Instance::s_CachedAvailableExtensions;

	Version Instance::GetVulkanVersion()
	{
		if (!s_CachedVersion)
		{
			if (vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"))
			{
				auto result = vk::enumerateInstanceVersion(&s_CachedVersion.m_Version);
				if (result != vk::Result::eSuccess)
					vk::throwResultException(result, "vk::enumerateInstanceVersion");
			}
			else
			{
				s_CachedVersion = VK_VERSION_1_0;
			}
		}
		return s_CachedVersion;
	}

	const std::vector<Detail::InstanceLayer>& Instance::GetAvailableLayers(bool requery)
	{
		if (requery || s_CachedAvailableLayers.empty())
		{
			s_CachedAvailableLayers.clear();
			auto properties = vk::enumerateInstanceLayerProperties();
			s_CachedAvailableLayers.reserve(properties.size());
			for (std::size_t i = 0; i < properties.size(); ++i)
			{
				auto&       property = properties[i];
				std::string layerName(property.layerName.size(), '\0');
				std::memcpy(layerName.data(), property.layerName.data(), property.layerName.size());
				auto end = layerName.find_first_of('\0');
				if (end < layerName.size())
					layerName.resize(end);

				s_CachedAvailableLayers.emplace_back(std::move(layerName), property.implementationVersion);
			}
		}
		return s_CachedAvailableLayers;
	}

	const std::vector<Detail::InstanceExtension>& Instance::GetAvailableExtensions(bool requery)
	{
		if (requery || s_CachedAvailableExtensions.empty())
		{
			s_CachedAvailableExtensions.clear();
			auto properties = vk::enumerateInstanceExtensionProperties();
			s_CachedAvailableExtensions.reserve(properties.size());
			for (std::size_t i = 0; i < properties.size(); ++i)
			{
				auto&       property = properties[i];
				std::string extensionName(property.extensionName.size(), '\0');
				std::memcpy(extensionName.data(), property.extensionName.data(), property.extensionName.size());
				auto end = extensionName.find_first_of('\0');
				if (end < extensionName.size())
					extensionName.resize(end);

				s_CachedAvailableExtensions.emplace_back(extensionName, property.specVersion);
			}
		}
		return s_CachedAvailableExtensions;
	}

	bool Instance::HasLayer(std::string_view name, Version lowestVersion)
	{
		for (auto& layer : s_CachedAvailableLayers)
			if (layer.m_Name == name && layer.m_Version > lowestVersion)
				return true;
		return false;
	}

	bool Instance::HasExtension(std::string_view name, Version lowestVersion)
	{
		for (auto& extension : s_CachedAvailableExtensions)
			if (extension.m_Name == name && extension.m_Version > lowestVersion)
				return true;
		return false;
	}

	Instance::Instance(std::string_view appName, Version appVersion, std::string_view engineName, Version engineVersion, Version minAPIVersion, Version maxAPIVersion)
	    : m_AppName(appName), m_AppVersion(appVersion), m_EngineName(engineName), m_EngineVersion(engineVersion), m_MinAPIVersion(minAPIVersion), m_MaxAPIVersion(maxAPIVersion), m_Debug(new Debug(*this)) {}

	Instance::~Instance()
	{
		if (isValid())
			destroy();
		delete m_Debug;
	}

	void Instance::requestLayer(std::string_view name, Version requiredVersion, bool required)
	{
		auto itr = std::find_if(m_Layers.begin(), m_Layers.end(), [name](const Detail::InstanceLayer& layer) -> bool
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

	void Instance::requestExtension(std::string_view name, Version requiredVersion, bool required)
	{
		auto itr = std::find_if(m_Extensions.begin(), m_Extensions.end(), [name](const Detail::InstanceExtension& extension) -> bool
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

	Version Instance::getLayerVersion(std::string_view name) const
	{
		for (auto& layer : m_EnabledLayers)
			if (layer.m_Name == name)
				return layer.m_Version;
		return {};
	}

	Version Instance::getExtensionVersion(std::string_view name) const
	{
		for (auto& extension : m_EnabledExtensions)
			if (extension.m_Name == name)
				return extension.m_Version;
		return {};
	}

	void Instance::createImpl()
	{
		Version vulkanVersion = GetVulkanVersion();
		if (vulkanVersion < m_MinAPIVersion)
			return;

		Version instanceVersion;
		if (vulkanVersion >= m_MaxAPIVersion)
			instanceVersion = m_MaxAPIVersion;
		else if (vulkanVersion >= m_MinAPIVersion)
			instanceVersion = m_MinAPIVersion;

		m_MissingLayers.clear();
		m_MissingExtensions.clear();
		GetAvailableLayers();
		for (auto& layer : m_Layers)
		{
			bool found = false;
			for (auto& availLayer : s_CachedAvailableLayers)
			{
				if (availLayer.m_Name == layer.m_Name && availLayer.m_Version > layer.m_Version)
				{
					m_EnabledLayers.push_back(availLayer);
					found = true;
					break;
				}
			}
			if (found) continue;
			if (layer.m_Required)
				m_MissingLayers.push_back(layer);
		}

		GetAvailableExtensions();
		for (auto& extension : m_Extensions)
		{
			bool found = false;
			for (auto& availExtension : s_CachedAvailableExtensions)
			{
				if (availExtension.m_Name == extension.m_Name && availExtension.m_Version > extension.m_Version)
				{
					m_EnabledExtensions.push_back(availExtension);
					found = true;
					break;
				}
			}
			if (found) continue;
			if (extension.m_Required)
				m_MissingExtensions.push_back(extension);
		}

		if (Debug::IsEnabled())
		{
			bool found = false;
			for (auto& availLayer : s_CachedAvailableLayers)
			{
				if (availLayer.m_Name == "VK_LAYER_KHRONOS_validation")
				{
					m_EnabledLayers.push_back(availLayer);
					found = true;
					break;
				}
			}
			if (!found)
			{
				Debug::Disable();
			}
			else
			{
				found = false;
				for (auto& availExtension : s_CachedAvailableExtensions)
				{
					if (availExtension.m_Name == "VK_EXT_debug_utils")
					{
						m_EnabledExtensions.push_back(availExtension);
						found = true;
						break;
					}
				}
				if (!found)
					Debug::Disable();
			}
		}

		if (!m_MissingLayers.empty() || !m_MissingExtensions.empty())
			return;

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

		vk::ApplicationInfo appInfo = { m_AppName.c_str(), m_AppVersion, m_EngineName.c_str(), m_EngineVersion, instanceVersion };

		vk::InstanceCreateInfo createInfo = { {}, &appInfo, useLayers, useExtensions };

		vk::DebugUtilsMessengerCreateInfoEXT debugCreateInfo;

		if (Debug::IsEnabled())
		{
			Debug::PopulateCreateInfo(debugCreateInfo);
			createInfo.pNext = &debugCreateInfo;
		}

		m_Handle     = vk::createInstance(createInfo);
		m_ApiVersion = instanceVersion;
	}

	bool Instance::destroyImpl()
	{
		m_Handle.destroy();
		m_EnabledLayers.clear();
		m_EnabledExtensions.clear();
		return true;
	}
} // namespace Graphics