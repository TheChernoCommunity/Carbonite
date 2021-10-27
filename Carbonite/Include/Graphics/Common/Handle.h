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
			std::size_t m_ChildItr = 0;
			bool        m_Recreate;

			std::vector<HandleBase*> m_Children;
			std::vector<HandleBase*> m_DestroyedChildren;
		};

		template <class HandleType>
		struct IsHandleValid
		{
			static constexpr bool Value = std::is_constructible_v<HandleType, std::nullptr_t> && std::is_assignable_v<HandleType&, std::nullptr_t> && std::is_copy_constructible_v<HandleType> && std::is_copy_assignable_v<HandleType> && std::is_move_constructible_v<HandleType> && std::is_move_assignable_v<HandleType> && std::is_destructible_v<HandleType>;
		};

		template <class HandleType>
		static constexpr auto IsHandleValidV = IsHandleValid<HandleType>::Value;

		template <class HandleType>
		struct HandleStorage : public HandleBase
		{
		public:
			HandleStorage()
			    : m_Handle(nullptr) {}
			HandleStorage(HandleType handle)
			    : m_Handle(handle) {}
			HandleStorage(const HandleType& handle)
			    : m_Handle(handle) {}
			HandleStorage(HandleType&& handle)
			    : m_Handle(std::move(handle)) {}

			virtual bool isValid() const override
			{
				return m_Handle;
			}

			auto& getHandle()
			{
				return m_Handle;
			}
			auto& getHandle() const
			{
				return m_Handle;
			}
			auto& operator*()
			{
				return m_Handle;
			}
			auto& operator*() const
			{
				return m_Handle;
			}
			auto* operator->()
			{
				return &m_Handle;
			}
			auto* operator->() const
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

		template <class HandleType, bool IsDestroyable, bool IsDebuggable, bool IsValid>
		struct Handle;

		template <class HandleType, bool IsDebuggable>
		struct Handle<HandleType, true, IsDebuggable, true> : public HandleStorage<HandleType>
		{
		public:
			using HandleT                    = HandleType;
			using Base                       = HandleStorage<HandleType>;
			static constexpr bool Debuggable = IsDebuggable;

		public:
			Handle()
			    : m_Created(false), m_Destroyable(true) {}
			Handle(HandleType handle)
			    : Base(handle), m_Created(true), m_Destroyable(false) {}
			Handle(const HandleType& handle)
			    : Base(handle), m_Created(true), m_Destroyable(false) {}
			Handle(HandleType&& handle)
			    : Base(std::move(handle)), m_Created(true), m_Destroyable(false) {}

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

		template <class HandleType, bool IsDebuggable>
		struct Handle<HandleType, false, IsDebuggable, true> : public HandleStorage<HandleType>
		{
		public:
			using HandleT                    = HandleType;
			using Base                       = HandleStorage<HandleType>;
			static constexpr bool Debuggable = IsDebuggable;

		public:
			Handle(HandleType handle)
			    : Base(handle) {}
			Handle(const HandleType& handle)
			    : Base(handle) {}
			Handle(HandleType&& handle)
			    : Base(std::move(handle)) {}

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

	template <class HandleType, bool IsDestroyable, bool IsDebuggable>
	using Handle = Detail::Handle<HandleType, IsDestroyable, IsDebuggable && Core::s_IsDebugMode, Detail::IsHandleValidV<HandleType>>;
} // namespace Graphics

/* Implementation */

namespace Graphics::Detail
{
	template <class HandleType, bool IsDebuggable>
	bool Handle<HandleType, true, IsDebuggable, true>::create()
	{
		bool pCreated = m_Created;
		if (pCreated)
		{
			Base::m_Recreate = true;
			destroy();
		}

		createImpl();
		m_Created = Base::isValid();
		if (pCreated && m_Created)
		{
			for (auto& child : Base::m_DestroyedChildren)
				child->create();
			Base::m_DestroyedChildren.clear();
		}
		Base::m_Recreate = false;
		return m_Created;
	}

	template <class HandleType, bool IsDebuggable>
	void Handle<HandleType, true, IsDebuggable, true>::destroy()
	{
		if (Base::m_Recreate)
			Base::m_DestroyedChildren.clear();

		for (Base::m_ChildItr = 0; Base::m_ChildItr < Base::m_Children.size(); ++Base::m_ChildItr)
		{
			auto child = Base::m_Children[Base::m_ChildItr];

			if (child->isValid())
			{
				child->destroy();

				if (Base::m_Recreate && child->isDestroyable())
					Base::m_DestroyedChildren.push_back(child);
			}
		}

		if (m_Destroyable && isCreated() && destroyImpl())
			Base::m_Handle = nullptr;
		m_Created        = false;
		Base::m_ChildItr = 0;
	}

	template <class HandleType, bool IsDebuggable>
	bool Handle<HandleType, false, IsDebuggable, true>::create()
	{
		Base::m_Recreate = true;
		destroy();

		for (auto& child : Base::m_destroyedChildren)
			child->create();
		Base::m_DestroyedChildren.clear();

		Base::m_Recreate = false;
		return true;
	}

	template <class HandleType, bool IsDebuggable>
	void Handle<HandleType, false, IsDebuggable, true>::destroy()
	{
		Base::m_DestroyedChildren.clear();

		for (Base::m_ChildItr = 0; Base::m_ChildItr < Base::m_Children.size(); ++Base::m_ChildItr)
		{
			auto child = Base::m_Children[Base::m_ChildItr];

			if (child->isValid())
			{
				child->destroy();

				if (child->isDestroyable())
					Base::m_DestroyedChildren.push_back(child);
			}
		}

		Base::m_ChildItr = 0;
	}
} // namespace Graphics::Detail
