#pragma once

#include "mip\file\file_engine.h"

#include "FileHandler.h"
#include "Label.h"
#include "ManagedObject.h"
#include "Pair.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;

namespace CLI
{
	public ref class FileEngine : public ManagedObject<std::shared_ptr<mip::FileEngine>>
	{
	public:
		ref class Settings : public ManagedObject<mip::FileEngine::Settings>
		{
		public:

			Settings(String^ id, String^ clientData)
				: Settings(id, clientData, "en-US") {}

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


		FileEngine(std::shared_ptr<mip::FileEngine>* ptr)
			: ManagedObject(true, ptr) {}

		array<CLI::Label^>^ ListSensitivityLabels();

		FileHandler^ CreateFileHandler(
			String^ inputFilePath);

		// TODO:
		//FileHandler^ CreateFileHandler(
		//	System::IO::Stream inputStream,
		//	String^ inputFileName);

	};
}