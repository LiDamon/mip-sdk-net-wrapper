#pragma once

#include "gcroot.h"

namespace NetMip
{
	template<class T>
	public class UnmanagedObject
	{
	protected:
		gcroot<T^> m_Instance;

	public:
		UnmanagedObject()
		{
		}

		UnmanagedObject(T^ instance)
			: m_Instance(instance)
		{
		}

	public:
		T^ GetInstance()
		{
			return m_Instance;
		}

		void SetInstance(T^ instance)
		{
			m_Instance = instance;
		}
	};
}
