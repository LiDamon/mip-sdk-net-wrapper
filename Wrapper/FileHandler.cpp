#include "FileHandler.h"

#include "Converters.h"
#include "UnmanagedObject.h"

namespace CLI
{
	void FileHandler::GetLabelAsync(LateValue<ContentLabel^>^ lateValue)
	{
		auto ptr = std::make_shared<UnmanagedObject<LateValue<ContentLabel^>>>(lateValue);
		m_Instance->get()->GetLabelAsync(ptr);
	}

	// TODO:
	//void FileHandler::SetLabel(String^ labelId, LabelingOptions^ labelingOptions);

	void FileHandler::DeleteLabel(AssignmentMethod method, String^ justificationMessage)
	{
		auto mipMethod = (mip::AssignmentMethod)method;

		m_Instance->get()->DeleteLabel(mipMethod, net_string_to_std_string(justificationMessage));
	}

	// TODO:
	//void FileHandler::GetProtectionAsync(LateValue<UserPolicy^>^ context);

}