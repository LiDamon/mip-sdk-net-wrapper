#pragma once

#include <exception>
#include <memory>

#include "mip/file/file_profile.h"

namespace NetMip
{
	private class FileProfileObserverImpl final : public mip::FileProfile::Observer
	{
	public:
		virtual void OnLoadSuccess(const std::shared_ptr<mip::FileProfile>& profile, const std::shared_ptr<void>& context) override;
		virtual void OnLoadFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context) override;
		
		virtual void OnListEnginesSuccess(const std::vector<std::string>& engineIds, const std::shared_ptr<void>& context) override;
		virtual void OnListEnginesError(const std::exception_ptr& error, const std::shared_ptr<void>& context) override;

		virtual void OnUnloadEngineSuccess(const std::shared_ptr<void>& context) override;
		virtual void OnUnloadEngineError(const std::exception_ptr& error, const std::shared_ptr<void>& context) override;

		virtual void OnAddEngineSuccess(const std::shared_ptr<mip::FileEngine>& engine, const std::shared_ptr<void>& context) override;
		virtual void OnAddEngineError(const std::exception_ptr& error, const std::shared_ptr<void>& context) override;

		virtual void OnDeleteEngineSuccess(const std::shared_ptr<void>& context) override;
		virtual void OnDeleteEngineError(const std::exception_ptr& error, const std::shared_ptr<void>& context) override;
	};
}
