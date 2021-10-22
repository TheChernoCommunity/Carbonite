#pragma once

#include "Common.h"

#include <string>
#include <string_view>

namespace Graphics
{
	struct InstanceLayer
	{
	public:
		InstanceLayer(std::string_view name, Version version, bool required = true);

	public:
		std::string m_Name;
		Version     m_Version;
		bool        m_Required;
	};

	using InstanceExtension = InstanceLayer;

	struct Instance : public Handle<vk::Instance>
	{
	public:
		static Version                               GetVulkanVersion();
		static const std::vector<InstanceLayer>&     GetAvailableLayers(bool requery = false);
		static const std::vector<InstanceExtension>& GetAvailableExtensions(bool requery = false);
		static bool                                  HasLayer(std::string_view name, Version lowestVersion = {});
		static bool                                  HasExtension(std::string_view name, Version lowestVersion = {});

	private:
		static Version                    s_CachedVersion;
		static std::vector<InstanceLayer> s_CachedAvailableLayers;
		static std::vector<InstanceLayer> s_CachedAvailableExtensions;

	public:
		Instance(std::string_view appName, Version appVersion, std::string_view engineName, Version engineVersion, Version minAPIVersion = {}, Version maxAPIVersion = { ~0U });
		~Instance();

		void requestLayer(std::string_view name, Version requiredVersion = {}, bool required = true);
		void requestExtension(std::string_view name, Version requiredVersion = {}, bool required = true);

		Version getLayerVersion(std::string_view name) const;
		Version getExtensionVersion(std::string_view name) const;

		auto& getAppName() const
		{
			return m_AppName;
		}
		auto getAppVersion() const
		{
			return m_AppVersion;
		}
		auto& getEngineName() const
		{
			return m_EngineName;
		}
		auto getEngineVersion() const
		{
			return m_EngineVersion;
		}

		auto& getEnabledLayers() const
		{
			return m_EnabledLayers;
		}
		auto& getEnabledExtensions() const
		{
			return m_EnabledExtensions;
		}
		auto& getMissingLayers() const
		{
			return m_MissingLayers;
		}
		auto& getMissingExtensions() const
		{
			return m_MissingExtensions;
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
		std::string m_AppName;
		Version     m_AppVersion;
		std::string m_EngineName;
		Version     m_EngineVersion;
		Version     m_MinAPIVersion;
		Version     m_MaxAPIVersion;

		std::vector<InstanceLayer>     m_EnabledLayers;
		std::vector<InstanceExtension> m_EnabledExtensions;

	private:
		std::vector<InstanceLayer>     m_Layers;
		std::vector<InstanceExtension> m_Extensions;
		std::vector<InstanceLayer>     m_MissingLayers;
		std::vector<InstanceExtension> m_MissingExtensions;
	};
} // namespace Graphics