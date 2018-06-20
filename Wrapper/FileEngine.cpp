#include <string>
#include <vector>

#include "Converters.h"
#include "FileEngine.h"
#include "FileHandlerObserverImpl.h"
#include "StreamWrapper.h"

namespace NetMip
{
	FileEngine::Settings::Settings(String^ id, String^ clientData, String^ locale)
		: FileEngine::Settings::Settings(true, new mip::FileEngine::Settings(
			net_string_to_std_string(id),
			net_string_to_std_string(clientData),
			net_string_to_std_string(locale)))
	{
	}

	FileEngine::Settings::Settings(NetMip::Identity^ identity, String^ clientData, String^ locale)
		: FileEngine::Settings::Settings(true, new mip::FileEngine::Settings(
			*(identity->Instance),
			net_string_to_std_string(clientData),
			net_string_to_std_string(locale)))
	{
	}

	FileEngine::Settings::Settings(bool owner, mip::FileEngine::Settings* settings)
		: ManagedObject(owner, settings)
	{
	}


	String^ FileEngine::Settings::Id::get()
	{
		return std_string_to_net_string(this->Instance->GetId());
	}

	Identity^ FileEngine::Settings::Identity::get()
	{
		mip::Identity identity = this->Instance->GetIdentity();
		mip::Identity* ptr = new mip::Identity(identity);

		return gcnew NetMip::Identity(true, ptr);
	}

	void FileEngine::Settings::Identity::set(NetMip::Identity^ value)
	{
		this->Instance->SetIdentity(*(value->Instance));
	}

	String^ FileEngine::Settings::ClientData::get()
	{
		return std_string_to_net_string(this->Instance->GetClientData());
	}

	String^ FileEngine::Settings::Locale::get()
	{
		return std_string_to_net_string(this->Instance->GetLocale());
	}

	String^ FileEngine::Settings::SessionId::get()
	{
		return std_string_to_net_string(this->Instance->GetSessionId());
	}

	void FileEngine::Settings::SessionId::set(String^ value)
	{
		this->Instance->SetSessionId(net_string_to_std_string(value));
	}


	array<Pair<String^, String^>^>^ FileEngine::Settings::CustomSettings::get()
	{
		auto customSettings = this->Instance->GetCustomSettings();

		auto arr = gcnew array<Pair<String^, String^>^>((int)customSettings.size());

		int i = 0;
		for (auto const& pair : customSettings)
		{
			auto tuple = gcnew Pair<String^, String^>(
				std_string_to_net_string(pair.first),
				std_string_to_net_string(pair.second));

			arr[i++] = tuple;
		}

		return arr;
	}

	void FileEngine::Settings::CustomSettings::set(array<Pair<String^, String^>^>^ value)
	{
		std::vector<std::pair<std::string, std::string>> vector;

		for each (auto tuple in value)
		{
			std::pair<std::string, std::string> pair;
			pair.first = net_string_to_std_string(tuple->First);
			pair.second = net_string_to_std_string(tuple->Second);

			vector.push_back(pair);
		}

		this->Instance->SetCustomSettings(vector);
	}


	FileEngine::Settings^ FileEngine::GetSettings()
	{
		auto mipSettings = this->Instance->get()->GetSettings();
		mip::FileEngine::Settings* ptr = new mip::FileEngine::Settings(mipSettings);

		return gcnew FileEngine::Settings(true, ptr);
	}

	array<NetMip::Label^>^ FileEngine::ListSensitivityLabels()
	{
		auto mipLabels = this->Instance->get()->ListSensitivityLabels();

		auto arr = gcnew array<Label^>((int)mipLabels.size());

		int i = 0;
		for (auto const& mipLabel : mipLabels)
		{
			auto label = gcnew Label(false, mipLabel.get());

			arr[i++] = label;
		}

		return arr;
	}

	FileHandler^ FileEngine::CreateFileHandler(
		String^ inputFilePath)
	{
		auto observer = std::shared_ptr<mip::FileHandler::Observer>((mip::FileHandler::Observer*)(new FileHandlerObserverImpl()));

		std::shared_ptr<mip::FileHandler> mipHandler = this->Instance->get()->CreateFileHandler(
			net_string_to_std_string(inputFilePath),
			observer);

		std::shared_ptr<mip::FileHandler>* ptrHandler = new std::shared_ptr<mip::FileHandler>(mipHandler);

		return gcnew FileHandler(ptrHandler);
	}

	FileHandler^ FileEngine::CreateFileHandler(
		System::IO::Stream^ inputStream,
		String^ inputFilePath)
	{
		auto streamWrapper = std::make_shared<StreamWrapper>(inputStream);

		auto observer = std::shared_ptr<mip::FileHandler::Observer>((mip::FileHandler::Observer*)(new FileHandlerObserverImpl()));

		std::shared_ptr<mip::FileHandler> mipHandler = this->Instance->get()->CreateFileHandler(
			streamWrapper,
			net_string_to_std_string(inputFilePath),
			observer);

		std::shared_ptr<mip::FileHandler>* ptrHandler = new std::shared_ptr<mip::FileHandler>(mipHandler);

		return gcnew FileHandler(ptrHandler);
	}

}