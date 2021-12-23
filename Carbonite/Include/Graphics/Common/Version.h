#pragma once

#include <cstdint>

namespace Graphics
{
	union Version
	{
	public:
		constexpr Version() : m_Version(0) {}
		constexpr Version(std::uint32_t version) : m_Version(version) {}
		constexpr Version(std::uint32_t variant, std::uint32_t major, std::uint32_t minor, std::uint32_t patch) : m_SubVersions({ patch, minor, major, variant }) {}

		constexpr operator std::uint32_t() const { return m_Version; }

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
} // namespace Graphics
