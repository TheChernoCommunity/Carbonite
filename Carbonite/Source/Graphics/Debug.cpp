#include "Graphics/Debug.h"

#include <iostream>

namespace Graphics
{
#ifdef _DEBUG
	bool Debug::s_Enabled = true;
#else
	bool Debug::s_Enabled = false;
#endif

	void Debug::Disable()
	{
		s_Enabled = false;
	}

	void Debug::PopulateCreateInfo(vk::DebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo.messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
		createInfo.messageType     = vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
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

	VkBool32 Debug::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, [[maybe_unused]] void* pUserData)
	{
		std::string message = "VK Validation Layer " + GetSeverity(messageSeverity) + " (" + GetTypes(messageTypes) + "): " + pCallbackData->pMessage + "\n";
		if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
			std::cerr << message;
		else
			std::cout << message;
		return 0;
	}

	Debug::Debug(Instance& instance)
	    : m_Instance(&instance), Handle({ &instance })
	{
	}

	Debug::~Debug()
	{
		if (isCreated())
			destroy();
	}

	void Debug::createImpl()
	{
		vk::DebugUtilsMessengerCreateInfoEXT createInfo;
		PopulateCreateInfo(createInfo);
		m_Handle = m_Instance->getHandle().createDebugUtilsMessengerEXT(createInfo);
	}

	bool Debug::destroyImpl()
	{
		m_Instance->getHandle().destroyDebugUtilsMessengerEXT(m_Handle);
		return true;
	}
} // namespace Graphics