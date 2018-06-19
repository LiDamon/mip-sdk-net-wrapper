#pragma once

#include "UserPolicy.h"

#include "Converters.h"

namespace NetMip
{
	bool UserPolicy::AccessCheck(String^ right)
	{
		return m_Instance->get()->AccessCheck(net_string_to_std_string(right));
	}

	UserPolicyType UserPolicy::UserPolicyType::get()
	{
		return (NetMip::UserPolicyType)(m_Instance->get()->GetType());
	}

	String^ UserPolicy::Name::get()
	{
		return std_string_to_net_string(m_Instance->get()->GetName());
	}

	String^ UserPolicy::Description::get()
	{
		return std_string_to_net_string(m_Instance->get()->GetDescription());
	}

	NetMip::TemplateDescriptor^ UserPolicy::TemplateDescriptor::get()
	{
		std::shared_ptr<mip::TemplateDescriptor>* ptrTemplateDescriptor = new std::shared_ptr<mip::TemplateDescriptor>(
			m_Instance->get()->GetTemplateDescriptor());

		return gcnew NetMip::TemplateDescriptor(ptrTemplateDescriptor);
	}

	NetMip::PolicyDescriptor^ UserPolicy::PolicyDescriptor::get()
	{
		std::shared_ptr<mip::PolicyDescriptor>* ptrPolicyDescriptor = new std::shared_ptr<mip::PolicyDescriptor>(
			m_Instance->get()->GetPolicyDescriptor());

		return gcnew NetMip::PolicyDescriptor(ptrPolicyDescriptor);
	}

	String^ UserPolicy::Owner::get()
	{
		return std_string_to_net_string(m_Instance->get()->GetOwner());
	}

	String^ UserPolicy::IssuedTo::get()
	{
		return std_string_to_net_string(m_Instance->get()->GetIssuedTo());
	}

	bool UserPolicy::IsIssuedToOwner::get()
	{
		return m_Instance->get()->IsIssuedToOwner();
	}

	String^ UserPolicy::ContentId::get()
	{
		return std_string_to_net_string(m_Instance->get()->GetContentId());
	}

	bool UserPolicy::DoesUseDeprecatedAlgorithms::get()
	{
		return m_Instance->get()->DoesUseDeprecatedAlgorithms();
	}

	bool UserPolicy::IsAuditedExtractAllowed::get()
	{
		return m_Instance->get()->IsAuditedExtractAllowed();
	}

}