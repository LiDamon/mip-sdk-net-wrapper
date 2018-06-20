#include "FileProfile.h"

#include "Converters.h"
#include "FileProfileObserverImpl.h"
#include "LateAction.h"
#include "LateValue.h"
#include "UnmanagedObject.h"

namespace NetMip
{
	FileProfile::Settings::Settings(
		String^ path,
		bool useInMemoryStorage,
		NetMip::AuthDelegate^ authDelegate,
		NetMip::ApplicationInfo^ applicationInfo)
		: ManagedObject(true, new mip::FileProfile::Settings(
			net_string_to_std_string(path),
			useInMemoryStorage,
			*(authDelegate->GetBridge()),
			std::shared_ptr<mip::FileProfile::Observer>(new FileProfileObserverImpl()),
			*(applicationInfo->Instance))),
		m_AuthDelegate(authDelegate),
		m_ApplicationInfo(applicationInfo)
	{
	}

	FileProfile::Settings::Settings(bool owner, mip::FileProfile::Settings* ptr)
		: ManagedObject(owner, ptr)
	{
	}

	String^ FileProfile::Settings::Path::get()
	{
		return std_string_to_net_string(this->Instance->GetPath());
	}

	bool FileProfile::Settings::UseInMemoryStorage::get()
	{
		return this->Instance->GetUseInMemoryStorage();
	}

	NetMip::AuthDelegate^ FileProfile::Settings::AuthDelegate::get()
	{
		return m_AuthDelegate;
	}

	NetMip::ApplicationInfo^ FileProfile::Settings::ApplicationInfo::get()
	{
		return m_ApplicationInfo;
	}

	bool FileProfile::Settings::SkipTelemetryInit::get()
	{
		return this->Instance->GetSkipTelemetryInit();
	}

	void FileProfile::Settings::SetSkipTelemetryInit()
	{
		this->Instance->SetSkipTelemetryInit();
	}

	String^ FileProfile::Settings::SessionId::get()
	{
		return std_string_to_net_string(this->Instance->GetSessionId());
	}

	void FileProfile::Settings::SessionId::set(String^ value)
	{
		this->Instance->SetSessionId(net_string_to_std_string(value));
	}



	void FileProfile::LoadAsync(Settings^ settings, NetMip::LateValue<FileProfile^>^ lateValue)
	{
		auto ptr = std::make_shared<UnmanagedObject<LateValue<FileProfile^>>>(lateValue);
		mip::FileProfile::LoadAsync(*(settings->Instance), ptr);
	}

	String^ FileProfile::GetSdkVersion()
	{
		auto version = mip::FileProfile::GetVersion();
		return char_array_to_net_string(version);
	}

	FileProfile::Settings^ FileProfile::GetSettings()
	{
		auto settings = this->Instance->get()->GetSettings();
		return gcnew FileProfile::Settings(true, new mip::FileProfile::Settings(settings));
	}

	void FileProfile::ListEnginesAsync(LateValue<array<String^>^>^ lateEngineIds)
	{
		auto ptr = std::make_shared<UnmanagedObject<LateValue<array<String^>^>>>(lateEngineIds);
		this->Instance->get()->ListEnginesAsync(ptr);
	}

	void FileProfile::UnloadEngineAsync(String^ engineId, LateAction^ action)
	{
		auto ptr = std::make_shared<UnmanagedObject<LateAction>>(action);
		this->Instance->get()->UnloadEngineAsync(
			net_string_to_std_string(engineId),
			ptr);
	}

	void FileProfile::AddEngineAsync(
		FileEngine::Settings^ settings,
		NetMip::LateValue<FileEngine^>^ lateValue)
	{
		auto ptr = std::make_shared<UnmanagedObject<LateValue<FileEngine^>>>(lateValue);
		this->Instance->get()->AddEngineAsync(*(settings->Instance), ptr);
	}

	void FileProfile::DeleteEngineAsync(String^ engineId, LateAction^ action)
	{
		auto ptr = std::make_shared<UnmanagedObject<LateAction>>(action);
		this->Instance->get()->DeleteEngineAsync(
			net_string_to_std_string(engineId),
			ptr);
	}

}
