#pragma once

#include <ostream>
#include <utility>

template <class T>
struct Flags
{
public:
	using ValueT = T;

public:
	constexpr Flags(const ValueT& value)
	    : m_Value(value) {}
	constexpr Flags(ValueT&& value)
	    : m_Value(std::move(value)) {}
	template <class U>
	constexpr Flags(const Flags<U>& flags)
	    : m_Value(flags.m_Value)
	{
	}
	template <class U>
	constexpr Flags(Flags<U>&& flags)
	    : m_Value(std::move(flags.m_Value))
	{
	}

	constexpr Flags& operator=(const ValueT& value)
	{
		m_Value = value;
		return *this;
	}
	constexpr Flags& operator=(ValueT&& value)
	{
		m_Value = std::move(value);
		return *this;
	}
	template <class U>
	constexpr Flags& operator=(const Flags<U>& flags)
	{
		m_Value = flags.m_Value;
		return *this;
	}
	template <class U>
	constexpr Flags& operator=(Flags<U>&& flags)
	{
		m_Value = std::move(flags.m_Value);
		return *this;
	}

	constexpr operator ValueT&()
	{
		return m_Value;
	}
	constexpr ValueT& getValue()
	{
		return m_Value;
	}

	friend constexpr Flags operator~(const Flags& flags)
	{
		return ~flags.m_Value;
	}
	template <class U>
	friend constexpr bool operator==(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value == rhs.m_Value;
	}
	template <class U>
	friend constexpr bool operator!=(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value != rhs.m_Value;
	}
	template <class U>
	friend constexpr bool operator<(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value < rhs.m_Value;
	}
	template <class U>
	friend constexpr bool operator<=(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value <= rhs.m_Value;
	}
	template <class U>
	friend constexpr bool operator>(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value > rhs.m_Value;
	}
	template <class U>
	friend constexpr bool operator>=(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value >= rhs.m_Value;
	}
	template <class U>
	friend constexpr Flags operator&(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value & rhs.m_Value;
	}
	template <class U>
	constexpr Flags& operator&=(const Flags<U>& rhs)
	{
		m_Value &= rhs.m_Value;
		return *this;
	}
	template <class U>
	friend constexpr Flags operator|(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value | rhs.m_Value;
	}
	template <class U>
	constexpr Flags& operator|=(const Flags<U>& rhs)
	{
		m_Value |= rhs.m_Value;
		return *this;
	}
	template <class U>
	friend constexpr Flags operator^(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value ^ rhs.m_Value;
	}
	template <class U>
	constexpr Flags& operator^=(const Flags<U>& rhs)
	{
		m_Value ^= rhs.m_Value;
		return *this;
	}
	template <class U>
	friend constexpr Flags operator<<(const Flags& lhs, std::size_t count)
	{
		return lhs.m_Value << count;
	}
	template <class U>
	constexpr Flags& operator<<=(std::size_t count)
	{
		m_Value <<= count;
		return *this;
	}
	template <class U>
	friend constexpr Flags operator>>(const Flags& lhs, std::size_t count)
	{
		return lhs.m_Value >> count;
	}
	template <class U>
	constexpr Flags& operator>>=(std::size_t count)
	{
		m_Value >>= count;
		return *this;
	}
	template <class U>
	friend constexpr Flags operator-(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value - rhs.m_Value;
	}
	template <class U>
	constexpr Flags& operator-=(const Flags<U>& rhs)
	{
		m_Value -= rhs.m_Value;
		return *this;
	}
	template <class U>
	friend constexpr Flags operator+(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value + rhs.m_Value;
	}
	template <class U>
	constexpr Flags& operator+=(const Flags<U>& rhs)
	{
		m_Value += rhs.m_Value;
		return *this;
	}
	template <class U>
	friend constexpr Flags operator*(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value * rhs.m_Value;
	}
	template <class U>
	constexpr Flags& operator*=(const Flags<U>& rhs)
	{
		m_Value *= rhs.m_Value;
		return *this;
	}
	template <class U>
	friend constexpr Flags operator/(const Flags& lhs, const Flags<U>& rhs)
	{
		return lhs.m_Value / rhs.m_Value;
	}
	template <class U>
	constexpr Flags& operator/=(const Flags<U>& rhs)
	{
		m_Value /= rhs.m_Value;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Flags& flags)
	{
		return stream << flags.m_Value;
	}

public:
	ValueT m_Value;
};
