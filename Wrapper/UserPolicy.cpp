#pragma once

#include "UserPolicy.h"

#include "Converters.h"

namespace NetMip
{
	bool UserPolicy::AccessCheck(String^ right)
	{
		return this->Instance->get()->AccessCheck(net_string_to_std_string(right));
	}

	UserPolicyType UserPolicy::UserPolicyType::get()
	{
		return (NetMip::UserPolicyType)(this->Instance->get()->GetType());
	}

	String^ UserPolicy::Name::get()
	{
		return std_string_to_net_string(this->Instance->get()->GetName());
	}

	String^ UserPolicy::Description::get()
	{
		return std_string_to_net_string(this->Instance->get()->GetDescription());
	}

	NetMip::TemplateDescriptor^ UserPolicy::TemplateDescriptor::get()
	{
		std::shared_ptr<mip::TemplateDescriptor>* ptrTemplateDescriptor = new std::shared_ptr<mip::TemplateDescriptor>(
			this->Instance->get()->GetTemplateDescriptor());

		return gcnew NetMip::TemplateDescriptor(true, ptrTemplateDescriptor);
	}

	NetMip::PolicyDescriptor^ UserPolicy::PolicyDescriptor::get()
	{
		std::shared_ptr<mip::PolicyDescriptor>* ptrPolicyDescriptor = new std::shared_ptr<mip::PolicyDescriptor>(
			this->Instance->get()->GetPolicyDescriptor());

		return gcnew NetMip::PolicyDescriptor(true, ptrPolicyDescriptor);
	}

	String^ UserPolicy::Owner::get()
	{
		return std_string_to_net_string(this->Instance->get()->GetOwner());
	}

	String^ UserPolicy::IssuedTo::get()
	{
		return std_string_to_net_string(this->Instance->get()->GetIssuedTo());
	}

	bool UserPolicy::IsIssuedToOwner::get()
	{
		return this->Instance->get()->IsIssuedToOwner();
	}

	String^ UserPolicy::ContentId::get()
	{
		return std_string_to_net_string(this->Instance->get()->GetContentId());
	}

	bool UserPolicy::DoesUseDeprecatedAlgorithms::get()
	{
		return this->Instance->get()->DoesUseDeprecatedAlgorithms();
	}

	bool UserPolicy::IsAuditedExtractAllowed::get()
	{
		return this->Instance->get()->IsAuditedExtractAllowed();
	}

}