#pragma once

#include "TemplateDescriptor.h"

#include "Converters.h"

namespace NetMip
{
	String^ TemplateDescriptor::TemplateId::get()
	{
		return std_string_to_net_string(m_Instance->get()->TemplateId());
	}

	String^ TemplateDescriptor::Name::get()
	{
		return std_string_to_net_string(m_Instance->get()->Name());
	}

	String^ TemplateDescriptor::Description::get()
	{
		return std_string_to_net_string(m_Instance->get()->Description());
	}
}