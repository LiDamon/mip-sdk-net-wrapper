#pragma once

#include "Converters.h"
#include "Identity.h"

namespace NetMip
{
	Identity::Identity()
		: ManagedObject(new mip::Identity())
	{
	}

	Identity::Identity(String^ email)
		: ManagedObject(new mip::Identity(net_string_to_std_string(email)))
	{
	}

	Identity::Identity(mip::Identity* identity)
		: ManagedObject(false, identity)
	{
	}

	String^ Identity::Email::get()
	{
		return std_string_to_net_string(m_Instance->GetEmail());
	}
}