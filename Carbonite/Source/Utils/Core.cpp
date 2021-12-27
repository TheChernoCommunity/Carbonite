#include "PCH.h"

#include "Core.h"

#include <sstream>

namespace Core
{
	std::ostream& printCarboniteConfigFlags(std::ostream& stream, const CarboniteConfigFlags& flags)
	{
		std::ostringstream str;
		bool               hasAppended = false;

		CarboniteConfigFlags value = flags;
		if (value == CarboniteConfigFlag::Unknown)
		{
			str << "Unknown";
		}
		else
		{
			if ((value & CarboniteConfigFlag::Debug) == CarboniteConfigFlag::Debug)
			{
				str << "Debug";
				value &= ~CarboniteConfigFlag::Debug;
				hasAppended = true;
			}
			if ((value & CarboniteConfigFlag::Dist) == CarboniteConfigFlag::Dist)
			{
				if (hasAppended)
					str << " | ";
				str << "Dist";
				value &= ~CarboniteConfigFlag::Dist;
				hasAppended = true;
			}
			if (static_cast<std::uint16_t>(value) != 0)
			{
				if (hasAppended)
					str << " | ";
				str << value;
			}
		}

		return stream << str.str();
	}

	std::ostream& printCarboniteSystemFlags(std::ostream& stream, const CarboniteSystemFlags& flags)
	{
		std::ostringstream str;
		bool               hasAppended = false;

		CarboniteSystemFlags value = flags;
		if (value == CarboniteSystemFlag::Unknown)
		{
			str << "Unknown";
		}
		else
		{
			if ((value & CarboniteSystemFlag::Windows) == CarboniteSystemFlag::Windows)
			{
				str << "Windows";
				value &= ~CarboniteSystemFlag::Windows;
				hasAppended = true;
			}
			if ((value & CarboniteSystemFlag::Macosx) == CarboniteSystemFlag::Macosx)
			{
				if (hasAppended)
					str << " | ";
				str << "Macosx";
				value &= ~CarboniteSystemFlag::Macosx;
				hasAppended = true;
			}
			if ((value & CarboniteSystemFlag::Linux) == CarboniteSystemFlag::Linux)
			{
				if (hasAppended)
					str << " | ";
				str << "Linux";
				value &= ~CarboniteSystemFlag::Linux;
				hasAppended = true;
			}
			if ((value & CarboniteSystemFlag::Unix) == CarboniteSystemFlag::Unix)
			{
				if (hasAppended)
					str << " | ";
				str << "Unix";
				value &= ~CarboniteSystemFlag::Unix;
				hasAppended = true;
			}
			if (static_cast<std::uint16_t>(value) != 0)
			{
				if (hasAppended)
					str << " | ";
				str << value;
			}
		}

		return stream << str.str();
	}

	std::ostream& printCarboniteToolsetFlags(std::ostream& stream, const CarboniteToolsetFlags& flags)
	{
		std::ostringstream str;
		bool               hasAppended = false;

		CarboniteToolsetFlags value = flags;
		if (value == CarboniteToolsetFlag::Unknown)
		{
			str << "Unknown";
		}
		else
		{
			if ((value & CarboniteToolsetFlag::MSVC) == CarboniteToolsetFlag::MSVC)
			{
				str << "MSVC";
				value &= ~CarboniteToolsetFlag::MSVC;
				hasAppended = true;
			}
			if ((value & CarboniteToolsetFlag::Clang) == CarboniteToolsetFlag::Clang)
			{
				if (hasAppended)
					str << " | ";
				str << "Clang";
				value &= ~CarboniteToolsetFlag::Clang;
				hasAppended = true;
			}
			if ((value & CarboniteToolsetFlag::GCC) == CarboniteToolsetFlag::GCC)
			{
				if (hasAppended)
					str << " | ";
				str << "GCC";
				value &= ~CarboniteToolsetFlag::GCC;
				hasAppended = true;
			}
			if (static_cast<std::uint16_t>(value) != 0)
			{
				if (hasAppended)
					str << " | ";
				str << value;
			}
		}

		return stream << str.str();
	}

	std::ostream& printCarbonitePlatformFlags(std::ostream& stream, const CarbonitePlatformFlags& flags)
	{
		std::ostringstream str;
		bool               hasAppended = false;

		CarbonitePlatformFlags value = flags;
		if (value == CarbonitePlatformFlag::Unknown)
		{
			str << "Unknown";
		}
		else
		{
			if ((value & CarbonitePlatformFlag::X86) == CarbonitePlatformFlag::X86)
			{
				str << "X86";
				value &= ~CarbonitePlatformFlag::X86;
				hasAppended = true;
			}
			if ((value & CarbonitePlatformFlag::AMD64) == CarbonitePlatformFlag::AMD64)
			{
				if (hasAppended)
					str << " | ";
				str << "AMD64";
				value &= ~CarbonitePlatformFlag::AMD64;
				hasAppended = true;
			}
			if (static_cast<std::uint16_t>(value) != 0)
			{
				if (hasAppended)
					str << " | ";
				str << value;
			}
		}

		return stream << str.str();
	}
} // namespace Core
