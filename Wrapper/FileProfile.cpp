#include "FileProfile.h"

#include "Converters.h"
#include "FileProfileObserverImpl.h"
#include "LateValue.h"
#include "UnmanagedObject.h"

namespace CLI
{
	FileProfile::Settings::Settings(
		String^ path,
		bool useInMemoryStorage,
		CLI::AuthDelegate^ authDelegate,
		//std::shared_ptr<Observer> observer,
		CLI::ApplicationInfo^ applicationInfo)
		: ManagedObject(new mip::FileProfile::Settings(
			net_string_to_std_string(path),
			useInMemoryStorage,
			*(authDelegate->GetBridge()),
			std::shared_ptr<mip::FileProfile::Observer>((mip::FileProfile::Observer*)(new FileProfileObserverImpl())),
			*(applicationInfo->GetInstance()))),
		m_AuthDelegate(authDelegate),
		m_ApplicationInfo(applicationInfo)
	{
	}

	String^ FileProfile::Settings::Path::get()
	{
		return std_string_to_net_string(m_Instance->GetPath());
	}

	bool FileProfile::Settings::UseInMemoryStorage::get()
	{
		return m_Instance->GetUseInMemoryStorage();
	}

	CLI::AuthDelegate^ FileProfile::Settings::AuthDelegate::get()
	{
		return m_AuthDelegate;
	}

	CLI::ApplicationInfo^ FileProfile::Settings::ApplicationInfo::get()
	{
		return m_ApplicationInfo;
	}

	bool FileProfile::Settings::SkipTelemetryInit::get()
	{
		return m_Instance->GetSkipTelemetryInit();
	}

	void FileProfile::Settings::SetSkipTelemetryInit()
	{
		m_Instance->SetSkipTelemetryInit();
	}

	String^ FileProfile::Settings::SessionId::get()
	{
		return std_string_to_net_string(m_Instance->GetSessionId());
	}

	void FileProfile::Settings::SessionId::set(String^ value)
	{
		m_Instance->SetSessionId(net_string_to_std_string(value));
	}



	void FileProfile::LoadAsync(Settings^ settings, CLI::LateValue<FileProfile^>^ lateValue)
	{
		auto ptr = std::make_shared<UnmanagedObject<LateValue<FileProfile^>>>(lateValue);
		mip::FileProfile::LoadAsync(*(settings->GetInstance()), ptr);
	}

	void FileProfile::AddEngineAsync(
		FileEngine::Settings^ settings,
		CLI::LateValue<FileEngine^>^ lateValue)
	{
		auto ptr = std::make_shared<UnmanagedObject<LateValue<FileEngine^>>>(lateValue);
		this->GetInstance()->get()->AddEngineAsync(*(settings->GetInstance()), ptr);
	}
}
