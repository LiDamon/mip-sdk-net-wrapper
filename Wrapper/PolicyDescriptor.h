#pragma once

#include "mip/rms/policy_descriptor.h"

#include "ManagedObject.h"
#include "UserRights.h"
#include "UserRoles.h"

using namespace System;
using namespace System::Collections::Generic;

namespace NetMip
{
	public ref class PolicyDescriptor : public ManagedObject<std::shared_ptr<mip::PolicyDescriptor>>
	{
	internal:
		PolicyDescriptor(bool owner, std::shared_ptr<mip::PolicyDescriptor>* policyDescriptor)
			: ManagedObject(owner, policyDescriptor)
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

		property Dictionary<String^, String^>^ EncryptedAppData
		{
			Dictionary<String^, String^>^ get();
			void set(Dictionary<String^, String^>^ value);
		}

		property Dictionary<String^, String^>^ SignedAppData
		{
			Dictionary<String^, String^>^ get();
			void set(Dictionary<String^, String^>^ value);
		}
	};
}