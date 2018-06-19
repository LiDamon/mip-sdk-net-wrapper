#include "ContentLabel.h"

#include "Converters.h"
#include "Label.h"

namespace CLI
{
	CLI::Label^ ContentLabel::Label::get()
	{
		return gcnew CLI::Label(m_Instance->get()->GetLabel().get());
	}

	String^ ContentLabel::CreationTime::get()
	{
		return std_string_to_net_string(m_Instance->get()->GetCreationTime());
	}

	CLI::AssignmentMethod ContentLabel::AssignmentMethod::get()
	{
		auto mipAssignmentMethod = m_Instance->get()->GetAssignmentMethod();
		auto assignmentMethod = (CLI::AssignmentMethod)mipAssignmentMethod;
		return assignmentMethod;
	}
}