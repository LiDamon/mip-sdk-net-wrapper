#pragma once

#include <string>

#include "mip\common_types.h"

#include "ManagedObject.h"

using namespace System;

namespace NetMip
{
	public ref struct ApplicationInfo : public ManagedObject<mip::ApplicationInfo>
	{
	public:
		ApplicationInfo(String^ applicationId, String^ friendlyName);

	public:
		property String^ ApplicationId
		{
			String^ get();
		}

		property String^ FriendlyName
		{
			String^ get();
		}
	};
}