#include "FileProfileObserverImpl.h"

#include "Converters.h"
#include "ExceptionHelper.h"
#include "FileProfile.h"
#include "LateValue.h"
#include "UnmanagedObject.h"

using namespace System;

namespace NetMip
{
	void FileProfileObserverImpl::OnLoadSuccess(const std::shared_ptr<mip::FileProfile>& profile, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<NetMip::UnmanagedObject<NetMip::LateValue<NetMip::FileProfile^>>*>(context.get());
		NetMip::LateValue<NetMip::FileProfile^>^ lateValue = unmanagedLateValue->GetInstance();

		std::shared_ptr<mip::FileProfile>* ptrProfile = new std::shared_ptr<mip::FileProfile>(profile);

		lateValue->SetValue(gcnew FileProfile(ptrProfile));
	}

	void FileProfileObserverImpl::OnLoadFailure(const std::exception_ptr & error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<NetMip::UnmanagedObject<NetMip::LateValue<NetMip::FileProfile^>>*>(context.get());
		NetMip::LateValue<NetMip::FileProfile^>^ lateValue = unmanagedLateValue->GetInstance();

		lateValue->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}

	void FileProfileObserverImpl::OnListEnginesSuccess(const std::vector<std::string>& engineIds, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<NetMip::UnmanagedObject<NetMip::LateValue<array<String^>^>>*>(context.get());
		NetMip::LateValue<array<String^>^>^ lateValue = unmanagedLateValue->GetInstance();

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
		auto unmanagedLateValue = static_cast<NetMip::UnmanagedObject<NetMip::LateValue<String^>>*>(context.get());
		NetMip::LateValue<String^>^ lateValue = unmanagedLateValue->GetInstance();

		lateValue->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}


	void FileProfileObserverImpl::OnUnloadEngineSuccess(const std::shared_ptr<void>& context)
	{
		auto unmanagedLateAction = static_cast<NetMip::UnmanagedObject<NetMip::LateAction>*>(context.get());
		NetMip::LateAction^ lateAction = unmanagedLateAction->GetInstance();

		lateAction->Complete();
	}

	void FileProfileObserverImpl::OnUnloadEngineError(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateAction = static_cast<NetMip::UnmanagedObject<NetMip::LateAction>*>(context.get());
		NetMip::LateAction^ lateAction = unmanagedLateAction->GetInstance();

		lateAction->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}


	void FileProfileObserverImpl::OnAddEngineSuccess(const std::shared_ptr<mip::FileEngine>& engine, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<NetMip::UnmanagedObject<NetMip::LateValue<NetMip::FileEngine^>>*>(context.get());
		NetMip::LateValue<NetMip::FileEngine^>^ lateValue = unmanagedLateValue->GetInstance();

		std::shared_ptr<mip::FileEngine>* ptrEngine = new std::shared_ptr<mip::FileEngine>(engine);

		lateValue->SetValue(gcnew FileEngine(ptrEngine));
	}

	void FileProfileObserverImpl::OnAddEngineError(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateValue = static_cast<NetMip::UnmanagedObject<NetMip::LateValue<NetMip::FileEngine^>>*>(context.get());
		NetMip::LateValue<NetMip::FileEngine^>^ lateValue = unmanagedLateValue->GetInstance();

		lateValue->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}


	void FileProfileObserverImpl::OnDeleteEngineSuccess(const std::shared_ptr<void>& context)
	{
		auto unmanagedLateAction = static_cast<NetMip::UnmanagedObject<NetMip::LateAction>*>(context.get());
		NetMip::LateAction^ lateAction = unmanagedLateAction->GetInstance();

		lateAction->Complete();
	}

	void FileProfileObserverImpl::OnDeleteEngineError(const std::exception_ptr& error, const std::shared_ptr<void>& context)
	{
		auto unmanagedLateAction = static_cast<NetMip::UnmanagedObject<NetMip::LateAction>*>(context.get());
		NetMip::LateAction^ lateAction = unmanagedLateAction->GetInstance();

		lateAction->SetError(gcnew System::Exception(ExceptionHelper::GetExceptionMessage(error)));
	}

}
