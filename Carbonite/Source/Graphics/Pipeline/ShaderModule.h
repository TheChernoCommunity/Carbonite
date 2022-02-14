#pragma once

#include "Graphics/Common.h"

#include <string>

namespace Graphics
{
	enum class EShaderType : VkShaderStageFlags
	{
		Vertex         = static_cast<VkShaderStageFlags>(vk::ShaderStageFlagBits::eVertex),
		TessControl    = static_cast<VkShaderStageFlags>(vk::ShaderStageFlagBits::eTessellationControl),
		TessEvaluation = static_cast<VkShaderStageFlags>(vk::ShaderStageFlagBits::eTessellationEvaluation),
		Geometry       = static_cast<VkShaderStageFlags>(vk::ShaderStageFlagBits::eGeometry),
		Fragment       = static_cast<VkShaderStageFlags>(vk::ShaderStageFlagBits::eFragment),
		Compute        = static_cast<VkShaderStageFlags>(vk::ShaderStageFlagBits::eCompute),
		RTRayGen       = static_cast<VkShaderStageFlags>(vk::ShaderStageFlagBits::eRaygenKHR),
		RTAnyHit       = static_cast<VkShaderStageFlags>(vk::ShaderStageFlagBits::eAnyHitKHR),
		RTClosestHit   = static_cast<VkShaderStageFlags>(vk::ShaderStageFlagBits::eClosestHitKHR),
		RTMiss         = static_cast<VkShaderStageFlags>(vk::ShaderStageFlagBits::eMissKHR),
		RTIntersection = static_cast<VkShaderStageFlags>(vk::ShaderStageFlagBits::eIntersectionKHR),
		RTCallable     = static_cast<VkShaderStageFlags>(vk::ShaderStageFlagBits::eCallableKHR)
	};

	struct Device;

	struct ShaderModule : public Handle<vk::ShaderModule, true, false>
	{
	public:
		ShaderModule(Device& device);
		~ShaderModule();

		auto getCreatedType() const { return m_CreatedType; }

		auto& getDevice() { return m_Device; }
		auto& getDevice() const { return m_Device; }

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		std::vector<std::uint32_t> m_Code;

		EShaderType m_Type;

	private:
		Device& m_Device;

		EShaderType m_CreatedType;
	};
} // namespace Graphics
