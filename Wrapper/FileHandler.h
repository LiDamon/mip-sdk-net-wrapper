#pragma once

#include "mip\file\file_handler.h"

#include "ManagedObject.h"

namespace CLI
{
	public ref class FileHandler : public ManagedObject<std::shared_ptr<mip::FileHandler>>
	{
	internal:
		FileHandler(std::shared_ptr<mip::FileHandler>* ptr)
			: ManagedObject(true, ptr) {}
	};
}