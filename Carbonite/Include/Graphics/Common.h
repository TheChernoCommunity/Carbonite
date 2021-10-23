#pragma once

#include <vulkan/vulkan.hpp>

#include <cstdint>

#include <vector>

namespace Graphics
{
	union Version
	{
	public:
		constexpr Version();
		constexpr Version(std::uint32_t version);
		constexpr Version(std::uint32_t variant, std::uint32_t major, std::uint32_t minor, std::uint32_t patch);

		constexpr operator std::uint32_t() const
		{
			return m_Version;
		}

	public:
		struct SubVersions
		{
			std::uint32_t patch : 12;
			std::uint32_t minor : 10;
			std::uint32_t major : 7;
			std::uint32_t variant : 3;
		} m_SubVersions;
		std::uint32_t m_Version;
	};

	struct HandleBase
	{
	public:
		HandleBase(const std::vector<HandleBase*>& parents = {});
		virtual ~HandleBase();

		virtual bool create()  = 0;
		virtual void destroy() = 0;

		virtual bool isValid() const       = 0;
		virtual bool isCreated() const     = 0;
		virtual bool isDestroyable() const = 0;

		auto& getParents() const
		{
			return m_Parents;
		}
		auto& getChildren() const
		{
			return m_Children;
		}

	private:
		std::vector<HandleBase*> m_Parents;
		std::vector<HandleBase*> m_Children;
	};

	template <class HandleType, bool Destroyable = true>
	struct Handle : public HandleBase
	{
	public:
		using HandleT = HandleType;

	public:
		Handle(const std::vector<HandleBase*>& parents = {});

		virtual bool create() override;
		virtual void destroy() override;

		virtual bool isValid() const override
		{
			return m_Handle;
		}
		virtual bool isCreated() const override
		{
			return m_Created;
		}
		virtual bool isDestroyable() const override
		{
			return Destroyable;
		}
		HandleT& getHandle()
		{
			return m_Handle;
		}
		const HandleT& getHandle() const
		{
			return m_Handle;
		}

	private:
		virtual void createImpl()  = 0;
		virtual bool destroyImpl() = 0;

	protected:
		HandleT m_Handle = nullptr;

	private:
		std::vector<HandleBase*> m_DestroyedChildren;

		bool m_Created  = false;
		bool m_Recreate = false;
	};

	/* Implementation */

	/* struct Version */

	constexpr Version::Version()
	    : m_Version(0) {}

	constexpr Version::Version(std::uint32_t version)
	    : m_Version(version) {}

	constexpr Version::Version(std::uint32_t variant, std::uint32_t major, std::uint32_t minor, std::uint32_t patch)
	    : m_SubVersions({ patch, minor, major, variant }) {}

	/* template <class HandleType, bool Destroyable> struct Handle */

	template <class HandleType, bool Destroyable>
	Handle<HandleType, Destroyable>::Handle(const std::vector<HandleBase*>& parents)
	    : HandleBase(parents)
	{
	}

	template <class HandleType, bool Destroyable>
	bool Handle<HandleType, Destroyable>::create()
	{
		bool pCreated = m_Created;
		if (pCreated)
		{
			m_Recreate = true;
			destroy();
		}

		createImpl();
		m_Created = m_Handle;
		if (pCreated && m_Created)
		{
			for (auto& child : m_DestroyedChildren)
				child->create();
			m_DestroyedChildren.clear();
		}
		m_Recreate = false;
		return m_Created;
	}

	template <class HandleType, bool Destroyable>
	void Handle<HandleType, Destroyable>::destroy()
	{
		if (m_Recreate)
			m_DestroyedChildren.clear();

		auto& children = getChildren();
		auto  itr      = children.begin();
		while (itr != children.end())
		{
			auto child = *itr;

			if (child->isCreated())
			{
				child->destroy();

				if (m_Recreate && child->isDestroyable())
					m_DestroyedChildren.push_back(child);
			}

			++itr;
		}

		if constexpr (Destroyable)
			if (m_Handle && destroyImpl())
				m_Handle = nullptr;
		m_Created = false;
	}
} // namespace Graphics