#pragma once

#include "mip/rms/policy_descriptor.h"

#include "ManagedObject.h"

using namespace System;

namespace CLI
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

		///**
		//* @brief Gets collection of users-to-rights mappings

		//* @return Collection of users-to-rights mappings
		//*
		//* @note The value of the UserRightsList property will be empty if the current user doesn't have access to the user
		//* rights information (i.e. is not the owner and does not have the VIEWRIGHTSDATA right).
		//*/
		//virtual const std::vector<UserRights>& GetUserRightsList() const = 0;

		///**
		//* @brief Gets collection of users-to-roles mappings
		//*
		//* @return Collection of users-to-roles mappings
		//*/
		//virtual const std::vector<mip::UserRoles>& GetUserRolesList() = 0;

		///**
		//* @brief Gets policy expiration time
		//*
		//* @return Policy expiration time
		//*/
		//virtual const std::chrono::time_point<std::chrono::system_clock>& GetContentValidUntil() = 0;

		///**
		//* @brief Sets policy expiration time
		//*
		//* @param value Policy expiration time
		//*/
		//virtual void SetContentValidUntil(const std::chrono::time_point<std::chrono::system_clock>& value) = 0;

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