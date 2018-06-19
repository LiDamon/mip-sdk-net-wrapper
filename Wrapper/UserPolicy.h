#pragma once

#include "mip/rms/user_policy.h"

#include "ManagedObject.h"
#include "PolicyDescriptor.h"
#include "TemplateDescriptor.h"
#include "UserPolicyType.h"

using namespace System;

namespace NetMip
{
	public ref class UserPolicy : public ManagedObject<std::shared_ptr<mip::UserPolicy>>
	{
	internal:
		UserPolicy(std::shared_ptr<mip::UserPolicy>* contentLabel)
			: ManagedObject(contentLabel)
		{}

	public:
		bool AccessCheck(String^ right);

		property NetMip::UserPolicyType UserPolicyType
		{
			NetMip::UserPolicyType get();
		}

		property String^ Name
		{
			String^ get();
		}

		property String^ Description
		{
			String^ get();
		}

		property TemplateDescriptor^ TemplateDescriptor
		{
			NetMip::TemplateDescriptor^ get();
		}

		property PolicyDescriptor^ PolicyDescriptor
		{
			NetMip::PolicyDescriptor^ get();
		}

		property String^ Owner
		{
			String^ get();
		}

		property String^ IssuedTo
		{
			String^ get();
		}

		property bool IsIssuedToOwner
		{
			bool get();
		}

		property String^ ContentId
		{
			String^ get();
		}


		property bool DoesUseDeprecatedAlgorithms
		{
			bool get();
		}

		property bool IsAuditedExtractAllowed
		{
			bool get();
		}
	};
}