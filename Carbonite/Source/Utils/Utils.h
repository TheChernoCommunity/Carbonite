#pragma once

#include <cmath>
#include <cstdint>

namespace Utils
{
	constexpr unsigned bit(const int x) { return 1 << x; }

	template <class T>
	struct FloorImpl;

	template <>
	struct FloorImpl<std::int8_t>
	{
		std::int8_t operator()(std::int8_t value) { return value; }
	};

	template <>
	struct FloorImpl<std::int16_t>
	{
		std::int16_t operator()(std::int16_t value) { return value; }
	};

	template <>
	struct FloorImpl<std::int32_t>
	{
		std::int32_t operator()(std::int32_t value) { return value; }
	};

	template <>
	struct FloorImpl<std::int64_t>
	{
		std::int64_t operator()(std::int64_t value) { return value; }
	};

	template <>
	struct FloorImpl<std::uint8_t>
	{
		std::uint8_t operator()(std::uint8_t value) { return value; }
	};

	template <>
	struct FloorImpl<std::uint16_t>
	{
		std::uint16_t operator()(std::uint16_t value) { return value; }
	};

	template <>
	struct FloorImpl<std::uint32_t>
	{
		std::uint32_t operator()(std::uint32_t value) { return value; }
	};

	template <>
	struct FloorImpl<std::uint64_t>
	{
		std::uint64_t operator()(std::uint64_t value) { return value; }
	};

#if (SIZE_MAX != UINT32_MAX)
	template <>
	struct FloorImpl<std::size_t>
	{
		long double operator()(std::size_t value) { return std::floorl(value); }
	};
#endif

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
