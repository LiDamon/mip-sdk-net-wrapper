#pragma once

namespace CLI
{
	template<class T>
	public ref class ManagedObject
	{
	protected:
		T * m_Instance;
		bool m_owner;

	public:
		ManagedObject(T* instance)
			: ManagedObject(true, instance)
		{
		}

		ManagedObject(bool owner, T* instance)
			: m_Instance(instance),
			  m_owner(owner)
		{
		}

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

		T* GetInstance()
		{
			return m_Instance;
		}
	};
}
