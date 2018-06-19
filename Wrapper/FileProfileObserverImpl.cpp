#include "FileProfileObserverImpl.h"

#include "Converters.h"
#include "ExceptionHelper.h"
#include "FileProfile.h"
#include "LateValue.h"
#include "UnmanagedObject.h"

using namespace System;

namespace CLI
{
	void FileProfileObserverImpl::OnLoadSuccess(const std::shared_ptr<mip::FileProfile>& profile, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<CLI::UnmanagedObject<CLI::LateValue<CLI::FileProfile^>>*>(context.get());
		CLI::LateValue<CLI::FileProfile^>^ lateValue = unmanagedLateValue->GetInstance();

		std::shared_ptr<mip::FileProfile>* ptrProfile = new std::shared_ptr<mip::FileProfile>(profile);

		lateValue->SetValue(gcnew FileProfile(ptrProfile));
	}

	void FileProfileObserverImpl::OnLoadFailure(const std::exception_ptr & error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<CLI::UnmanagedObject<CLI::LateValue<CLI::FileProfile^>>*>(context.get());
		CLI::LateValue<CLI::FileProfile^>^ lateValue = unmanagedLateValue->GetInstance();

		lateValue->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}

	void FileProfileObserverImpl::OnListEnginesSuccess(const std::vector<std::string>& engineIds, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<CLI::UnmanagedObject<CLI::LateValue<array<String^>^>>*>(context.get());
		CLI::LateValue<array<String^>^>^ lateValue = unmanagedLateValue->GetInstance();

		auto arr = gcnew array<String^>((int)engineIds.size());

		int i = 0;
		for (auto const& engineId : engineIds)
		{
			arr[i++] = std_string_to_net_string(engineId);
		}


		lateValue->SetValue(arr);
	}

	void FileProfileObserverImpl::OnListEnginesError(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<CLI::UnmanagedObject<CLI::LateValue<String^>>*>(context.get());
		CLI::LateValue<String^>^ lateValue = unmanagedLateValue->GetInstance();

		lateValue->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}


	void FileProfileObserverImpl::OnUnloadEngineSuccess(const std::shared_ptr<void>& context)
	{
		auto unmanagedLateAction = static_cast<CLI::UnmanagedObject<CLI::LateAction>*>(context.get());
		CLI::LateAction^ lateAction = unmanagedLateAction->GetInstance();

		lateAction->Complete();
	}

	void FileProfileObserverImpl::OnUnloadEngineError(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateAction = static_cast<CLI::UnmanagedObject<CLI::LateAction>*>(context.get());
		CLI::LateAction^ lateAction = unmanagedLateAction->GetInstance();

		lateAction->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}


	void FileProfileObserverImpl::OnAddEngineSuccess(const std::shared_ptr<mip::FileEngine>& engine, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<CLI::UnmanagedObject<CLI::LateValue<CLI::FileEngine^>>*>(context.get());
		CLI::LateValue<CLI::FileEngine^>^ lateValue = unmanagedLateValue->GetInstance();

		std::shared_ptr<mip::FileEngine>* ptrEngine = new std::shared_ptr<mip::FileEngine>(engine);

		lateValue->SetValue(gcnew FileEngine(ptrEngine));
	}

	void FileProfileObserverImpl::OnAddEngineError(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<CLI::UnmanagedObject<CLI::LateValue<CLI::FileEngine^>>*>(context.get());
		CLI::LateValue<CLI::FileEngine^>^ lateValue = unmanagedLateValue->GetInstance();

		lateValue->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}


	void FileProfileObserverImpl::OnDeleteEngineSuccess(const std::shared_ptr<void>& context)
	{
		auto unmanagedLateAction = static_cast<CLI::UnmanagedObject<CLI::LateAction>*>(context.get());
		CLI::LateAction^ lateAction = unmanagedLateAction->GetInstance();

		lateAction->Complete();
	}

	void FileProfileObserverImpl::OnDeleteEngineError(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateAction = static_cast<CLI::UnmanagedObject<CLI::LateAction>*>(context.get());
		CLI::LateAction^ lateAction = unmanagedLateAction->GetInstance();

		lateAction->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}

}
