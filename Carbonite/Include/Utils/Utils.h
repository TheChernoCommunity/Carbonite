#pragma once

namespace Utils
{
	constexpr unsigned bit(const int x)
	{
		return 1 << x;
	}

	template <class T>
	constexpr T alignFloor(T value, T floor)
	{
		return std::floor(value / floor) * floor;
	}

	template <class T>
	constexpr T alignCeil(T value, T ceil)
	{
		return std::ceil((value + (ceil - T(1))) / ceil) * ceil;
	}
} // namespace Utils
