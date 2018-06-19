#include "FileHandlerObserverImpl.h"

#include "ContentLabel.h"
#include "Converters.h"
#include "ExceptionHelper.h"
#include "FileHandler.h"
#include "LateValue.h"
#include "UnmanagedObject.h"

using namespace System;

namespace CLI
{
	void FileHandlerObserverImpl::OnGetLabelSuccess(const std::shared_ptr<mip::ContentLabel>& label, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<CLI::UnmanagedObject<CLI::LateValue<CLI::ContentLabel^>>*>(context.get());
		CLI::LateValue<CLI::ContentLabel^>^ lateValue = unmanagedLateValue->GetInstance();

		std::shared_ptr<mip::ContentLabel>* ptrContentLabel = new std::shared_ptr<mip::ContentLabel>(label);

		lateValue->SetValue(gcnew ContentLabel(ptrContentLabel));
	}

	void FileHandlerObserverImpl::OnGetLabelFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<CLI::UnmanagedObject<CLI::LateValue<CLI::ContentLabel^>>*>(context.get());
		CLI::LateValue<CLI::ContentLabel^>^ lateValue = unmanagedLateValue->GetInstance();

		lateValue->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}
	

	// TODO:
	//
	//void FileHandlerObserverImpl::OnGetProtectionSuccess(const std::shared_ptr<mip::UserPolicy>& userPolicy, const std::shared_ptr<void>& context)
	//{
	//}
	//
	//void FileHandlerObserverImpl::OnGetProtectionFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	//{
	//	auto unmanagedLateValue = static_cast<CLI::UnmanagedObject<CLI::LateValue<CLI::UserPolicy^>>*>(context.get());
	//	CLI::LateValue<CLI::UserPolicy^>^ lateValue = unmanagedLateValue->GetInstance();
	//
	//	lateValue->SetError(gcnew System::Exception(getExceptionMessage(error)));
	//}


	void FileHandlerObserverImpl::OnCommitSuccess(bool committed, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<CLI::UnmanagedObject<CLI::LateValue<bool>>*>(context.get());
		CLI::LateValue<bool>^ lateValue = unmanagedLateValue->GetInstance();

		lateValue->SetValue(committed);
	}

	void FileHandlerObserverImpl::OnCommitFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<CLI::UnmanagedObject<CLI::LateValue<bool>>*>(context.get());
		CLI::LateValue<bool>^ lateValue = unmanagedLateValue->GetInstance();

		lateValue->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}
}
