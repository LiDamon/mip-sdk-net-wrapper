#pragma once

#include <string>
#include <vector>

#include "ManagedObject.h"
#include "Pair.h"
#include "stdafx.h"
/**
#include "mip\file\file_engine.h"
/*/
namespace mip
{
	class FileEngine
	{
	public:
		class Settings
		{
		public:
			Settings(std::string id, std::string clientData, std::string locale) {}

			std::string GetId() { return ""; }
			std::string GetClientData() { return ""; }
			std::string GetLocale() { return ""; }
			std::string GetSessionId() { return ""; }
			void SetSessionId(std::string value) { }
			std::vector<std::pair<std::string, std::string>> GetCustomSettings() { std::vector<std::pair<std::string, std::string>> v; return v; }
			void SetCustomSettings(std::vector<std::pair<std::string, std::string>> value) {}
		};
	};
}
/**/

using namespace System;
using namespace System::Collections::Generic;

namespace CLI
{
	public ref class FileEngine
	{
	public:
		ref class Settings : public ManagedObject<mip::FileEngine::Settings>
		{
		public:

			Settings(String^ id, String^ clientData, String^ locale);

			property String^ Id
			{
				String^ get();
			}

			property String^ ClientData
			{
				String^ get();
			}

			property String^ Locale
			{
				String^ get();
			}

			property String^ SessionId
			{
				String^ get();
				void set(String^ value);
			}

			property array<Pair<String^, String^>^>^ CustomSettings
			{
				array<Pair<String^, String^>^>^ get();
				void set(array<Pair<String^, String^>^>^ value);
			}
		};
	};
}