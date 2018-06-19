#include "UserRights.h"

#include "Converters.h"

namespace NetMip
{
	array<String^>^ UserRights::Users::get()
	{
		mip::UserList mipUsers = m_Instance->Users();

		auto arr = gcnew array<String^>((int)mipUsers.size());

		int i = 0;
		for (auto const& mipUser : mipUsers)
		{
			arr[i++] = std_string_to_net_string(mipUser);
		}

		return arr;
	}

	array<String^>^ UserRights::Rights::get()
	{
		mip::RightList mipRights = m_Instance->Rights();

		auto arr = gcnew array<String^>((int)mipRights.size());

		int i = 0;
		for (auto const& mipRight : mipRights)
		{
			arr[i++] = std_string_to_net_string(mipRight);
		}

		return arr;
	}
}
