#pragma once

#include "mip/common_types.h"

#include "ManagedObject.h"

using namespace System;

namespace NetMip
{
	public ref class Identity : public ManagedObject<mip::Identity>
	{
	internal:
		Identity(mip::Identity* identity);

	public:
		Identity();

		explicit Identity(String^ email);

		property String^ Email
		{
			String^ get();
		}
	};
}