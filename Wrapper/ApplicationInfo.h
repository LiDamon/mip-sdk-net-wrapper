#pragma once

#include <string>

#include "mip\common_types.h"

#include "ManagedObject.h"

using namespace System;

namespace CLI
{
	public ref struct ApplicationInfo : public ManagedObject<mip::ApplicationInfo>
	{
	public:
		ApplicationInfo(String^ applicationId, String^ friendlyName);

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