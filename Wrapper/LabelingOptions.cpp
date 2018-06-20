#include "LabelingOptions.h"

#include "mip/common_types.h"

#include "Converters.h"

namespace NetMip
{
	LabelingOptions::LabelingOptions(AssignmentMethod method, String^ justificationMessage)
		: ManagedObject(true, new mip::LabelingOptions((mip::AssignmentMethod)method, net_string_to_std_string(justificationMessage)))
	{
	}

	AssignmentMethod LabelingOptions::Method::get()
	{
		return (NetMip::AssignmentMethod)(this->Instance->GetAssignmentMethod());
	}

	void LabelingOptions::Method::set(AssignmentMethod value)
	{
		this->Instance->SetMethod((mip::AssignmentMethod)value);
	}

	String^ LabelingOptions::JustificationMessage::get()
	{
		return std_string_to_net_string(this->Instance->GetJustificationMessage());
	}

	void LabelingOptions::JustificationMessage::set(String^ value)
	{
		this->Instance->SetJustificationMessage(net_string_to_std_string(value));
	}
}
