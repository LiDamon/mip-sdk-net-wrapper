#pragma once

#include "PolicyDescriptor.h"

#include "Converters.h"

namespace CLI
{
	String^ PolicyDescriptor::Name::get()
	{
		return std_string_to_net_string(m_Instance->get()->GetName());
	}

	void PolicyDescriptor::Name::set(String^ value)
	{
		return m_Instance->get()->SetName(net_string_to_std_string(value));
	}


	String^ PolicyDescriptor::Description::get()
	{
		return std_string_to_net_string(m_Instance->get()->GetDescription());
	}

	void PolicyDescriptor::Description::set(String^ value)
	{
		return m_Instance->get()->SetDescription(net_string_to_std_string(value));
	}


	bool PolicyDescriptor::AllowOfflineAccess::get()
	{
		return m_Instance->get()->DoesAllowOfflineAccess();
	}

	void PolicyDescriptor::AllowOfflineAccess::set(bool value)
	{
		return m_Instance->get()->SetAllowOfflineAccess(value);
	}


	String^ PolicyDescriptor::Referrer::get()
	{
		return std_string_to_net_string(m_Instance->get()->GetReferrer());
	}

	void PolicyDescriptor::Referrer::set(String^ value)
	{
		return m_Instance->get()->SetReferrer(net_string_to_std_string(value));
	}
}