#pragma once

#include <string>
#include <vector>

#include "mip\upe\content_label.h"

#include "AssignmentMethod.h"
#include "Label.h"
#include "ManagedObject.h"

using namespace System;
using namespace System::Collections::Generic;

namespace NetMip
{
	public ref class ContentLabel : public ManagedObject<std::shared_ptr<mip::ContentLabel>>
	{
	internal:
		ContentLabel(std::shared_ptr<mip::ContentLabel>* contentLabel)
			: ManagedObject(contentLabel)
		{}

	public:

		property NetMip::Label^ Label
		{
			NetMip::Label^ get();
		}

		property String^ CreationTime
		{
			String^ get();
		}

		property AssignmentMethod AssignmentMethod
		{
			NetMip::AssignmentMethod get();
		}
	};
}