#pragma once

#include "LateValue.h"

using namespace System::Threading;

namespace NetMip
{
	generic <class T>
	LateValue<T>::LateValue()
		: m_EventHandle(gcnew ManualResetEvent(false))
	{
	}

	generic <class T>
	void LateValue<T>::SetValue(T value)
	{
		m_Value = value;
		m_EventHandle->Set();
	}

	generic <class T>
	void LateValue<T>::SetError(System::Exception^ ex)
	{
		m_Exception = ex;
		m_EventHandle->Set();
	}

	generic <class T>
	T LateValue<T>::AwaitValue()
	{
		return this->AwaitValue(Timeout::Infinite);
	}

	generic <class T>
	T LateValue<T>::AwaitValue(int millisecondsTimeout)
	{
		m_EventHandle->WaitOne(millisecondsTimeout);

		if (m_Exception != nullptr)
			throw m_Exception;

		return m_Value;
	}
}