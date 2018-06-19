#pragma once

#include "PolicyDescriptor.h"

#include "Converters.h"

namespace NetMip
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

	array<UserRights^>^ PolicyDescriptor::GetUserRightsList()
	{
		auto mipUserRightsList = m_Instance->get()->GetUserRightsList();

		auto arr = gcnew array<UserRights^>((int)mipUserRightsList.size());

		int i = 0;
		for (auto const& mipUserRights : mipUserRightsList)
		{
			mip::UserRights* ptr = (mip::UserRights*)(&(mipUserRights));
			arr[i++] = gcnew UserRights(ptr);
		}

		return arr;
	}

	array<UserRoles^>^ PolicyDescriptor::GetUserRolesList()
	{
		auto mipUserRolesList = m_Instance->get()->GetUserRolesList();

		auto arr = gcnew array<UserRoles^>((int)mipUserRolesList.size());

		int i = 0;
		for (auto const& mipUserRoles : mipUserRolesList)
		{
			mip::UserRoles* ptr = (mip::UserRoles*)(&(mipUserRoles));
			arr[i++] = gcnew UserRoles(ptr);
		}

		return arr;
	}


	//TODO: Convertion required between DateTime and std::chrono::time_point<std::chrono::system_clock>

	//DateTime PolicyDescriptor::ContentValidUntil::get()
	//{
	//}

	//void PolicyDescriptor::ContentValidUntil::set(DateTime value)
	//{
	//}


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