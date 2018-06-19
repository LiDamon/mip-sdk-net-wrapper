#pragma once

#include <string>
#include <vector>

#include "mip\upe\content_label.h"

#include "Label.h"
#include "ManagedObject.h"

using namespace System;
using namespace System::Collections::Generic;

namespace CLI
{
	public enum class AssignmentMethod : unsigned short
	{
		Standard = (unsigned short)mip::AssignmentMethod::STANDARD,
		Privileged = (unsigned short)mip::AssignmentMethod::PRIVILEGED,
		Auto = (unsigned short)mip::AssignmentMethod::AUTO,
	};

	public ref class ContentLabel : public ManagedObject<std::shared_ptr<mip::ContentLabel>>
	{
	internal:

		ContentLabel(std::shared_ptr<mip::ContentLabel>* contentLabel)
			: ManagedObject(contentLabel)
		{}

	public:

		property CLI::Label^ Label
		{
			CLI::Label^ get();
		}

		property String^ CreationTime
		{
			String^ get();
		}

		property AssignmentMethod AssignmentMethod
		{
			CLI::AssignmentMethod get();
		}
	};
}