#include "Core.h"

#include <sstream>

namespace Core
{
	std::ostream& printBuildConfigFlags(std::ostream& stream, const BuildConfigFlags& flags)
	{
		std::ostringstream str;
		bool               hasAppended = false;

		BuildConfigFlags value = flags;
		if (value == BuildConfigFlag::Unknown)
		{
			str << "Unknown";
		}
		else
		{
			if ((value & BuildConfigFlag::Debug) == BuildConfigFlag::Debug)
			{
				str << "Debug";
				value &= ~BuildConfigFlag::Debug;
				hasAppended = true;
			}
			if ((value & BuildConfigFlag::Dist) == BuildConfigFlag::Dist)
			{
				if (hasAppended)
					str << " | ";
				str << "Dist";
				value &= ~BuildConfigFlag::Dist;
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

	std::ostream& printBuildSystemFlags(std::ostream& stream, const BuildSystemFlags& flags)
	{
		std::ostringstream str;
		bool               hasAppended = false;

		BuildSystemFlags value = flags;
		if (value == BuildSystemFlag::Unknown)
		{
			str << "Unknown";
		}
		else
		{
			if ((value & BuildSystemFlag::Windows) == BuildSystemFlag::Windows)
			{
				str << "Windows";
				value &= ~BuildSystemFlag::Windows;
				hasAppended = true;
			}
			if ((value & BuildSystemFlag::Macosx) == BuildSystemFlag::Macosx)
			{
				if (hasAppended)
					str << " | ";
				str << "Macosx";
				value &= ~BuildSystemFlag::Macosx;
				hasAppended = true;
			}
			if ((value & BuildSystemFlag::Linux) == BuildSystemFlag::Linux)
			{
				if (hasAppended)
					str << " | ";
				str << "Linux";
				value &= ~BuildSystemFlag::Linux;
				hasAppended = true;
			}
			if ((value & BuildSystemFlag::Unix) == BuildSystemFlag::Unix)
			{
				if (hasAppended)
					str << " | ";
				str << "Unix";
				value &= ~BuildSystemFlag::Unix;
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

	std::ostream& printBuildToolsetFlags(std::ostream& stream, const BuildToolsetFlags& flags)
	{
		std::ostringstream str;
		bool               hasAppended = false;

		BuildToolsetFlags value = flags;
		if (value == BuildToolsetFlag::Unknown)
		{
			str << "Unknown";
		}
		else
		{
			if ((value & BuildToolsetFlag::MSVC) == BuildToolsetFlag::MSVC)
			{
				str << "MSVC";
				value &= ~BuildToolsetFlag::MSVC;
				hasAppended = true;
			}
			if ((value & BuildToolsetFlag::Clang) == BuildToolsetFlag::Clang)
			{
				if (hasAppended)
					str << " | ";
				str << "Clang";
				value &= ~BuildToolsetFlag::Clang;
				hasAppended = true;
			}
			if ((value & BuildToolsetFlag::GCC) == BuildToolsetFlag::GCC)
			{
				if (hasAppended)
					str << " | ";
				str << "GCC";
				value &= ~BuildToolsetFlag::GCC;
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

	std::ostream& printBuildPlatformFlags(std::ostream& stream, const BuildPlatformFlags& flags)
	{
		std::ostringstream str;
		bool               hasAppended = false;

		BuildPlatformFlags value = flags;
		if (value == BuildPlatformFlag::Unknown)
		{
			str << "Unknown";
		}
		else
		{
			if ((value & BuildPlatformFlag::X86) == BuildPlatformFlag::X86)
			{
				str << "X86";
				value &= ~BuildPlatformFlag::X86;
				hasAppended = true;
			}
			if ((value & BuildPlatformFlag::AMD64) == BuildPlatformFlag::AMD64)
			{
				if (hasAppended)
					str << " | ";
				str << "AMD64";
				value &= ~BuildPlatformFlag::AMD64;
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