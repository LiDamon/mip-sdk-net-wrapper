#include "FileHandlerObserverImpl.h"

#include "ContentLabel.h"
#include "Converters.h"
#include "ExceptionHelper.h"
#include "FileHandler.h"
#include "LateValue.h"
#include "UnmanagedObject.h"
#include "UserPolicy.h"

using namespace System;

namespace NetMip
{
	void FileHandlerObserverImpl::OnGetLabelSuccess(const std::shared_ptr<mip::ContentLabel>& label, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<NetMip::UnmanagedObject<NetMip::LateValue<NetMip::ContentLabel^>>*>(context.get());
		NetMip::LateValue<NetMip::ContentLabel^>^ lateValue = unmanagedLateValue->GetInstance();

		std::shared_ptr<mip::ContentLabel>* ptrContentLabel = new std::shared_ptr<mip::ContentLabel>(label);

		lateValue->SetValue(gcnew ContentLabel(true, ptrContentLabel));
	}

	void FileHandlerObserverImpl::OnGetLabelFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<NetMip::UnmanagedObject<NetMip::LateValue<NetMip::ContentLabel^>>*>(context.get());
		NetMip::LateValue<NetMip::ContentLabel^>^ lateValue = unmanagedLateValue->GetInstance();

		lateValue->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}
	

	void FileHandlerObserverImpl::OnGetProtectionSuccess(const std::shared_ptr<mip::UserPolicy>& userPolicy, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<NetMip::UnmanagedObject<NetMip::LateValue<NetMip::UserPolicy^>>*>(context.get());
		NetMip::LateValue<NetMip::UserPolicy^>^ lateValue = unmanagedLateValue->GetInstance();

		std::shared_ptr<mip::UserPolicy>* ptrUserPolicy = new std::shared_ptr<mip::UserPolicy>(userPolicy);

		lateValue->SetValue(gcnew UserPolicy(true, ptrUserPolicy));
	}
	
	void FileHandlerObserverImpl::OnGetProtectionFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<NetMip::UnmanagedObject<NetMip::LateValue<NetMip::UserPolicy^>>*>(context.get());
		NetMip::LateValue<NetMip::UserPolicy^>^ lateValue = unmanagedLateValue->GetInstance();
	
		lateValue->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}


	void FileHandlerObserverImpl::OnCommitSuccess(bool committed, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<NetMip::UnmanagedObject<NetMip::LateValue<bool>>*>(context.get());
		NetMip::LateValue<bool>^ lateValue = unmanagedLateValue->GetInstance();

		lateValue->SetValue(committed);
	}

	void FileHandlerObserverImpl::OnCommitFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<NetMip::UnmanagedObject<NetMip::LateValue<bool>>*>(context.get());
		NetMip::LateValue<bool>^ lateValue = unmanagedLateValue->GetInstance();

		lateValue->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}
}
