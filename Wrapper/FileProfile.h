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
	/// <summary>
	/// FileProfile class is the root class for using the Microsoft Information Protection operations.
	/// </summary>
	/// <remarks>
	/// A typical application will only need one Profile but it can create multiple profiles if needed.
	/// </remarks>
	public ref class FileProfile : public ManagedObject<std::shared_ptr<mip::FileProfile>>
	{
	public:

		/// <summary>
		/// Interface for configuring the profile.
		/// </summary>
		/// <remarks>
		/// A typical application will only need one Profile but it can create multiple profiles if needed.
		/// </remarks>
		ref class Settings : public ManagedObject<mip::FileProfile::Settings>
		{
		public:
			Settings(
				String^ path,
				bool useInMemoryStorage,
				NetMip::AuthDelegate^ authDelegate,
				NetMip::ApplicationInfo^ applicationInfo);

		internal:
			Settings(bool owner, mip::FileProfile::Settings* settings);

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

		/// <summary>
		/// Starts loading a profile based on the provided settings.
		/// </summary>
		static void LoadAsync(Settings^ settings, NetMip::LateValue<FileProfile^>^ lateValue);

		/// <summary>
		/// Gets the underlying library version.
		/// </summary>
		static String^ GetSdkVersion();

	internal:
		FileProfile(std::shared_ptr<mip::FileProfile>* ptr)
			: ManagedObject(true, ptr) {}

	public:
		/// <summary>
		/// Gets the profile settings.
		/// </summary>
		Settings^ GetSettings();

		/// <summary>
		/// Starts list engines operation.
		/// </summary>
		void ListEnginesAsync(LateValue<array<String^>^>^ lateEngineIds);

		/// <summary>
		/// Starts unloading the file engine with the given id.
		/// </summary>
		void UnloadEngineAsync(String^ engineId, LateAction^ action);

		/// <summary>
		/// Starts adding a new file engine to the profile.
		/// </summary>
		void AddEngineAsync(
			FileEngine::Settings^ settings,
			NetMip::LateValue<FileEngine^>^ lateValue);

		/// <summary>
		/// Starts deleting the file engine with the given id.
		/// </summary>
		/// <remarks>
		/// All data for the given profile will be completely deleted.
		/// </remarks>
		void DeleteEngineAsync(String^ engineId, LateAction^ action);

	};


}