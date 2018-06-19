#pragma once

#include "mip\file\file_handler.h"

#include "ContentLabel.h"
#include "LabelingOptions.h"
#include "LateValue.h"
#include "ManagedObject.h"
#include "PolicyDescriptor.h"
#include "UserPolicy.h"

namespace CLI
{
	public ref class FileHandler : public ManagedObject<std::shared_ptr<mip::FileHandler>>
	{
	internal:
		FileHandler(std::shared_ptr<mip::FileHandler>* ptr)
			: ManagedObject(true, ptr) {}

	public:
		void GetLabelAsync(LateValue<ContentLabel^>^ lateContentLabel);

		void SetLabel(String^ labelId, LabelingOptions^ labelingOptions);

		void DeleteLabel(AssignmentMethod method, String^ justificationMessage);

		void GetProtectionAsync(LateValue<UserPolicy^>^ lateUserPolicy);

		void SetCustomPermissions(PolicyDescriptor^ policyDescriptor);

		void RemoveProtection();

		void CommitAsync(String^ outputFilePath, LateValue<bool>^ lateResult);

		void CommitAsync(System::IO::Stream^ outputStream, LateValue<bool>^ lateResult);

		property String^ OutputFileName
		{
			String^ get();
		}
	};
}