#include "Label.h"

#include "Converters.h"

namespace CLI
{
	String^ Label::Id::get()
	{
		return std_string_to_net_string(this->m_Instance->GetId());
	}

	String^ Label::Name::get()
	{
		return std_string_to_net_string(this->m_Instance->GetName());
	}

	String^ Label::Description::get()
	{
		return std_string_to_net_string(this->m_Instance->GetDescription());
	}

	String^ Label::Color::get()
	{
		return std_string_to_net_string(this->m_Instance->GetColor());
	}

	String^ Label::Order::get()
	{
		return std_string_to_net_string(this->m_Instance->GetOrder());
	}

	String^ Label::Tooltip::get()
	{
		return std_string_to_net_string(this->m_Instance->GetTooltip());
	}

	bool Label::IsActive::get()
	{
		return this->m_Instance->IsActive();
	}

	Label^ Label::Parent::get()
	{
		return m_Parent;
	}

	array<Label^>^ Label::Children::get()
	{
		if (m_Children == nullptr)
		{
			auto mipChildren = this->m_Instance->GetChildren();

			auto arr = gcnew array<Label^>(mipChildren.size());

			int i = 0;
			for (auto const& mipChild : mipChildren)
			{
				auto child = gcnew Label(this, mipChild.get());

				arr[i++] = child;
			}

			m_Children = arr;
		}

		return m_Children;
	}
}