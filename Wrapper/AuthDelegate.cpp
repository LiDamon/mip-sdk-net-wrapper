#pragma once

#include "AuthDelegate.h"
#include "Converters.h"

namespace NetMip
{
	/**************************************
	 * NetMip::AuthDelegate::OAuth2Challenge
	 **************************************/

	//AuthDelegate::OAuth2Challenge::OAuth2Challenge(String^ authority, String^ resource)
	//	: ManagedObject(new mip::AuthDelegate::OAuth2Challenge(net_string_to_std_string(authority), net_string_to_std_string(resource)))
	//{
	//}

	AuthDelegate::OAuth2Challenge::OAuth2Challenge(bool owner, mip::AuthDelegate::OAuth2Challenge* challenge)
		: ManagedObject(owner, challenge)
	{
	}

	String^ AuthDelegate::OAuth2Challenge::Authority::get()
	{
		return std_string_to_net_string(this->Instance->GetAuthority());
	}

	String^ AuthDelegate::OAuth2Challenge::Resource::get()
	{
		return std_string_to_net_string(this->Instance->GetResource());
	}


	/**************************************
	 * NetMip::AuthDelegate::OAuth2Token
	 **************************************/

	//AuthDelegate::OAuth2Token::OAuth2Token()
	//	: ManagedObject(new mip::AuthDelegate::OAuth2Token())
	//{
	//}

	//AuthDelegate::OAuth2Token::OAuth2Token(String^ accessToken)
	//	: ManagedObject(new mip::AuthDelegate::OAuth2Token(net_string_to_std_string(accessToken)))
	//{
	//}

	AuthDelegate::OAuth2Token::OAuth2Token(mip::AuthDelegate::OAuth2Token* token)
		: ManagedObject(false, token)
	{
	}

	String^ AuthDelegate::OAuth2Token::AccessToken::get()
	{
		return std_string_to_net_string(this->Instance->GetAccessToken());
	}

	void AuthDelegate::OAuth2Token::AccessToken::set(String^ value)
	{
		this->Instance->SetAccessToken(net_string_to_std_string(value));
	}


	/**************************************
	 * NetMip::AuthDelegate
	 **************************************/

	AuthDelegate::AuthDelegate()
	{
		mip::AuthDelegate* ptr = (mip::AuthDelegate*)new AuthDelegateBridgeImpl(this);
		m_bridge = new std::shared_ptr<mip::AuthDelegate>(ptr);
	}

	AuthDelegate::~AuthDelegate()
	{
		this->!AuthDelegate();
	}

	AuthDelegate::!AuthDelegate()
	{
		if (m_bridge != nullptr)
		{
			delete m_bridge;
			m_bridge = nullptr;
		}
	}

	std::shared_ptr<mip::AuthDelegate>* AuthDelegate::GetBridge()
	{
		return (std::shared_ptr<mip::AuthDelegate>*)m_bridge;
	}


	/**************************************
	 * NetMip::AuthDelegateBridge
	 **************************************/

	bool AuthDelegateBridgeImpl::AcquireOAuth2Token(
		const mip::Identity& identity,
		const mip::AuthDelegate::OAuth2Challenge& challenge,
		mip::AuthDelegate::OAuth2Token& token)
	{
		bool result = m_cli->AcquireOAuth2Token(
			gcnew NetMip::Identity(true, new mip::Identity(identity)),
			gcnew NetMip::AuthDelegate::OAuth2Challenge(true, new mip::AuthDelegate::OAuth2Challenge(challenge)),
			gcnew NetMip::AuthDelegate::OAuth2Token(&token));

		return result;
	}

	AuthDelegateBridgeImpl::~AuthDelegateBridgeImpl()
	{
	}
}