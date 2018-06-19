#pragma once

#include <string>
#include <vector>

#include "mip\upe\label.h"

#include "ManagedObject.h"

using namespace System;
using namespace System::Collections::Generic;

namespace CLI
{
	public ref class Label : public ManagedObject<mip::Label>
	{
	private:
		Label^ m_Parent = nullptr;
		array<Label^>^ m_Children = nullptr;

	internal:

		Label(mip::Label* label)
			: ManagedObject(label)
		{}

		Label(Label^ parent, mip::Label* label)
			: ManagedObject(label),
			  m_Parent(parent)
		{}

	public:

		property String^ Id
		{
			String^ get();
		}

		property String^ Name
		{
			String^ get();
		}

		property String^ Description
		{
			String^ get();
		}

		property String^ Color
		{
			String^ get();
		}

		property String^ Order
		{
			String^ get();
		}

		property String^ Tooltip
		{
			String^ get();
		}

		property bool IsActive
		{
			bool get();
		}

		property Label^ Parent
		{
			Label^ get();
		}

		property array<Label^>^ Children
		{
			array<Label^>^ get();
		}
	};
}