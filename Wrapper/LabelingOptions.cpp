#include "LabelingOptions.h"

#include "mip/common_types.h"

#include "Converters.h"

namespace CLI
{
	LabelingOptions::LabelingOptions(AssignmentMethod method, String^ justificationMessage)
		: ManagedObject(new mip::LabelingOptions((mip::AssignmentMethod)method, net_string_to_std_string(justificationMessage)))
	{
	}

	AssignmentMethod LabelingOptions::Method::get()
	{
		return (CLI::AssignmentMethod)(m_Instance->GetAssignmentMethod());
	}

	void LabelingOptions::Method::set(AssignmentMethod value)
	{
		m_Instance->SetMethod((mip::AssignmentMethod)value);
	}

	String^ LabelingOptions::JustificationMessage::get()
	{
		return std_string_to_net_string(m_Instance->GetJustificationMessage());
	}

	void LabelingOptions::JustificationMessage::set(String^ value)
	{
		m_Instance->SetJustificationMessage(net_string_to_std_string(value));
	}
}
