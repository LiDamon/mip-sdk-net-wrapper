#include "ContentLabel.h"

#include "Converters.h"
#include "Label.h"

namespace NetMip
{
	NetMip::Label^ ContentLabel::Label::get()
	{
		return gcnew NetMip::Label(m_Instance->get()->GetLabel().get());
	}

	String^ ContentLabel::CreationTime::get()
	{
		return std_string_to_net_string(m_Instance->get()->GetCreationTime());
	}

	NetMip::AssignmentMethod ContentLabel::AssignmentMethod::get()
	{
		auto mipAssignmentMethod = m_Instance->get()->GetAssignmentMethod();
		auto assignmentMethod = (NetMip::AssignmentMethod)mipAssignmentMethod;
		return assignmentMethod;
	}
}