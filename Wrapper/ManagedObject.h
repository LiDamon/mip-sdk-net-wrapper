#pragma once

namespace NetMip
{
	template<class T>
	public ref class ManagedObject
	{
	private:
		T * m_Instance;
		bool m_owner;

	protected:
		ManagedObject(bool owner, T* instance)
			: m_Instance(instance),
			  m_owner(owner)
		{
		}

	public:
		virtual ~ManagedObject()
		{
			this->!ManagedObject();
		}

		!ManagedObject()
		{
			if (m_Instance != nullptr)
			{
				if (m_owner)
				{
					delete m_Instance;
					m_Instance = nullptr;
				}
			}
		}

	internal:
		property T* Instance
		{
			T* get()
			{
				return m_Instance;
			}
		}
	};
}
