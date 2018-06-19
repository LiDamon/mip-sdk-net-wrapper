#pragma once

#include <string>
#include <vector>

#include "mip\upe\content_label.h"

#include "AssignmentMethod.h"
#include "Label.h"
#include "ManagedObject.h"

using namespace System;
using namespace System::Collections::Generic;

namespace CLI
{
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