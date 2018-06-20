#pragma once

#include "Converters.h"
#include "Identity.h"

namespace NetMip
{
	Identity::Identity()
		: Identity(true, new mip::Identity())
	{
	}

	Identity::Identity(String^ email)
		: Identity(true, new mip::Identity(net_string_to_std_string(email)))
	{
	}

	Identity::Identity(bool owner, mip::Identity* identity)
		: ManagedObject(owner, identity)
	{
	}

	String^ Identity::Email::get()
	{
		return std_string_to_net_string(this->Instance->GetEmail());
	}
}