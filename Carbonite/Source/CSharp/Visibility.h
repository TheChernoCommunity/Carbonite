#pragma once

#include <cstdint>

#include <ostream>

namespace CSharp
{
	enum class EVisibility : std::uint8_t
	{
		Public,
		Protected,
		Private,
		Internal,
		ProtectedInternal
	};

	std::ostream& operator<<(std::ostream& stream, EVisibility visibility);

	EVisibility getVisibilityFromMonoFieldFlags(std::uint32_t flags);
	EVisibility getVisibilityFromMonoClassFlags(std::uint32_t flags);
} // namespace CSharp