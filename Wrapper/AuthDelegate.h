#pragma once

#include <vcclr.h>

#include "mip/common_types.h"

#include "Identity.h"
#include "ManagedObject.h"

using namespace System;

namespace CLI
{
	// Forward declare
	class AuthDelegateBridgeImpl;
	ref class AuthDelegate;

	public ref class AuthDelegate abstract
	{
	public:
		ref class OAuth2Challenge : public ManagedObject<mip::AuthDelegate::OAuth2Challenge>
		{
		internal:
			OAuth2Challenge(mip::AuthDelegate::OAuth2Challenge* challenge);

		public:
			OAuth2Challenge(String^ authority, String^ resource);

			property String^ Authority
			{
				String^ get();
			}

			property String^ Resource
			{
				String^ get();
			}
		};

		ref class OAuth2Token : public ManagedObject<mip::AuthDelegate::OAuth2Token>
		{
		internal:
			OAuth2Token(mip::AuthDelegate::OAuth2Token* token);

		public:
			OAuth2Token();
			OAuth2Token(String^ accessToken);

			property String^ AccessToken
			{
				String^ get();
				void set(String^ value);
			}
		};


	public:
		virtual ~AuthDelegate();

		!AuthDelegate();

		virtual bool AcquireOAuth2Token(
			Identity^ identity,
			OAuth2Challenge^ challenge,
			OAuth2Token^ token) abstract;

	protected:
		AuthDelegate();

	internal:
		std::shared_ptr<mip::AuthDelegate>* GetBridge();

	private:
		std::shared_ptr<mip::AuthDelegate>* m_bridge;
	};

	private class AuthDelegateBridgeImpl final : mip::AuthDelegate
	{
	public:
		AuthDelegateBridgeImpl(gcroot<CLI::AuthDelegate^> ad) : m_cli(ad) { }

		~AuthDelegateBridgeImpl();

		virtual bool AcquireOAuth2Token(
			const mip::Identity& identity,
			const mip::AuthDelegate::OAuth2Challenge& challenge,
			mip::AuthDelegate::OAuth2Token& token) override;

	private:
		gcroot<CLI::AuthDelegate^> m_cli;
	};
}