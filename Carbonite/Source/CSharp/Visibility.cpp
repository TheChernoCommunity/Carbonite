#include "PCH.h"

#include "Visibility.h"

#include <mono/metadata/attrdefs.h>

namespace CSharp
{
	std::ostream& operator<<(std::ostream& stream, EVisibility visibility)
	{
		switch (visibility)
		{
		case EVisibility::Public: return stream << "public";
		case EVisibility::Protected: return stream << "protected";
		case EVisibility::Private: return stream << "private";
		case EVisibility::Internal: return stream << "internal";
		case EVisibility::ProtectedInternal: return stream << "protected internal";
		default: return stream << "unknown";
		}
	}

	EVisibility getVisibilityFromMonoFieldFlags(std::uint32_t flags)
	{
		switch (flags & MONO_FIELD_ATTR_FIELD_ACCESS_MASK)
		{
		case MONO_FIELD_ATTR_PUBLIC:
			return EVisibility::Public;
		case MONO_FIELD_ATTR_FAM_OR_ASSEM:
			return EVisibility::Protected;
		case MONO_FIELD_ATTR_FAMILY:
			return EVisibility::Protected;
		case MONO_FIELD_ATTR_ASSEMBLY:
			return EVisibility::Internal;
		case MONO_FIELD_ATTR_FAM_AND_ASSEM:
			return EVisibility::ProtectedInternal;
		case MONO_FIELD_ATTR_PRIVATE:
			return EVisibility::Private;
		default:
			return EVisibility::Internal;
		}
	}

	EVisibility getVisibilityFromMonoClassFlags(std::uint32_t flags)
	{
		switch (flags & MONO_TYPE_ATTR_VISIBILITY_MASK)
		{
		case MONO_TYPE_ATTR_NOT_PUBLIC:
			return EVisibility::Private;
		case MONO_TYPE_ATTR_PUBLIC:
			return EVisibility::Public;
		case MONO_TYPE_ATTR_NESTED_PUBLIC:
			return EVisibility::Public;
		case MONO_TYPE_ATTR_NESTED_PRIVATE:
			return EVisibility::Private;
		case MONO_TYPE_ATTR_NESTED_FAMILY:
			return EVisibility::Protected;
		case MONO_TYPE_ATTR_NESTED_ASSEMBLY:
			return EVisibility::Internal;
		case MONO_TYPE_ATTR_NESTED_FAM_AND_ASSEM:
			return EVisibility::ProtectedInternal;
		case MONO_TYPE_ATTR_NESTED_FAM_OR_ASSEM:
			return EVisibility::Protected;
		default:
			return EVisibility::Internal;
		}
	}
} // namespace CSharp