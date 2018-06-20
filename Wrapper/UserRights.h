#pragma once

#include "mip/rms/user_rights.h"

#include "ManagedObject.h"

using namespace System;

namespace NetMip
{
	public ref class UserRights : public ManagedObject<mip::UserRights>
	{
	internal:
		UserRights(bool owner, mip::UserRights* userRoles)
			: ManagedObject(owner, userRoles)
		{}

	public:
		property array<String^>^ Users
		{
			array<String^>^ get();
		}

		property array<String^>^ Rights
		{
			array<String^>^ get();
		}

	};
}
