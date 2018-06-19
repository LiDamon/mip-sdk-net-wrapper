#include "FileHandler.h"

#include "Converters.h"
#include "StreamWrapper.h"
#include "UnmanagedObject.h"

namespace CLI
{
	void FileHandler::GetLabelAsync(LateValue<ContentLabel^>^ lateValue)
	{
		auto ptr = std::make_shared<UnmanagedObject<LateValue<ContentLabel^>>>(lateValue);
		m_Instance->get()->GetLabelAsync(ptr);
	}

	void FileHandler::SetLabel(String^ labelId, LabelingOptions^ labelingOptions)
	{
		mip::LabelingOptions mipLabelingOptions = *(labelingOptions->GetInstance());

		m_Instance->get()->SetLabel(
			net_string_to_std_string(labelId),
			mipLabelingOptions);
	}

	void FileHandler::DeleteLabel(AssignmentMethod method, String^ justificationMessage)
	{
		auto mipMethod = (mip::AssignmentMethod)method;

		m_Instance->get()->DeleteLabel(mipMethod, net_string_to_std_string(justificationMessage));
	}

	// TODO:
	//void FileHandler::GetProtectionAsync(LateValue<UserPolicy^>^ context);


	void FileHandler::RemoveProtection()
	{
		m_Instance->get()->RemoveProtection();
	}

	void FileHandler::CommitAsync(String^ outputFilePath, LateValue<bool>^ lateResult)
	{
		auto ptr = std::make_shared<UnmanagedObject<LateValue<bool>>>(lateResult);

		m_Instance->get()->CommitAsync(net_string_to_std_string(outputFilePath), ptr);
	}

	void FileHandler::CommitAsync(System::IO::Stream^ outputStream, LateValue<bool>^ lateResult)
	{
		auto streamWrapper = std::make_shared<StreamWrapper>(outputStream);

		auto ptr = std::make_shared<UnmanagedObject<LateValue<bool>>>(lateResult);

		m_Instance->get()->CommitAsync(streamWrapper, ptr);
	}

	String^ FileHandler::OutputFileName::get()
	{
		return std_string_to_net_string(m_Instance->get()->GetOutputFileName());
	}
}