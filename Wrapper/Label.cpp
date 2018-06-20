#include "Label.h"

#include "Converters.h"

namespace NetMip
{
	Label::Label(bool owner, mip::Label* label)
		: ManagedObject(owner, label)
	{
		auto weakParent = label->GetParent();
		if (auto tmp = weakParent.lock())
		{
			if (mip::Label* parent = tmp.get())
			{
				m_Parent = gcnew Label(false, parent);
			}
		}
	}

	Label::Label(bool owner, mip::Label* label, Label^ parent)
		: ManagedObject(owner, label),
		  m_Parent(parent)
	{
	}

	String^ Label::Id::get()
	{
		return std_string_to_net_string(this->Instance->GetId());
	}

	String^ Label::Name::get()
	{
		return std_string_to_net_string(this->Instance->GetName());
	}

	String^ Label::Description::get()
	{
		return std_string_to_net_string(this->Instance->GetDescription());
	}

	String^ Label::Color::get()
	{
		return std_string_to_net_string(this->Instance->GetColor());
	}

	String^ Label::Order::get()
	{
		return std_string_to_net_string(this->Instance->GetOrder());
	}

	String^ Label::Tooltip::get()
	{
		return std_string_to_net_string(this->Instance->GetTooltip());
	}

	bool Label::IsActive::get()
	{
		return this->Instance->IsActive();
	}

	Label^ Label::Parent::get()
	{
		return m_Parent;
	}

	array<Label^>^ Label::Children::get()
	{
		if (m_Children == nullptr)
		{
			auto mipChildren = this->Instance->GetChildren();

			auto arr = gcnew array<Label^>((int)mipChildren.size());

			int i = 0;
			for (auto const& mipChild : mipChildren)
			{
				auto child = gcnew Label(false, mipChild.get(), this);

				arr[i++] = child;
			}

			m_Children = arr;
		}

		return m_Children;
	}
}