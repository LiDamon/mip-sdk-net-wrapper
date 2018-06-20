#include "UserRoles.h"

#include "Converters.h"

namespace NetMip
{
	array<String^>^ UserRoles::Users::get()
	{
		mip::UserList mipUsers = this->Instance->Users();

		auto arr = gcnew array<String^>((int)mipUsers.size());

		int i = 0;
		for (auto const& mipUser : mipUsers)
		{
			arr[i++] = std_string_to_net_string(mipUser);
		}

		return arr;
	}

	array<String^>^ UserRoles::Roles::get()
	{
		mip::RoleList mipRoles = this->Instance->Roles();

		auto arr = gcnew array<String^>((int)mipRoles.size());

		int i = 0;
		for (auto const& mipRole : mipRoles)
		{
			arr[i++] = std_string_to_net_string(mipRole);
		}

		return arr;
	}
}
