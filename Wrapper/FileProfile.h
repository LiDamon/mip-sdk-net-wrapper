#pragma once

#include <vcclr.h>

#include "mip/file/file_profile.h"

#include "ApplicationInfo.h"
#include "AuthDelegate.h"
#include "FileEngine.h"
#include "LateAction.h"
#include "LateValue.h"

using namespace System;

namespace NetMip
{
	public ref class FileProfile : public ManagedObject<std::shared_ptr<mip::FileProfile>>
	{
	public:
		ref class Settings : public ManagedObject<mip::FileProfile::Settings>
		{
		public:
			Settings(
				String^ path,
				bool useInMemoryStorage,
				NetMip::AuthDelegate^ authDelegate,
				NetMip::ApplicationInfo^ applicationInfo);

		internal:
			Settings(mip::FileProfile::Settings* settings);

		public:
			property String^ Path
			{
				String^ get();
			}

			property bool UseInMemoryStorage
			{
				bool get();
			}

			property NetMip::AuthDelegate^ AuthDelegate
			{
				NetMip::AuthDelegate^ get();
			}

			property NetMip::ApplicationInfo^ ApplicationInfo
			{
				NetMip::ApplicationInfo^ get();
			}

			property bool SkipTelemetryInit
			{
				bool get();
			}

			void SetSkipTelemetryInit();

			property String^ SessionId
			{
				String^ get();
				void set(String^ value);
			}

		private:
			NetMip::AuthDelegate^ m_AuthDelegate;
			NetMip::ApplicationInfo^ m_ApplicationInfo;
		};

	public:
		static void LoadAsync(Settings^ settings, NetMip::LateValue<FileProfile^>^ lateValue);

		static String^ GetVersion();

	internal:
		FileProfile(std::shared_ptr<mip::FileProfile>* ptr)
			: ManagedObject(true, ptr) {}

	public:
		Settings^ GetSettings();

		void ListEnginesAsync(LateValue<array<String^>^>^ lateEngineIds);

		void UnloadEngineAsync(String^ engineId, LateAction^ action);

		void AddEngineAsync(
			FileEngine::Settings^ settings,
			NetMip::LateValue<FileEngine^>^ lateValue);

		void DeleteEngineAsync(String^ engineId, LateAction^ action);

	};


}