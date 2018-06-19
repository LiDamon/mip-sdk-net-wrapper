#pragma once

#include "mip/common_types.h"

namespace NetMip
{
	public enum class AssignmentMethod : unsigned short
	{
		Standard = (unsigned short)mip::AssignmentMethod::STANDARD,
		Privileged = (unsigned short)mip::AssignmentMethod::PRIVILEGED,
		Auto = (unsigned short)mip::AssignmentMethod::AUTO,
	};
}
