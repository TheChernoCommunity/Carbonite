#pragma once

#include <string>

#include <vulkan/vulkan.hpp>

#include "Asset.h"
#include "Device/Device.h"
#include "Graphics/Common.h"

namespace Graphics
{
	class Shader : public Handle<vk::ShaderModule, true, false>
	{
	public:
		Shader(Device& device, const Asset asset);
		Shader(Device& device, const std::string& source, const ShaderType type);

		void setSourceStr(const std::string& source);

		ShaderType getType() const;

		~Shader();

	private:
		Device&     m_device;
		std::string m_sourceStr;
		ShaderType  m_type;

		virtual void createImpl() override;
		virtual bool destroyImpl() override;
	};

} // namespace Graphics
