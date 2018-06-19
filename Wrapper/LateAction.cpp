#pragma once

#include "LateAction.h"

using namespace System::Threading;

namespace NetMip
{
	LateAction::LateAction()
		: m_EventHandle(gcnew ManualResetEvent(false))
	{
	}

	void LateAction::Complete()
	{
		m_EventHandle->Set();
	}

	void LateAction::SetError(System::Exception^ ex)
	{
		m_Exception = ex;
		m_EventHandle->Set();
	}

	void LateAction::Await()
	{
		this->Await(Timeout::Infinite);
	}

	void LateAction::Await(int millisecondsTimeout)
	{
		m_EventHandle->WaitOne(millisecondsTimeout);

		if (m_Exception != nullptr)
			throw m_Exception;

		return;
	}
}