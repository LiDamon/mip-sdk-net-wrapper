#include <string>
#include <vector>

#include "Converters.h"
#include "FileEngine.h"
#include "FileHandlerObserverImpl.h"

namespace CLI
{
	FileEngine::Settings::Settings(String^ id, String^ clientData, String^ locale)
		: ManagedObject(new mip::FileEngine::Settings(net_string_to_std_string(id), net_string_to_std_string(clientData), net_string_to_std_string(locale)))
	{
	}

	String^ FileEngine::Settings::Id::get()
	{
		return std_string_to_net_string(m_Instance->GetId());
	}

	String^ FileEngine::Settings::ClientData::get()
	{
		return std_string_to_net_string(m_Instance->GetClientData());
	}

	String^ FileEngine::Settings::Locale::get()
	{
		return std_string_to_net_string(m_Instance->GetLocale());
	}

	String^ FileEngine::Settings::SessionId::get()
	{
		return std_string_to_net_string(m_Instance->GetSessionId());
	}

	void FileEngine::Settings::SessionId::set(String^ value)
	{
		m_Instance->SetSessionId(net_string_to_std_string(value));
	}


	array<Pair<String^, String^>^>^ FileEngine::Settings::CustomSettings::get()
	{
		auto customSettings = m_Instance->GetCustomSettings();

		auto arr = gcnew array<Pair<String^, String^>^>(customSettings.size());

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

		m_Instance->SetCustomSettings(vector);
	}


	array<CLI::Label^>^ FileEngine::ListSensitivityLabels()
	{
		auto mipLabels = m_Instance->get()->ListSensitivityLabels();

		auto arr = gcnew array<Label^>(mipLabels.size());

		int i = 0;
		for (auto const& mipLabel : mipLabels)
		{
			auto label = gcnew Label(mipLabel.get());

			arr[i++] = label;
		}

		return arr;
	}

	FileHandler^ FileEngine::CreateFileHandler(
		String^ inputFilePath)
	{
		auto observer = std::shared_ptr<mip::FileHandler::Observer>((mip::FileHandler::Observer*)(new FileHandlerObserverImpl()));

		std::shared_ptr<mip::FileHandler> mipHandler = m_Instance->get()->CreateFileHandler(
			net_string_to_std_string(inputFilePath),
			observer);

		std::shared_ptr<mip::FileHandler>* ptrHandler = new std::shared_ptr<mip::FileHandler>(mipHandler);

		return gcnew FileHandler(ptrHandler);
	}

}