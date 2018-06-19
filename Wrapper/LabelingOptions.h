#pragma once

#include <vcclr.h>

#include "mip/file/labeling_options.h"

#include "AssignmentMethod.h"
#include "ManagedObject.h"

using namespace System;

namespace CLI
{
	public ref class LabelingOptions : public ManagedObject<mip::LabelingOptions>
	{
	private:
		static AssignmentMethod DEFAULT_ASSIGNMENT_METHOD = AssignmentMethod::Standard;
		static String^ DEFAULT_JUSTIFICATION_METHOD = String::Empty;

	public:
		LabelingOptions(AssignmentMethod method, String^ justificationMessage);

		LabelingOptions()
			: LabelingOptions(DEFAULT_ASSIGNMENT_METHOD, DEFAULT_JUSTIFICATION_METHOD)
		{}

		LabelingOptions(String^ justificationMessage)
			: LabelingOptions(DEFAULT_ASSIGNMENT_METHOD, justificationMessage)
		{}

		LabelingOptions(AssignmentMethod method)
			: LabelingOptions(method, DEFAULT_JUSTIFICATION_METHOD)
		{}

	public:
		property AssignmentMethod Method
		{
			AssignmentMethod get();
			void set(AssignmentMethod value);
		}

		property String^ JustificationMessage
		{
			String^ get();
			void set(String^ value);
		}
	};
}