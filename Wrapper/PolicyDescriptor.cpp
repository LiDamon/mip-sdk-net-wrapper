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

	Dictionary<String^, String^>^ PolicyDescriptor::EncryptedAppData::get()
	{
		auto mipEncryptedAppData = m_Instance->get()->GetEncryptedAppData();

		auto dictionary = gcnew Dictionary<String^, String^>((int)mipEncryptedAppData.size());

		for (auto const& mipEntry : mipEncryptedAppData)
		{
			dictionary->Add(
				std_string_to_net_string(mipEntry.first),
				std_string_to_net_string(mipEntry.second));
		}

		return dictionary;
	}

	void PolicyDescriptor::EncryptedAppData::set(Dictionary<String^, String^>^ value)
	{
		std::unordered_map<std::string, std::string> map(value->Count);

		for each (auto pair in value)
		{
			std::pair<std::string, std::string> stdPair(
				net_string_to_std_string(pair.Key),
				net_string_to_std_string(pair.Value));

			map.insert(stdPair);
		}

		m_Instance->get()->SetEncryptedAppData(map);
	}

	Dictionary<String^, String^>^ PolicyDescriptor::SignedAppData::get()
	{
		auto mipSignedAppData = m_Instance->get()->GetSignedAppData();

		auto dictionary = gcnew Dictionary<String^, String^>((int)mipSignedAppData.size());

		for (auto const& mipEntry : mipSignedAppData)
		{
			dictionary->Add(
				std_string_to_net_string(mipEntry.first),
				std_string_to_net_string(mipEntry.second));
		}

		return dictionary;
	}

	void PolicyDescriptor::SignedAppData::set(Dictionary<String^, String^>^ value)
	{
		std::unordered_map<std::string, std::string> map(value->Count);

		for each (auto pair in value)
		{
			std::pair<std::string, std::string> stdPair(
				net_string_to_std_string(pair.Key),
				net_string_to_std_string(pair.Value));

			map.insert(stdPair);
		}

		m_Instance->get()->SetSignedAppData(map);
	}
}