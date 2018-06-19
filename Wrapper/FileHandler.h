#pragma once

#include "mip\file\file_handler.h"

#include "ContentLabel.h"
#include "LabelingOptions.h"
#include "LateValue.h"
#include "ManagedObject.h"
#include "PolicyDescriptor.h"
#include "UserPolicy.h"

namespace NetMip
{
	/// <summary>
	/// Interface for all file handling functions.
	/// </summary>
	public ref class FileHandler : public ManagedObject<std::shared_ptr<mip::FileHandler>>
	{
	internal:
		FileHandler(std::shared_ptr<mip::FileHandler>* ptr)
			: ManagedObject(true, ptr) {}

	public:

		/// <summary>
		/// Starts retrieving the sensitivity label from the file.
		/// </summary>
		void GetLabelAsync(LateValue<ContentLabel^>^ lateContentLabel);

		/// <summary>
		/// Starts retrieving the protection policy from the file.
		/// </summary>
		void GetProtectionAsync(LateValue<UserPolicy^>^ lateUserPolicy);

		/// <summary>
		/// Sets the sensitivity label to the file.
		/// </summary>
		/// <remarks>
		/// Changes will not be written to the file until <see cref="CommitAsync"/> will be called.
		/// </remarks>
		/// <exception cref="JustificationRequiredError">
		/// Thrown when setting the label requires a justification and no justification message was provided via the labelingOptions parameter.
		/// </exception>
		void SetLabel(String^ labelId, LabelingOptions^ labelingOptions);

		/// <summary>
		/// Deletes the sensitivity label from the file.
		/// </summary>
		/// <remarks>
		/// Changes will not be written to the file until <see cref="CommitAsync"/> will be called.
		/// Privilegd and Auto method allows the API to override any existing label.
		/// </remarks>
		/// <exception cref="JustificationRequiredError">
		/// Thrown when setting the label requires a justification and no justification message was provided via the justificationMessage parameter.
		/// </exception>
		void DeleteLabel(AssignmentMethod method, String^ justificationMessage);

		/// <summary>
		/// Sets custom permissions to the file.
		/// </summary>
		/// <remarks>
		/// Changes will not be written to the file until <see cref="CommitAsync"/> will be called.
		/// </remarks>
		void SetCustomPermissions(PolicyDescriptor^ policyDescriptor);

		/// <summary>
		/// Removes custom permissions from the file.
		/// </summary>
		/// <remarks>
		/// If the file is labeled, the label will be lost.
		/// Changes will not be written to the file until <see cref="CommitAsync"/> will be called.
		/// </remarks>
		void RemoveProtection();

		/// <summary>
		/// Writes the changes to the file specified by the outputFilePath parameter.
		/// </summary>
		void CommitAsync(String^ outputFilePath, LateValue<bool>^ lateResult);

		/// <summary>
		/// Writes the changes to the stream specified by the outputStream parameter.
		/// </summary>
		void CommitAsync(System::IO::Stream^ outputStream, LateValue<bool>^ lateResult);

		/// <summary>
		/// Calculates the output file name and extension based on the original file name and the accumulated changes..
		/// </summary>
		property String^ OutputFileName
		{
			String^ get();
		}
	};
}