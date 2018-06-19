#pragma once

#include "mip/rms/policy_descriptor.h"

#include "ManagedObject.h"
#include "UserRights.h"
#include "UserRoles.h"

using namespace System;

namespace NetMip
{
	public ref class PolicyDescriptor : public ManagedObject<std::shared_ptr<mip::PolicyDescriptor>>
	{
	internal:
		PolicyDescriptor(std::shared_ptr<mip::PolicyDescriptor>* contentLabel)
			: ManagedObject(contentLabel)
		{}

	public:
		property String ^ Name
		{
			String^ get();
			void set(String^ value);
		}

		property String ^ Description
		{
			String^ get();
			void set(String^ value);
		}

		array<UserRights^>^ GetUserRightsList();

		array<UserRoles^>^ GetUserRolesList();

		//TODO: Convertion required between DateTime and std::chrono::time_point<std::chrono::system_clock>

		//property DateTime ContentValidUntil
		//{
		//	DateTime get();
		//	void set(DateTime value);
		//}

		property bool AllowOfflineAccess
		{
			bool get();
			void set(bool value);
		}

		property String ^ Referrer
		{
			String^ get();
			void set(String^ value);
		}

		//TODO: Complete the PolicyDescriptor API

		///**
		//* @brief Gets app-specific data that was encrypted
		//*
		//* @return App-specific data
		//*
		//* @note A UserPolicy may contain a dictionary of app-specific data that was encrypted by the RMS service. This
		//* encrypted data is independent of the signed data accessible via PolicyDescriptor::GetSignedAppData
		//*/
		//virtual const AppDataHashMap& GetEncryptedAppData() = 0;

		///**
		//* @brief Sets app-specific data that should be encrypted
		//*
		//* @param value App-specific data
		//*
		//* @note An application can specify a dictionary of app-specific data that will be encrypted by the RMS service. This
		//* encrypted data is independent of the signed data set by PolicyDescriptor::SetSignedAppData.
		//*/
		//virtual void SetEncryptedAppData(const AppDataHashMap& value) = 0;

		///**
		//* @brief Gets the app-specific data that was signed
		//*
		//* @return App-specific data
		//*
		//* @note A UserPolicy may contain a dictionary of app-specific data that was signed by the RMS service. This signed
		//* data is independent of the encrypted data accessible via PolicyDescriptor::GetEncryptedAppData
		//*/
		//virtual const AppDataHashMap& GetSignedAppData() = 0;

		///**
		//* @brief Sets app-specific data that should be signed
		//*
		//* @param value App-specific data
		//*
		//* @note An application can specify a dictionary of app-specific data that will be signed by the RMS service. This
		//* signed data is independent of the encrypted data set by PolicyDescriptor::SetEncryptedAppData.
		//*/
		//virtual void SetSignedAppData(const AppDataHashMap& value) = 0;
	};
}