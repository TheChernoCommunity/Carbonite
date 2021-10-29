#include "Graphics/Debug/DebugUtilsEXT.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Instance.h"

namespace Graphics::DebugUtilsEXT
{
	template <class FunctionPtr>
	FunctionPtr getInstanceFunction(Instance& instance, const char* name)
	{
		return reinterpret_cast<FunctionPtr>(vkGetInstanceProcAddr(*instance, name));
	}

	template <class FunctionPtr>
	FunctionPtr getDeviceFunction(Device& device, const char* name)
	{
		return reinterpret_cast<FunctionPtr>(vkGetDeviceProcAddr(*device, name));
	}

	void FunctionPtrs::init(Instance& instance)
	{
		vkCreateDebugUtilsMessengerEXT  = getInstanceFunction<decltype(vkCreateDebugUtilsMessengerEXT)>(instance, "vkCreateDebugUtilsMessengerEXT");
		vkDestroyDebugUtilsMessengerEXT = getInstanceFunction<decltype(vkDestroyDebugUtilsMessengerEXT)>(instance, "vkDestroyDebugUtilsMessengerEXT");
		vkSetDebugUtilsObjectNameEXT    = getInstanceFunction<decltype(vkSetDebugUtilsObjectNameEXT)>(instance, "vkSetDebugUtilsObjectNameEXT");
	}

	void FunctionPtrs::init([[maybe_unused]] Device& device)
	{
	}
} // namespace Graphics::DebugUtilsEXT