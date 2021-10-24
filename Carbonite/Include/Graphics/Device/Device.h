#pragma once

#include "Surface.h"

namespace Graphics
{
	struct QueueFamily;

	struct DeviceLayer
	{
	public:
		DeviceLayer(std::string_view name, Version version, bool required = true);

	public:
		std::string m_Name;
		Version     m_Version;
		bool        m_Required;
	};

	using DeviceExtension = DeviceLayer;

	struct DeviceQueueFamilyRequest
	{
	public:
		DeviceQueueFamilyRequest(std::uint32_t count, vk::QueueFlags queueFlags, bool supportsPresent = false, bool required = true);

	public:
		std::uint32_t  m_Count;
		vk::QueueFlags m_QueueFlags;

		bool m_SupportsPresent;
		bool m_Required;
	};

	struct Device : public Handle<vk::Device>
	{
	public:
		Device(Surface& surface);
		~Device();

		void requestLayer(std::string_view name, Version requiredVersion = {}, bool required = true);
		void requestExtension(std::string_view name, Version requiredVersion = {}, bool required = true);

		void requestQueueFamily(std::uint32_t count, vk::QueueFlags queueFlags, bool supportsPresent = false, bool required = true);

		Version getLayerVersion(std::string_view name) const;
		Version getExtensionVersion(std::string_view name) const;

		auto getSurface() const
		{
			return m_Surface;
		}
		auto& getPhysicalDevice() const
		{
			return m_PhysicalDevice;
		}

		auto& getEnabledLayers() const
		{
			return m_EnabledLayers;
		}
		auto& getEnabledExtensions() const
		{
			return m_EnabledExtensions;
		}

		QueueFamily* getQueueFamily(vk::QueueFlags queueFlags, bool supportsPresent = false) const;
		auto&        getQueueFamilies() const
		{
			return m_QueueFamilies;
		}

		bool isLayerEnabled(std::string_view name) const
		{
			return getLayerVersion(name);
		}
		bool isExtensionEnabled(std::string_view name) const
		{
			return getExtensionVersion(name);
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	protected:
		std::vector<DeviceLayer>     m_EnabledLayers;
		std::vector<DeviceExtension> m_EnabledExtensions;

		std::vector<QueueFamily> m_QueueFamilies;

	private:
		Surface* m_Surface;

		vk::PhysicalDevice m_PhysicalDevice = nullptr;

		std::vector<DeviceLayer>     m_Layers;
		std::vector<DeviceExtension> m_Extensions;

		std::vector<DeviceQueueFamilyRequest> m_QueueRequests;
	};
} // namespace Graphics