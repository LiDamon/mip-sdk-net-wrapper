#include <string>

#include "mip\common_types.h"

#include "ApplicationInfo.h"
#include "Converters.h"

using namespace System;

namespace CLI
{
	ApplicationInfo::ApplicationInfo(String^ applicationId, String^ friendlyName)
		: ManagedObject(new mip::ApplicationInfo())
	{
		m_Instance->applicationId = net_string_to_std_string(applicationId);
		m_Instance->friendlyName = net_string_to_std_string(friendlyName);
	}

	String^ ApplicationInfo::ApplicationId::get()
	{
		return std_string_to_net_string(m_Instance->applicationId);
	}

	String^ ApplicationInfo::FriendlyName::get()
	{
		return std_string_to_net_string(m_Instance->friendlyName);
	}
}