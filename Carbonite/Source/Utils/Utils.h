#pragma once

#include <cmath>
#include <cstdint>

#include <concepts>

namespace Utils
{
	constexpr unsigned bit(const int x) { return 1 << x; }

	template <class T>
	struct FloorImpl;

	template <std::integral T>
	struct FloorImpl<T>
	{
		T operator()(T value) { return value; }
	};

	template <>
	struct FloorImpl<float>
	{
		float operator()(float value) { return std::floorf(value); }
	};

	template <>
	struct FloorImpl<double>
	{
		double operator()(double value) { return std::floor(value); }
	};

	template <>
	struct FloorImpl<long double>
	{
		long double operator()(long double value) { return std::floorl(value); }
	};

	template <class L, class R>
	constexpr auto alignFloor(L value, R floor)
	{
		auto div = value / floor;
		return FloorImpl<decltype(div)>()(div) * floor;
	}

	template <class L, class R>
	constexpr auto alignCeil(L value, R ceil)
	{
		auto div = (value + (ceil - R(1))) / ceil;
		return FloorImpl<decltype(div)>()(div) * ceil;
	}
} // namespace Utils
