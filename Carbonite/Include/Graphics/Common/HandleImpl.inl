#pragma once

#include "Graphics/Instance.h"

#include "Graphics/Debug/Debug.h"

#include "Graphics/Device/Surface.h"

#include "Graphics/Device/Device.h"

#include "Handle.h"

namespace Graphics::Detail
{
	/* template <class HandleType, true> struct Handle; */
	template <class HandleType, bool IsDebuggable>
	Handle<HandleType, true, IsDebuggable, true>::Handle()
	    : HandleStorage<HandleType>(nullptr), m_Created(false), m_Destroyable(true)
	{
	}

	template <class HandleType, bool IsDebuggable>
	template <std::enable_if_t<std::is_copy_constructible_v<HandleType>, bool>>
	Handle<HandleType, true, IsDebuggable, true>::Handle(const HandleType& handle)
	    : HandleStorage<HandleType>(handle), m_Created(true), m_Destroyable(false)
	{
	}

	template <class HandleType, bool IsDebuggable>
	Handle<HandleType, true, IsDebuggable, true>::Handle(HandleType&& handle)
	    : HandleStorage<HandleType>(std::move(handle)), m_Created(true), m_Destroyable(false)
	{
	}

	template <class HandleType, bool IsDebuggable>
	void Handle<HandleType, true, IsDebuggable, true>::setDebugName(Device& device, std::string_view name)
	{
		if constexpr (IsDebuggable)
		{
			if (HandleBase::isValid() && Debug::IsEnabled())
			{
				if (name.empty())
				{
					vk::DebugUtilsObjectNameInfoEXT nameInfo   = { HandleStorage<HandleType>::m_Handle.objectType, reinterpret_cast<std::uint64_t>(static_cast<typename HandleType::CType>(HandleStorage<HandleType>::m_Handle)), nullptr };
					VkDebugUtilsObjectNameInfoEXT   vkNameInfo = nameInfo;
					device.getSurface().getInstance().getDebug().getDebugUtilsEXT().vkSetDebugUtilsObjectNameEXT(*device, &vkNameInfo);
				}
				else
				{
					std::string tName(name);

					vk::DebugUtilsObjectNameInfoEXT nameInfo   = { HandleStorage<HandleType>::m_Handle.objectType, reinterpret_cast<std::uint64_t>(static_cast<typename HandleType::CType>(HandleStorage<HandleType>::m_Handle)), tName.c_str() };
					VkDebugUtilsObjectNameInfoEXT   vkNameInfo = nameInfo;
					device.getSurface().getInstance().getDebug().getDebugUtilsEXT().vkSetDebugUtilsObjectNameEXT(*device, &vkNameInfo);
				}
			}
		}
	}

	template <class HandleType, bool IsDebuggable>
	bool Handle<HandleType, true, IsDebuggable, true>::create()
	{
		bool pCreated = m_Created;
		if (pCreated)
		{
			HandleBase::m_Recreate = true;
			destroy();
		}

		createImpl();
		m_Created = HandleBase::isValid();
		if (pCreated && m_Created)
		{
			for (auto& child : HandleBase::m_DestroyedChildren)
				child->create();
			HandleBase::m_DestroyedChildren.clear();
		}
		HandleBase::m_Recreate = false;
		return m_Created;
	}

	template <class HandleType, bool IsDebuggable>
	void Handle<HandleType, true, IsDebuggable, true>::destroy()
	{
		if (HandleBase::m_Recreate)
			HandleBase::m_DestroyedChildren.clear();

		for (HandleBase::m_ChildItr = 0; HandleBase::m_ChildItr < HandleBase::m_Children.size(); ++HandleBase::m_ChildItr)
		{
			auto child = HandleBase::m_Children[HandleBase::m_ChildItr];

			if (child->isValid())
			{
				child->destroy();

				if (HandleBase::m_Recreate && child->isDestroyable())
					HandleBase::m_DestroyedChildren.push_back(child);
			}
		}

		if (m_Destroyable && isCreated() && destroyImpl())
			HandleStorage<HandleType>::m_Handle = nullptr;
		m_Created              = false;
		HandleBase::m_ChildItr = 0;
	}

	/* template <class HandleType, false> struct Handle; */
	template <class HandleType, bool IsDebuggable>
	template <std::enable_if_t<std::is_copy_constructible_v<HandleType>, bool>>
	Handle<HandleType, false, IsDebuggable, true>::Handle(const HandleType& handle)
	    : HandleStorage<HandleType>(handle)
	{
	}

	template <class HandleType, bool IsDebuggable>
	Handle<HandleType, false, IsDebuggable, true>::Handle(HandleType&& handle)
	    : HandleStorage<HandleType>(std::move(handle))
	{
	}

	template <class HandleType, bool IsDebuggable>
	void Handle<HandleType, false, IsDebuggable, true>::setDebugName(Device& device, std::string_view name)
	{
		if constexpr (IsDebuggable)
		{
			if (HandleBase::isValid() && Debug::IsEnabled())
			{
				if (name.empty())
				{
					vk::DebugUtilsObjectNameInfoEXT nameInfo   = { HandleStorage<HandleType>::m_Handle.objectType, reinterpret_cast<std::uint64_t>(static_cast<typename HandleType::CType>(HandleStorage<HandleType>::m_Handle)), nullptr };
					VkDebugUtilsObjectNameInfoEXT   vkNameInfo = nameInfo;
					device.getSurface().getInstance().getDebug().getDebugUtilsEXT().vkSetDebugUtilsObjectNameEXT(*device, &vkNameInfo);
				}
				else
				{
					std::string tName(name);

					vk::DebugUtilsObjectNameInfoEXT nameInfo   = { HandleStorage<HandleType>::m_Handle.objectType, reinterpret_cast<std::uint64_t>(static_cast<typename HandleType::CType>(HandleStorage<HandleType>::m_Handle)), tName.c_str() };
					VkDebugUtilsObjectNameInfoEXT   vkNameInfo = nameInfo;
					device.getSurface().getInstance().getDebug().getDebugUtilsEXT().vkSetDebugUtilsObjectNameEXT(*device, &vkNameInfo);
				}
			}
		}
	}

	template <class HandleType, bool IsDebuggable>
	bool Handle<HandleType, false, IsDebuggable, true>::create()
	{
		HandleBase::m_Recreate = true;
		destroy();

		for (auto& child : HandleBase::m_DestroyedChildren)
			child->create();
		HandleBase::m_DestroyedChildren.clear();

		HandleBase::m_Recreate = false;
		return true;
	}

	template <class HandleType, bool IsDebuggable>
	void Handle<HandleType, false, IsDebuggable, true>::destroy()
	{
		HandleBase::m_DestroyedChildren.clear();

		for (HandleBase::m_ChildItr = 0; HandleBase::m_ChildItr < HandleBase::m_Children.size(); ++HandleBase::m_ChildItr)
		{
			auto child = HandleBase::m_Children[HandleBase::m_ChildItr];

			if (child->isValid())
			{
				child->destroy();

				if (child->isDestroyable())
					HandleBase::m_DestroyedChildren.push_back(child);
			}
		}

		HandleBase::m_ChildItr = 0;
	}
} // namespace Graphics::Detail