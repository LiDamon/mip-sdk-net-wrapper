#pragma once

#include <exception>
#include <memory>

#include "mip/common_types.h"
#include "mip/file/file_profile.h"
#include "mip/rms/user_policy.h"

namespace CLI
{
	private class FileHandlerObserverImpl final : public mip::FileHandler::Observer
	{
	public:
		virtual void OnGetLabelSuccess(const std::shared_ptr<mip::ContentLabel>& label, const std::shared_ptr<void>& context) override;
		virtual void OnGetLabelFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context) override;
		virtual void OnGetProtectionSuccess(const std::shared_ptr<mip::UserPolicy>& userPolicy, const std::shared_ptr<void>& context) override;
		virtual void OnGetProtectionFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context) override;
		virtual void OnCommitSuccess(bool committed, const std::shared_ptr<void>& context) override;
		virtual void OnCommitFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context) override;
	};
}
