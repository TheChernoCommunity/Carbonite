#pragma once

#include "Utils/Core.h"

#include <vk_mem_alloc.h>
#include <vulkan/vulkan.hpp>

#include <cstdint>

#include <string_view>
#include <type_traits>
#include <vector>

namespace Graphics
{
	struct Device;

	namespace Detail
	{
		struct HandleBase
		{
		public:
			HandleBase()          = default;
			virtual ~HandleBase() = default;

			virtual bool create()  = 0;
			virtual void destroy() = 0;

			virtual bool isValid() const       = 0;
			virtual bool isCreated() const     = 0;
			virtual bool isDestroyable() const = 0;

			void addChild(HandleBase* child);
			void removeChild(HandleBase* child);

			auto& getChildren() const
			{
				return m_Children;
			}

		protected:
			std::size_t              m_ChildItr = 0;
			std::vector<HandleBase*> m_Children;

			bool                     m_Recreate = false;
			std::vector<HandleBase*> m_DestroyedChildren;
		};

		template <class HandleType>
		struct HandleStorage : public HandleBase
		{
		public:
			HandleStorage()
			    : m_Handle(nullptr)
			{
			}
			template <std::enable_if_t<std::is_copy_constructible_v<HandleType>, bool> = true>
			HandleStorage(const HandleType& handle)
			    : m_Handle(handle)
			{
			}
			HandleStorage(HandleType&& handle)
			    : m_Handle(std::move(handle))
			{
			}

			virtual bool isValid() const override
			{
				return m_Handle;
			}

			HandleType& getHandle()
			{
				return m_Handle;
			}
			HandleType& getHandle() const
			{
				return m_Handle;
			}

			HandleType& operator*()
			{
				return m_Handle;
			}
			HandleType& operator*() const
			{
				return m_Handle;
			}
			HandleType* operator->()
			{
				return &m_Handle;
			}
			HandleType* operator->() const
			{
				return &m_Handle;
			}

			operator HandleType&()
			{
				return m_Handle;
			}
			operator const HandleType&() const
			{
				return m_Handle;
			}

		protected:
			HandleType m_Handle;
		};

		template <class HandleType>
		struct IsHandleTypeValid
		{
			static constexpr bool Value = std::is_constructible_v<HandleType, std::nullptr_t> && std::is_assignable_v<HandleType&, std::nullptr_t> && std::is_destructible_v<HandleType> && std::is_move_constructible_v<HandleType> && std::is_move_assignable_v<HandleType>;
		};
		template <class HandleType>
		static constexpr auto IsHandleTypeValidV = IsHandleTypeValid<HandleType>::Value;

		template <class HandleType, bool Destroyable = true, bool IsDebuggable = false, bool Valid = false>
		struct Handle;

		/* template <class HandleType, true> struct Handle; */
		template <class HandleType, bool IsDebuggable>
		struct Handle<HandleType, true, IsDebuggable, true> : public HandleStorage<HandleType>
		{
		public:
			Handle();
			template <std::enable_if_t<std::is_copy_constructible_v<HandleType>, bool> = true>
			Handle(const HandleType& handle);
			Handle(HandleType&& handle);

			void setDebugName(Device& device, std::string_view name);

			virtual bool create() override;
			virtual void destroy() override;
			virtual bool isCreated() const override
			{
				return m_Created;
			}
			virtual bool isDestroyable() const override
			{
				return m_Destroyable;
			}

		private:
			virtual void createImpl()  = 0;
			virtual bool destroyImpl() = 0;

		private:
			bool m_Created;
			bool m_Destroyable;
		};

		/* template <class HandleType, false> struct Handle; */
		template <class HandleType, bool IsDebuggable>
		struct Handle<HandleType, false, IsDebuggable, true> : public HandleStorage<HandleType>
		{
		public:
			template <std::enable_if_t<std::is_copy_constructible_v<HandleType>, bool> = true>
			Handle(const HandleType& handle);
			Handle(HandleType&& handle);

			void setDebugName(Device& device, std::string_view name);

			virtual bool create() override;
			virtual void destroy() override;

			virtual bool isCreated() const override
			{
				return true;
			}
			virtual bool isDestroyable() const override
			{
				return false;
			}
		};
	} // namespace Detail

	template <class HandleType, bool Destroyable = true, bool IsDebuggable = false>
	using Handle = Detail::Handle<HandleType, Destroyable, IsDebuggable && Core::s_IsDebugMode, Detail::IsHandleTypeValidV<HandleType>>;
} // namespace Graphics

#include "HandleImpl.inl"