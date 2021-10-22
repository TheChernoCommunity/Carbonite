#pragma once

#include "Instance.h"

namespace Graphics
{
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

	struct Device : public Handle<vk::Device>
	{
	public:
		Device(Instance& instance);
		~Device();

		void requestLayer(std::string_view name, Version requiredVersion = {}, bool required = true);
		void requestExtension(std::string_view name, Version requiredVersion = {}, bool required = true);

		Version getLayerVersion(std::string_view name) const;
		Version getExtensionVersion(std::string_view name) const;

		auto getInstance() const
		{
			return m_Instance;
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

	private:
		Instance* m_Instance;

		vk::PhysicalDevice m_PhysicalDevice = nullptr;

		std::vector<DeviceLayer>     m_Layers;
		std::vector<DeviceExtension> m_Extensions;
	};
} // namespace Graphics