#include "PCH.h"

#include "Graphics/Debug/Debug.h"
#include "Graphics/Instance.h"
#include "Log.h"

#include <iostream>

namespace Graphics
{
	bool Debug::s_Enabled = Core::s_IsConfigDebug;

	void Debug::Disable()
	{
		s_Enabled = false;
	}

	void Debug::PopulateCreateInfo(vk::DebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo.messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
		createInfo.messageType     = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
		createInfo.pfnUserCallback = Debug::DebugCallback;
	}

	std::string Debug::GetSeverity(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity)
	{
		switch (messageSeverity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: return "Verbose";
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: return "Info";
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: return "Warning";
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: return "Error";
		default: return "Unknown";
		}
	}

	std::string Debug::GetTypes(VkDebugUtilsMessageTypeFlagsEXT messageTypes)
	{
		std::string str;
		if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
		{
			str += "General";
			messageTypes &= ~VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT;
		}
		if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
		{
			if (!str.empty())
				str += " | ";
			str += "Validation";
			messageTypes &= ~VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
		}
		if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
		{
			if (!str.empty())
				str += " | ";
			str += "Performance";
			messageTypes &= ~VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		}
		if (messageTypes != 0) str = "(" + str + ") + " + std::to_string(messageTypes);
		return str;
	}

	VkBool32 Debug::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, [[maybe_unused]] VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, [[maybe_unused]] void* pUserData)
	{
		std::string message = pCallbackData->pMessage;
		switch (static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(messageSeverity))
		{
		case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
			Log::trace(message);
			break;

		case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
			Log::info(message);
			break;

		case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
			Log::warn(message);
			break;

		case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
			Log::error(message);
			break;

		default:
			Log::debug(message);
			break;
		}

		return VK_FALSE;
	}

	Debug::Debug(Instance& instance)
	    : m_Instance(instance)
	{
		m_Instance.addChild(this);
	}

	Debug::~Debug()
	{
		if (isValid())
			destroy();
		m_Instance.removeChild(this);
	}

	void Debug::createImpl()
	{
		vk::DebugUtilsMessengerCreateInfoEXT createInfo;
		PopulateCreateInfo(createInfo);

		m_Handle = m_Instance->createDebugUtilsMessengerEXT(createInfo, nullptr, m_Instance.getDispatcher());
	}

	bool Debug::destroyImpl()
	{
		m_Instance->destroyDebugUtilsMessengerEXT(m_Handle, nullptr, m_Instance.getDispatcher());
		return true;
	}
} // namespace Graphics
