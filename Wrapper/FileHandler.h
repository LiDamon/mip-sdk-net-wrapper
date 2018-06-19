#pragma once

#include "mip\file\file_handler.h"

#include "ContentLabel.h"
#include "LateValue.h"
#include "ManagedObject.h"

namespace CLI
{
	public ref class FileHandler : public ManagedObject<std::shared_ptr<mip::FileHandler>>
	{
	internal:
		FileHandler(std::shared_ptr<mip::FileHandler>* ptr)
			: ManagedObject(true, ptr) {}

	public:
		void GetLabelAsync(LateValue<ContentLabel^>^ lateContentLabel);

		// TODO:
		//void SetLabel(String^ labelId, LabelingOptions^ labelingOptions);

		void DeleteLabel(AssignmentMethod method, String^ justificationMessage);

		// TODO:
		//void GetProtectionAsync(LateValue<UserPolicy^>^ context);

	};
}