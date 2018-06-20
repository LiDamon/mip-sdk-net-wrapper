#include <string>

#include "mip\common_types.h"

#include "ApplicationInfo.h"
#include "Converters.h"

using namespace System;

namespace NetMip
{
	ApplicationInfo::ApplicationInfo(String^ applicationId, String^ friendlyName)
		: ManagedObject(true, new mip::ApplicationInfo())
	{
		this->Instance->applicationId = net_string_to_std_string(applicationId);
		this->Instance->friendlyName = net_string_to_std_string(friendlyName);
	}

	String^ ApplicationInfo::ApplicationId::get()
	{
		return std_string_to_net_string(this->Instance->applicationId);
	}

	String^ ApplicationInfo::FriendlyName::get()
	{
		return std_string_to_net_string(this->Instance->friendlyName);
	}
}