#pragma once

#include "mip/rms/user_roles.h"

#include "ManagedObject.h"

using namespace System;

namespace NetMip
{
	public ref class UserRoles : public ManagedObject<mip::UserRoles>
	{
	internal:
		UserRoles(bool owner, mip::UserRoles* userRoles)
			: ManagedObject(owner, userRoles)
		{}

	public:
		property array<String^>^ Users
		{
			array<String^>^ get();
		}

		property array<String^>^ Roles
		{
			array<String^>^ get();
		}

	};
}
